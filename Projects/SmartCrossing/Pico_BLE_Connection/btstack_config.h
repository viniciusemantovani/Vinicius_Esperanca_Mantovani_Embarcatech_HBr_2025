// Garante que este arquivo de cabeçalho seja incluído apenas uma vez durante a compilação.
#ifndef _PICO_BTSTACK_CONFIG_COMMON_H
#define _PICO_BTSTACK_CONFIG_COMMON_H

// Verifica se a funcionalidade Bluetooth Low Energy (BLE) está habilitada no projeto.
// Se não estiver, gera um erro de compilação, pois este código depende do BLE.
#ifndef ENABLE_BLE
#error Please link to pico_btstack_ble
#endif

// ====================================================================================
// HABILITAÇÃO DE FUNCIONALIDADES DO BTSTACK
// ====================================================================================

#define ENABLE_LE_PERIPHERAL  // Habilita o modo "Periférico" (servidor), permitindo que o Pico seja descoberto e se conecte a um dispositivo central (como um celular).
#define ENABLE_LOG_INFO       // Habilita mensagens de log informativas no console (via printf).
#define ENABLE_LOG_ERROR      // Habilita mensagens de log de erro no console.
#define ENABLE_PRINTF_HEXDUMP // Permite imprimir dados brutos em formato hexadecimal, útil para depuração.

// Como o Pico atuará apenas como um servidor (periférico), ele não iniciará conexões.
// Por isso, o número máximo de clientes GATT que ele pode gerenciar é zero.
#define MAX_NR_GATT_CLIENTS 0

// ====================================================================================
// CONFIGURAÇÃO DE BUFFERS E TAMANHOS (GERENCIAMENTO DE MEMÓRIA)
// ====================================================================================

#define HCI_OUTGOING_PRE_BUFFER_SIZE 4          // Reserva 4 bytes antes do buffer de envio de dados para o cabeçalho do pacote.
#define HCI_ACL_PAYLOAD_SIZE (255 + 4)          // Define o tamanho máximo da carga útil de um pacote de dados (ACL) como 259 bytes.
#define HCI_ACL_CHUNK_SIZE_ALIGNMENT 4          // Garante que os blocos de memória para pacotes sejam alinhados em múltiplos de 4 bytes para otimização.
#define MAX_NR_HCI_CONNECTIONS 1                // Limita o dispositivo a apenas uma conexão Bluetooth simultânea.
#define MAX_NR_SM_LOOKUP_ENTRIES 3              // Define o número de dispositivos pareados cujas informações de segurança podem ser armazenadas.
#define MAX_NR_WHITELIST_ENTRIES 1              // Reduzido de 16 para 1 para economizar memória. A "whitelist" permite conexões apenas de dispositivos específicos.
#define MAX_NR_LE_DEVICE_DB_ENTRIES 1           // Reduzido de 16. Define o tamanho do banco de dados para armazenar informações sobre outros dispositivos BLE.

// ---- Limites de Buffers do Controlador Bluetooth ----
#define MAX_NR_CONTROLLER_ACL_BUFFERS 3 // Número de buffers para pacotes de dados (ACL) que o controlador pode armazenar.
#define MAX_NR_CONTROLLER_SCO_PACKETS 3 // Número de buffers para pacotes de áudio (SCO), embora não seja usado neste projeto.

// ---- Controle de Fluxo (Flow Control) ----
#define ENABLE_HCI_CONTROLLER_TO_HOST_FLOW_CONTROL // Habilita um mecanismo para evitar que o controlador sobrecarregue o processador principal (o Pico) com dados.
#define HCI_HOST_ACL_PACKET_LEN (255+4)            // Tamanho do pacote de dados que o host (Pico) pode receber.
#define HCI_HOST_ACL_PACKET_NUM 3                  // Número de pacotes de dados que o host pode enfileirar.
#define HCI_HOST_SCO_PACKET_LEN 120                // Tamanho do pacote de áudio que o host pode receber.
#define HCI_HOST_SCO_PACKET_NUM 3                  // Número de pacotes de áudio que o host pode enfileirar.

// ---- Configuração de Armazenamento Persistente (NVM) ----
#define NVM_NUM_DEVICE_DB_ENTRIES 1   // Reduzido de 16. Número de dispositivos salvos na memória não volátil.
#define NVM_NUM_LINK_KEYS 1           // Reduzido de 16. Número de chaves de pareamento salvas.

// ---- Tamanho do Banco de Dados ATT (GATT) ----
// Define o tamanho máximo do banco de dados que armazena os Serviços e Características.
// Reduzido de 512 para 128 bytes para economizar muita memória, já que o projeto é simples.
#define MAX_ATT_DB_SIZE 128

// ====================================================================================
// CONFIGURAÇÃO DA CAMADA DE ABSTRAÇÃO DE HARDWARE (HAL) DO BTSTACK
// ====================================================================================

#define HAVE_EMBEDDED_TIME_MS      // Informa ao BTstack que o sistema tem uma função para obter o tempo em milissegundos.
#define HAVE_ASSERT                // Habilita a função `assert()`, que para o programa se uma condição crítica não for atendida (bom para depuração).
#define HCI_RESET_RESEND_TIMEOUT_MS 1000 // Define o tempo (1s) para reenviar um comando de reset se não houver resposta.
#define ENABLE_SOFTWARE_AES128     // Habilita a criptografia AES-128 via software, necessária para conexões seguras.
#define ENABLE_MICRO_ECC_FOR_LE_SECURE_CONNECTIONS // Habilita uma biblioteca de criptografia de curva elíptica (ECC) para conexões seguras BLE.

#endif // Fim do bloco _PICO_BTSTACK_CONFIG_COMMON_H