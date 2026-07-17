# Task: IoT Security Lab - EmbarcaTech 2025

Authors: **Eduardo Tejada and Vinícius Esperança Mantovani**

Course: Embedded Systems Technological Residency

Institution: EmbarcaTech - HBr

Campinas, June 2025

---
## About the Program

This program is divided into two functionalities: an MQTT publisher and an MQTT subscriber. The choice between functionalities is made through a `define` in the main code. This multiplicity of functionalities allows for MQTT communication between two BitDogLab boards using a broker hosted on a computer.
<br/>
Highlights of this project include the knowledge acquired regarding MQTT, MQTT authentication and security, and simple cryptography. The latter is achieved by using an XOR cipher to encrypt and decrypt messages exchanged between the boards.
<br/>
NOTE: The message to be exchanged between boards must be hardcoded directly into the code, as other methods of writing messages have not yet been implemented.

*Process for running the broker:*
1. Install Mosquitto;
2. Configure the Mosquitto password file to contain one or more users and passwords;
3. Configure the Mosquitto configuration file to only accept authenticated connections;
4. Change the broker IP in the code of this program to match the IP of the host PC;
5. Ensure the broker is running;
6. Build the program with the flag set to subscriber and proceed to flash the program onto one of the boards;
7. Build the program with the flag set to publisher and proceed to flash the program onto the second board;

### Our Conclusions

Which techniques are scalable?
<br/>
We noted that the MQTT authentication and communication techniques are quite scalable, as well as the encryption technique used, although the latter is highly insecure.
<br/><br/>
How to apply them with multiple BitDogLabs on a school network?
<br/>
The aforementioned techniques can be easily applied to a school network with several BitDogLabs, where some would act as publishers and others as subscribers, allowing them to interact with each other via a host broker. Furthermore, in a possible future version, it would be possible to implement real-time communication of events generated on the boards, as well as connection-oriented communication (between publisher and subscriber) at an application layer higher than MQTT.

---

## Bill of Materials (BOM): 

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                |

---

## Execution - Option 1

1. Open the project in VS Code, using an environment with Raspberry Pi Pico SDK support (CMake + ARM compiler);
2. Build the project normally (Ctrl+Shift+B in VS Code or via terminal with `cmake` and `make`);
3. Connect your BitDogLab via USB cable and put the Pico into boot mode (hold the BOOTSEL button while plugging in the cable);
4. Copy the generated `.uf2` file to the storage drive that appears (RPI-RP2);
5. The Pico will automatically reboot and start executing the code;
<br />
Tip: Use the Raspberry Pi Pico extension in VS Code to import the program as a Pico project, using SDK 2.1.0.

## Execution - Option 2

1. Create a build folder inside the root directory of this repository (`mkdir build`);
2. Enter the created folder (`cd build`);
3. Run cmake from within the created folder (`cmake ../CMakeLists.txt`);
4. Run the make command still inside the created folder (`make`);
5. Connect the board to the PC in boot/flashing mode;
6. Copy the `.uf2` file generated in the build folder during compilation to the board's drive.

---

## Files

- `iot_security_lab.c`: Main project code;
- `src/mqtt_comm.c`: MQTT library code used (over the toolkit);
- `src/wifi_conn.c`: WiFi library code used (over the toolkit);
- `src/xor_cipher.c`: XOR cipher library code used (over the toolkit);
- `include/mqtt_comm.h`: MQTT library .h file;
- `include/wifi_conn.h`: WiFi library .h file;
- `include/xor_cipher.h`: XOR cipher library .h file;

---

## 📜 License
GNU GPL-3.0.

---

# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autores: **Eduardo Tejada e Vinícius Esperança Mantovani**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, junho de 2025

---
## Sobre o Programa

