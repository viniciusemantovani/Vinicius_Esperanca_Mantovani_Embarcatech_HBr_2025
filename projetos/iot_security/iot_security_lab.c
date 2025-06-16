// Bibliotecas necessárias
#include <string.h>                 // Para funções de string como strlen()
#include "pico/stdlib.h"            // Biblioteca padrão do Pico (GPIO, tempo, etc.)
#include "pico/cyw43_arch.h"        // Driver WiFi para Pico W
#include "include/wifi_conn.h"      // Funções personalizadas de conexão WiFi
#include "include/mqtt_comm.h"      // Funções personalizadas para MQTT
#include "include/xor_cipher.h"     // Funções de cifra XOR

#define PUB_SUB 0 // 1 - Subscriber 0 - Publisher
#define BROKER_IP "192.168.82.123"

int main() {
    // Inicializa todas as interfaces de I/O padrão (USB serial, etc.)
    stdio_init_all();
    
    sleep_ms(5000);

    // Conecta à rede WiFi
    // Parâmetros: Nome da rede (SSID) e senha
    connect_to_wifi("M34 de Vinícius", "abacate123");

    // Configura o cliente MQTT
    // Parâmetros: ID do cliente, IP do broker, usuário, senha
    if(PUB_SUB == 1)
    mqtt_setup("bitdog2", BROKER_IP, "bitdog2", "Senha1234");
    else
    mqtt_setup("bitdog", BROKER_IP, "bitdogExp", "Senha123");

    // Mensagem original a ser enviada
    const char *mensagem = "ola tudo bem?";
    // Buffer para mensagem criptografada (16 bytes)
    uint8_t criptografada[16];
    // Criptografa a mensagem usando XOR com chave 42
    xor_encrypt((uint8_t *)mensagem, criptografada, strlen(mensagem), 42);

    if(PUB_SUB == 1)
    mqtt_comm_subscribe("escola/sala1/temperatura");

    // Loop principal do programa
    while (true) {

        if(PUB_SUB == 0)
        // Publica a mensagem original (não criptografada)
        mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(criptografada));
        
        // Alternativa: Publica a mensagem criptografada (atualmente comentada)
        // mqtt_comm_publish("escola/sala1/temperatura", criptografada, strlen(mensagem));
        
        // Aguarda 5 segundos antes da próxima publicação
        sleep_ms(5000);
    }
    return 0;
}

/* 
 * Comandos de terminal para testar o MQTT:
 * 
 * Inicia o broker MQTT com logs detalhados:
 * mosquitto -c mosquitto.conf -v
 * 
 * Assina o tópico de temperatura (recebe mensagens):
 * mosquitto_sub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123"
 * 
 * Publica mensagem de teste no tópico de temperatura:
 * mosquitto_pub -h localhost -p 1883 -t "escola/sala1/temperatura" -u "aluno" -P "senha123" -m "26.6"
 */