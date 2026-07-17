// ====================================================================================
// INCLUSÃO DE BIBLIOTECAS
// ====================================================================================

#include <stdio.h>              // Biblioteca padrão de entrada/saída, usada para o printf().
#include <string.h>             // Biblioteca para manipulação de strings.
#include "pico/stdlib.h"         // Biblioteca principal do SDK do Raspberry Pi Pico.
#include "pico/cyw43_arch.h"     // Biblioteca para controle do chip wireless (CYW43439) da Pico W.
#include "btstack.h"             // Biblioteca principal da pilha de software Bluetooth (BTstack).

// ====================================================================================
// CONFIGURAÇÃO DOS PACOTES DE ANÚNCIO (ADVERTISING) BLUETOOTH
// ====================================================================================

// ==== Pacote de Advertising (contém o nome do dispositivo) ====
// Este é o pacote que o dispositivo transmite para ser descoberto por outros.
static uint8_t adv_data[] = {
    // Campo de Flags: indica que o dispositivo é BLE (BR/EDR Not Supported) e visível publicamente.
    0x02, 0x01, 0x06,
    // Campo de Nome Local Completo: define o nome 'Pico-BLE'.
    // 0x08 = tamanho (8 bytes), 0x09 = tipo (nome), 'P','i','c','o','-','B','L','E' = nome em ASCII.
    0x08, 0x09, 'P','i','c','o','-','B','L','E'
};

// ==== Pacote de Scan Response (contém o UUID do serviço) ====
// Informação extra que um scanner (como um celular) pode solicitar após receber o pacote de advertising.
static uint8_t scan_rsp_data[] = {
    // Lista completa de Serviços de 16 bits.
    // 0x03 = tamanho (3 bytes), 0x03 = tipo (lista de serviços), 0xF0, 0xFF = UUID do serviço (0xFFF0).
    0x03, 0x03, 0xF0, 0xFF
};

// ====================================================================================
// VARIÁVEIS GLOBAIS DA LÓGICA DA APLICAÇÃO
// ====================================================================================

// ==== Valor e Handle da Característica BLE ====
static uint8_t  mobility_level = 1;        // Variável que armazena o valor principal (nível de mobilidade), inicia em 1.
static uint16_t mobility_value_handle = 0; // "Handle" é um identificador único para a característica. O BTstack definirá seu valor.

// ==== Variáveis para os Timers e Estados dos LEDs ====
static btstack_timer_source_t led_timer_green;     // Estrutura do timer para o LED verde.
static int  led_blink_remaining_green = 0;         // Contador de quantas piscadas ainda faltam.
static bool led_state_green = false;               // Estado atual do LED (false=apagado, true=aceso).

static btstack_timer_source_t led_timer_blue;      // Estrutura do timer para o LED azul.
static int  led_blink_remaining_blue = 0;
static bool led_state_blue = false;

static btstack_timer_source_t led_timer_red;       // Estrutura do timer para o LED vermelho.
static int  led_blink_remaining_red = 0;
static bool led_state_red = false;

// ====================================================================================
// FUNÇÕES AUXILIARES E DE CONTROLE DOS LEDs
// ====================================================================================

// ---- Função auxiliar para inicializar um pino como saída ----
static void gpio_init_output_low(uint gpio){
    gpio_init(gpio);                  // Inicializa o pino GPIO.
    gpio_set_dir(gpio, GPIO_OUT);     // Define o pino como saída.
    gpio_put(gpio, 0);                // Define o valor inicial como 0 (desligado).
}

// ---- Funções de controle do LED VERDE ----

// Esta função é o "callback" do timer. É executada repetidamente para fazer o LED piscar.
static void led_timer_handler_green(btstack_timer_source_t *ts){
    if (led_blink_remaining_green <= 0){ // Se o contador de piscadas chegou a zero...
        gpio_put(GREEN_LED, 0);          // ...apaga o LED...
        return;                          // ...e para a execução.
    }
    led_state_green = !led_state_green;      // Inverte o estado do LED (liga/desliga).
    gpio_put(GREEN_LED, led_state_green);    // Aplica o novo estado ao pino físico.
    led_blink_remaining_green--;             // Decrementa o contador de piscadas.
    btstack_run_loop_set_timer(ts, 500);     // Reagenda esta mesma função para ser chamada daqui a 500ms.
    btstack_run_loop_add_timer(ts);          // Adiciona o timer de volta ao loop de eventos.
}

