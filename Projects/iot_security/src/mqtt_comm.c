#include "lwip/apps/mqtt.h"       // Biblioteca MQTT do lwIP
#include "include/mqtt_comm.h"    // Header file com as declarações locais
// Base: https://github.com/BitDogLab/BitDogLab-C/blob/main/wifi_button_and_led/lwipopts.h
#include "lwipopts.h"             // Configurações customizadas do lwIP
#include "include/xor_cipher.h"

/* Variável global estática para armazenar a instância do cliente MQTT
 * 'static' limita o escopo deste arquivo */
static mqtt_client_t *client;

/* Callback de conexão MQTT - chamado quando o status da conexão muda
 * Parâmetros:
 *   - client: instância do cliente MQTT
 *   - arg: argumento opcional (não usado aqui)
 *   - status: resultado da tentativa de conexão */
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("Conectado ao broker MQTT com sucesso!\n");
    } else {
        printf("Falha ao conectar ao broker, código: %d\n", status);
    }
}

/* Função para configurar e iniciar a conexão MQTT
 * Parâmetros:
 *   - client_id: identificador único para este cliente
 *   - broker_ip: endereço IP do broker como string (ex: "192.168.1.1")
 *   - user: nome de usuário para autenticação (pode ser NULL)
 *   - pass: senha para autenticação (pode ser NULL) */
void mqtt_setup(const char *client_id, const char *broker_ip, const char *user, const char *pass) {
    ip_addr_t broker_addr;  // Estrutura para armazenar o IP do broker
    
    // Converte o IP de string para formato numérico
    if (!ip4addr_aton(broker_ip, &broker_addr)) {
        printf("Erro no IP\n");
        return;
    }

    // Cria uma nova instância do cliente MQTT
    client = mqtt_client_new();
    if (client == NULL) {
        printf("Falha ao criar o cliente MQTT\n");
        return;
    }

    // Configura as informações de conexão do cliente
    struct mqtt_connect_client_info_t ci = {
        .client_id = client_id,  // ID do cliente
        .client_user = user,     // Usuário (opcional)
        .client_pass = pass      // Senha (opcional)
    };

    // Inicia a conexão com o broker
    // Parâmetros:
    //   - client: instância do cliente
    //   - &broker_addr: endereço do broker
    //   - 1883: porta padrão MQTT
    //   - mqtt_connection_cb: callback de status
    //   - NULL: argumento opcional para o callback
    //   - &ci: informações de conexão
    mqtt_client_connect(client, &broker_addr, 1883, mqtt_connection_cb, NULL, &ci);
}

/* Callback de confirmação de publicação
 * Chamado quando o broker confirma recebimento da mensagem (para QoS > 0)
 * Parâmetros:
 *   - arg: argumento opcional
 *   - result: código de resultado da operação */
static void mqtt_pub_request_cb(void *arg, err_t result) {
    if (result == ERR_OK) {
        printf("Publicação MQTT enviada com sucesso!\n");
    } else {
        printf("Erro ao publicar via MQTT: %d\n", result);
    }
}

/* Função para publicar dados em um tópico MQTT
 * Parâmetros:
 *   - topic: nome do tópico (ex: "sensor/temperatura")
 *   - data: payload da mensagem (bytes)
 *   - len: tamanho do payload */
void mqtt_comm_publish(const char *topic, const uint8_t *data, size_t len) {
    // Envia a mensagem MQTT
    err_t status = mqtt_publish(
        client,              // Instância do cliente
        topic,               // Tópico de publicação
        data,                // Dados a serem enviados
        len,                 // Tamanho dos dados
        0,                   // QoS 0 (nenhuma confirmação)
        0,                   // Não reter mensagem
        mqtt_pub_request_cb, // Callback de confirmação
        NULL                 // Argumento para o callback
    );

    if (status != ERR_OK) {
        printf("mqtt_publish falhou ao ser enviada: %d\n", status);
    }
}

/* Callback de chegada de mensagens */
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
    printf("Mensagem recebida no tópico: %s, tamanho: %u bytes\n", topic, tot_len);
}

/* Callback para processar os dados da mensagem recebida */
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
    uint8_t descriptografada[16];
    xor_encrypt((uint8_t *)data, descriptografada, len, 42);
    printf("Payload recebido (%u bytes): %.*s\n", len, len, descriptografada);
}

/* Callback de confirmação do subscribe */
void mqtt_sub_request_cb(void *arg, err_t result) {
    if (result == ERR_OK) {
        printf("Subscribe realizado com sucesso.\n");
    } else {
        printf("Erro ao realizar subscribe: %d\n", result);
    }
}

/* Função para se inscrever em um tópico MQTT
 * Parâmetros:
 *   - topic: nome do tópico (ex: "sensor/temperatura")
 */
void mqtt_comm_subscribe(const char *topic) {
    // Define os callbacks de mensagem
    mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, NULL);

    // Realiza a inscrição no tópico
    err_t status = mqtt_subscribe(
        client,               // Instância do cliente
        topic,                // Tópico para se inscrever
        0,                    // QoS 0
        mqtt_sub_request_cb,  // Callback de confirmação
        NULL                  // Argumento para o callback
    );

    if (status != ERR_OK) {
        printf("mqtt_subscribe falhou: %d\n", status);
    }
}