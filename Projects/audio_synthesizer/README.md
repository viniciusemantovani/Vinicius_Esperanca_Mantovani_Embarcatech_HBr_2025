# Embedded Systems Projects - EmbarcaTech 2025 - English

Author: **Vinícius Esperança Mantovani**

Course: Embedded Systems Technological Residency

Institution: EmbarcaTech - HBr

Campinas, June 2025

---

# Audio Synthesizer

This program implements a 3-second audio capture and playback system. To achieve this, it uses a GY-MAX4466 microphone, two passive buzzers, and two buttons.

How to use:
- Pressing "A" starts a recording;
- Pressing "B" starts playback;

The main RGB LED on the BitDogLab indicates whether the system is recording audio (red), playing back (green), or in standby (off).
The display shows bars with sizes proportional to the microphone's ADC readings. Thus, each audio reading is represented as a bar.

---

## Bill of Materials (BOM): 

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                |
| I2C OLED Display      | SDA: GPIO14 / SCL: GPIO15 |
| Buttons (two)         | GPIOs 5 and 6 (pull-up)   |  
| Microphone            | ADC: GPIO28               |

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
   
## Execution - Option 3

Automated method! LINUX ONLY!

- Fill in the path to the RP Pi Pico folder (in `mount_point=$(find <Path to rp pi pico folder> -maxdepth 1 -type d -name "RPI-RP*" | head -n 1)`)
- Run the compile_flash script (`./compile_flash`)

---

## Files

- `src/app/main.c`: Main project code;
- `src/hal/ssd1306.c`: OLED library .c file;
- `src/hal/buzzer_pwm1.c`: Buzzer library .c file;
- `src/hal/led_rgb.c`: RGB LED library .c file;
- `src/hal/microphone_dma.c`: Microphone library .c file;
- `include/ssd1306.h`: OLED library .h file;
- `include/fonts/font.h`: Font .h file used by the OLED library;
- `include/buzzer_pwm1.h`: Buzzer library .h file;
- `include/led_rgb.h`: RGB LED library .h file;
- `include/microphone_dma.h`: Microphone library .h file;

---

## 🖼️ Project Video

Available at:
[https://youtu.be/w-MWRK55lzM]

---

## 📜 License
GNU GPL-3.0.

---

# Projetos de Sistemas Embarcados - EmbarcaTech 2025 - Português

Autor: **Vinícius Esperança Mantovani**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, Junho de 2025

---

# Sintetizador de áudio

Este programa implementa um sistema de captura e reprodução de áudios de três segundos. Para tanto, faz uso de um microfone GY-MAX4466, dois buzzers passivos e dois botões.
Como usar:
- Pressionando "A", pode-se iniciar uma gravação;
- Pressionando "B", pode-se iniciar uma reprodução;
O Led RGB principal da BitDogLab indica se o sistema está gravando áudio (vermelho), reproduzindo (verde) ou em espera (apagado).
Já o display, apresenta barras com tamanhos proporcionais às leituras do ADC do microfone. Isso se faz, de forma que cada áudio é apresentado como uma barra.

---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                |
| Display OLED I2C   | SDA: GPIO14 / SCL: GPIO15    |
| Botões (dois)      | GPIOs 5 e 6 (pull-up)        |  
| Microfone          | ADC: GPIO28                  |
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
   
## Execução - Opção 3

Método automatizado! SOMENTE NO LINUX!

- Preencha o caminho para o folder da RP Pi Pico (em "mount_point=$(find <Path to rp pi pico folder> -maxdepth 1 -type d -name "RPI-RP*" | head -n 1)")
- Execute o script compile_flash (./compile_flash)

---

##  Arquivos

- `src/app/main.c`: Código principal do projeto;
- `src/hal/ssd1306.c`: .c da biblioteca do OLED;
- `src/hal/buzzer_pwm1.c`: .c da biblioteca do buzzer;
- `src/hal/led_rgb.c`: .c da biblioteca do LED RGB;
- `src/hal/microphone_dma.c`: .c da biblioteca do microphone;
- `include/ssd1306.h`: .h da biblioteca do OLED;
- `include/fonts/font.h`: .h da fonte usada pela biblioteca do OLED;
- `include/buzzer_pwm1.h`: .h da biblioteca do buzzer;
- `include/led_rgb.h`: .h da biblioteca do LED RGB;
- `include/microphone_dma.h`: .h da biblioteca do microphone;

---

## 🖼️ Vídeo do projeto

Disponível em:
[https://youtu.be/w-MWRK55lzM]

---

## 📜 Licença
GNU GPL-3.0.