// Esta função inicia a sequência de piscar do LED verde.
static void start_led_blink_green(int level){
    int crossing_time_sec = 5 * level;                 // Calcula o tempo total que o LED deve piscar.
    led_blink_remaining_green = crossing_time_sec * 2; // O número de piscadas é o tempo * 2 (porque pisca 2x por segundo).
    led_state_green = false;                           // Garante que o estado inicial seja 'apagado'.
    gpio_put(GREEN_LED, 0);                            // Apaga o LED antes de começar.
    btstack_run_loop_set_timer(&led_timer_green, 500); // Agenda a primeira chamada do handler para daqui a 500ms.
    btstack_run_loop_add_timer(&led_timer_green);      // Adiciona o timer ao loop de eventos.
    printf("[LED VERDE] Piscando por %d s (nivel=%d)\n", crossing_time_sec, level);
}

// ---- Funções de controle do LED AZUL (sinaliza conexão) ----
static void led_timer_handler_blue(btstack_timer_source_t *ts){
    if (led_blink_remaining_blue <= 0){ gpio_put(BLUE_LED, 0); return; }
    led_state_blue = !led_state_blue;
    gpio_put(BLUE_LED, led_state_blue);
    led_blink_remaining_blue--;
    btstack_run_loop_set_timer(ts, 300);
    btstack_run_loop_add_timer(ts);
}

static void start_led_blink_blue(void){
    btstack_run_loop_remove_timer(&led_timer_red); // Para o timer do LED vermelho, se estiver ativo.
    gpio_put(RED_LED, 0);
    btstack_run_loop_remove_timer(&led_timer_blue); // Reinicia o timer do LED azul.
    led_state_blue = false;
    gpio_put(BLUE_LED, 0);
    led_blink_remaining_blue = 6; // Pisca 3 vezes.
    btstack_run_loop_set_timer(&led_timer_blue, 50);
    btstack_run_loop_add_timer(&led_timer_blue);
    printf("[LED AZUL] Piscando (conexão)\n");
}

// ---- Funções de controle do LED VERMELHO (sinaliza desconexão) ----
static void led_timer_handler_red(btstack_timer_source_t *ts){
    if (led_blink_remaining_red <= 0){ gpio_put(RED_LED, 0); return; }
    led_state_red = !led_state_red;
    gpio_put(RED_LED, led_state_red);
    led_blink_remaining_red--;
    btstack_run_loop_set_timer(ts, 300);
    btstack_run_loop_add_timer(ts);
}
static void start_led_blink_red(void){
    btstack_run_loop_remove_timer(&led_timer_blue); // Para o timer do LED azul, se estiver ativo.
    gpio_put(BLUE_LED, 0);
    btstack_run_loop_remove_timer(&led_timer_red); // Reinicia o timer do LED vermelho.
    led_state_red = false;
    gpio_put(RED_LED, 0);
    led_blink_remaining_red = 6; // Pisca 3 vezes.
    btstack_run_loop_set_timer(&led_timer_red, 50);
    btstack_run_loop_add_timer(&led_timer_red);
    printf("[LED VERMELHO] Piscando (desconexão)\n");
}

// ====================================================================================
// CALLBACKS DO SERVIDOR GATT (LÓGICA DE LEITURA E ESCRITA)
// ====================================================================================