Este programa implementa está dividido em duas funcionalidades, um publisher e um subscriber mqtt. A escolha entre funcionalidades é feita por meio de um define no código main. Essa multiplicidade de funcionalidades se dá para que seja possível executar uma comunicação entre duas placas BitDogLab por mqtt com um broker hospedado em um computador.
<br/>
Pontos de destaque para este projeto são o conhecimento adquirido a respeito de mqtt, autenticação e segurança em mqtt e, criptografia simples. Esse último ponto, pelo uso de um XOR para criptografar e descriptografar mensagens trocadas entre placas.
<br/>
OBS: a mensagem a ser trocada entre placas deve ser escrita diretamente no código, pois ainda não foram implementadas outras formas de escrita de mensagem.

*Processo para funcionamento do broker:*
1. Instalar o Mosquitto instalado;
2. Configurar o arquivo de senha do Mosquitto para conter um ou mais usuários ou senhar;
3. Configurar o arquivo de configuração do Mosquitto para somente aceitar conexões autenticadas;
4. Alterar o IP do broker no código deste programa para conter o IP do PC usado;
5. Garantir que o broker está operando;
6. Executar *build* do programa com flag setada para subscriber e seguir com o *flash* do programa em uma das placas;
7. Executar *build* do programa com flag setada para publisher e seguir com o *flash* do programa na segunda placa;

### Nossas conclusões

Quais técnicas são escaláveis?
<br/>
Notamos que a técnica de autenticação e comunicação por mqtt são bastante escaláveis, bem como a técnica de criptografia usada, embora esta seja pouquíssimo segura.
<br/><br/>
Como aplicá-las com várias BitDogLab em rede escolar?
<br/>
As técnicas mencionadas podem ser tranquilamente aplicadas a uma rede escolar com várias BitDogLab, de forma que algumas seriam publishers e outras subscribers, podendo elas, portanto, interagir entre si, por intermédio de um host broker. Além disso, em uma possível futura versão, seria possível implementar comunicação em tempo real de eventos gerados nas placas e, também, comunicação com orientação a conexão (entre publisher e subscriber) em camada de aplicação superior, ainda, à do mqtt.

---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                |

---

## Execução - Opção 1

1. Abra o projeto no VS Code, usando o ambiente com suporte ao SDK do Raspberry Pi Pico (CMake + compilador ARM);
2. Compile o projeto normalmente (Ctrl+Shift+B no VS Code ou via terminal com cmake e make);
3. Conecte sua BitDogLab via cabo USB e coloque a Pico no modo de boot (pressione o botão BOOTSEL e conecte o cabo);
4. Copie o arquivo .uf2 gerado para a unidade de armazenamento que aparece (RPI-RP2);
5. A Pico reiniciará automaticamente e começará a executar o código;
<br />
Sugestão: Use a extensão da Raspberry Pi Pico no VScode para importar o programa como projeto Pico, usando o sdk 2.1.0.

## Execução - Opção 2

1. Crie uma pasta build dentro da pasta raiz deste repositório (mkdir build);
2. Entre na pasta criada (cd build);
3. Execute cmake de dentro da pasta criada (cmake ../CMakeLists.txt);
4. Execute o comando make ainda dentro da pasta criada (make);
5. Conecte a placa ao PC em modo de gravação;
6. Copie o arquivo .uf2 gerado na pasta build durante a compilação para o disco da placa.

---

##  Arquivos

- `iot_security_lab.c`: Código principal do projeto;
- `src/mqtt_comm.c`: Código da biblioteca mqtt usada (sobre o toolkit);
- `src/wifi_conn.c`: Código da biblioteca wifi usada (sobre o toolkit);
- `src/xor_cipher.c`: Código da biblioteca xor usada (sobre o toolkit);
- `include/mqtt_comm.h`: .h da biblioteca do mqtt;
- `include/wifi_conn.h`: .h da biblioteca do wifi;
- `include/xor_cipher.h`: .h da biblioteca do xor;

---

## 📜 Licença
GNU GPL-3.0.