// Callback chamado quando um cliente (ex: celular) tenta LER o valor da característica.
static uint16_t att_read_callback(hci_con_handle_t connection_handle, uint16_t attribute_handle, uint16_t offset, uint8_t *buffer, uint16_t buffer_size) {
    (void)connection_handle; // Ignora o parâmetro (não usado aqui).
    if (attribute_handle != mobility_value_handle) return 0; // Verifica se o handle corresponde à nossa característica.
    if (offset > 0) return 0; // Não suporta leitura com deslocamento.
    if (buffer && buffer_size >= 1) { // Se o buffer for válido e tiver espaço...
        buffer[0] = mobility_level;   // ...copia o valor da nossa variável para o buffer de resposta.
        return 1; // Retorna o tamanho dos dados (1 byte).
    }
    return 1; // Retorna o tamanho mesmo se o buffer for nulo (necessário para o GATT).
}

// Callback chamado quando um cliente tenta ESCREVER um novo valor na característica.
static int att_write_callback(hci_con_handle_t connection_handle, uint16_t attribute_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size) {
    (void)connection_handle; (void)transaction_mode; // Ignora parâmetros não usados.
    if (attribute_handle != mobility_value_handle) return ATT_ERROR_ATTRIBUTE_NOT_FOUND; // Verifica o handle.
    if (offset != 0 || buffer_size < 1) return ATT_ERROR_INVALID_ATTRIBUTE_VALUE_LENGTH; // Valida o tamanho e offset.

    uint8_t value = buffer[0]; // Pega o primeiro byte do dado recebido.
    // Converte o valor de caractere ASCII ('1'..'5') para número (1..5)
    if (value >= '1' && value <= '5') value = (uint8_t)(value - '0');
    // Garante que o valor esteja no intervalo [1, 5].
    if (value < 1) value = 1;
    if (value > 5) value = 5;
    
    mobility_level = value; // Atualiza a variável global com o novo valor validado.
    printf("[GATT] Mobility level = %u (tempo=%us)\n", mobility_level, mobility_level * 5);
    start_led_blink_green(mobility_level); // Inicia o feedback visual no LED verde.
    return ATT_ERROR_SUCCESS; // Retorna sucesso.
}

// ====================================================================================
// CONFIGURAÇÃO DO BANCO DE DADOS GATT
// ====================================================================================

// Função que monta a estrutura de Serviços e Características do nosso dispositivo.
static void create_gatt_database(void) {
    att_db_util_init(); // Inicia o construtor do banco de dados GATT.
    // Adiciona o serviço principal com o UUID 0xFFF0.
    att_db_util_add_service_uuid16(0xFFF0);
    // Adiciona a característica (com UUID 0xFFF1) ao serviço criado acima.
    mobility_value_handle = att_db_util_add_characteristic_uuid16(
        0xFFF1, // UUID da característica.
        // Propriedades: permite Leitura, Escrita (com e sem resposta). DYNAMIC significa que o valor é gerenciado por callbacks.
        ATT_PROPERTY_READ | ATT_PROPERTY_WRITE | ATT_PROPERTY_WRITE_WITHOUT_RESPONSE | ATT_PROPERTY_DYNAMIC,
        ATT_SECURITY_NONE, ATT_SECURITY_NONE, // Sem requisitos de segurança.
        NULL, 0
    );
    printf("GATT DB created. Service 0xFFF0, Char 0xFFF1, value_handle=0x%04x\n", mobility_value_handle);
}

// ====================================================================================
// GERENCIADOR PRINCIPAL DE PACOTES E EVENTOS BLUETOOTH
// ====================================================================================

// Registra a função packet_handler para receber os eventos.
static btstack_packet_callback_registration_t hci_event_callback_registration;

// Esta função é o "cérebro" da aplicação, processando todos os eventos da pilha Bluetooth.
static void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    (void)channel; (void)size; // Ignora parâmetros não usados.
    if (packet_type != HCI_EVENT_PACKET) return; // Processa apenas pacotes de evento.

    uint8_t event_type = hci_event_packet_get_type(packet);
    switch (event_type){
        // Evento disparado quando o estado da pilha Bluetooth muda.
        case BTSTACK_EVENT_STATE:
            // Se o estado for 'HCI_STATE_WORKING', significa que a pilha está pronta.
            if (btstack_event_state_get_state(packet) == HCI_STATE_WORKING){
                printf("Bluetooth ready!\n");
                cyw43_arch_gpio_put(LED_PIN, 1); // Acende o LED onboard para indicar que o BLE está ativo.
                // Configura os parâmetros de advertising (intervalo, tipo, etc.).
                gap_advertisements_set_params(160, 200, 0, 0, NULL, 0x07, 0x00);
                // Define os dados do pacote de advertising.
                gap_advertisements_set_data(sizeof(adv_data), adv_data);
                // Define os dados do pacote de scan response.
                gap_scan_response_set_data(sizeof(scan_rsp_data), scan_rsp_data);
                // Habilita o advertising, tornando o dispositivo visível.
                gap_advertisements_enable(1);
            }
            break;

        // Meta-evento do Bluetooth Low Energy (contém sub-eventos).
        case HCI_EVENT_LE_META:
            // Verifica se o sub-evento é de conexão completa.
            if (hci_event_le_meta_get_subevent_code(packet) == HCI_SUBEVENT_LE_CONNECTION_COMPLETE){
                printf("Device connected!\n");
                // start_led_blink_blue(); // Poderia chamar a função para piscar o LED azul aqui.
            }
            break;

        // Evento disparado quando um dispositivo se desconecta.
        case HCI_EVENT_DISCONNECTION_COMPLETE:
            printf("Device disconnected\n");
            // start_led_blink_red(); // Poderia chamar a função para piscar o LED vermelho aqui.
            // Reconfigura e reabilita o advertising para permitir novas conexões.
            gap_advertisements_set_params(160, 200, 0, 0, NULL, 0x07, 0x00);
            gap_advertisements_enable(1);
            break;
    }
}

// ====================================================================================
// FUNÇÃO PRINCIPAL (MAIN)
// ====================================================================================
int main(){
    // Inicializa a comunicação serial via USB para usar o printf().
    stdio_init_all();
    printf("\n=== Pico W BLE Mobility Service (Advertising rápido fixo, LED onboard sempre ON) ===\n");

    // Inicializa o chip wireless CYW43439, configurando para o Brasil.
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_BRAZIL)){
        printf("Failed to init cyw43_arch\n");
        return -1;
    }

    // Inicializa os pinos dos LEDs externos como saídas em nível baixo.
    gpio_init_output_low(GREEN_LED);
    gpio_init_output_low(BLUE_LED);
    gpio_init_output_low(RED_LED);

    // Associa cada timer com sua respectiva função de callback (handler).
    btstack_run_loop_set_timer_handler(&led_timer_green, led_timer_handler_green);
    btstack_run_loop_set_timer_handler(&led_timer_blue,  led_timer_handler_blue);
    btstack_run_loop_set_timer_handler(&led_timer_red,   led_timer_handler_red);

    // Inicializa as camadas da pilha Bluetooth.
    l2cap_init(); // Protocolo de multiplexação e adaptação da camada lógica.
    sm_init();    // Gerenciador de Segurança (para pareamento).
    
    // Monta a nossa estrutura de serviços e características.
    create_gatt_database();
    
    // Inicializa o servidor ATT (Protocolo de Atributos) e registra nossos callbacks de leitura/escrita.
    att_server_init(att_db_util_get_address(), att_read_callback, att_write_callback);

    // Registra nossa função packet_handler para receber todos os eventos da camada HCI (Host Controller Interface).
    hci_event_callback_registration.callback = &packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);

    // Liga o rádio Bluetooth.
    hci_power_control(HCI_POWER_ON);
    printf("Bluetooth initializing...\n");

    // Inicia o loop principal de eventos do BTstack. O programa fica "preso" nesta linha para sempre,
    // processando eventos de Bluetooth e de timers de forma assíncrona.
    btstack_run_loop_execute();
    
    // As linhas abaixo, em teoria, nunca são alcançadas em um sistema embarcado que roda para sempre.
    // ★★★ ALTERAÇÃO AQUI: Corrigido de "cyw4fs" para "cyw43" ★★★
    cyw43_arch_deinit(); // Desliga o chip wireless.
    
    return 0;
}