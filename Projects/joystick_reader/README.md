# Joystick Reader

This program implements a reader for the values measured by the ADC from the joystick located on the BitDogLab. In it, the OLED display shows the values read on the Y and X axes, respectively.
<br />

---

## Bill of Materials (BOM): 

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                         |
| I2C OLED Display      | SDA: GPIO14 / SCL: GPIO15 |
| Joystick              | GPIO 22 (pull-up), GPIOs 26 and 27 with ADC|

---

## Execution

1. Open the project in VS Code, using an environment with Raspberry Pi Pico SDK support (CMake + ARM compiler);
2. Build the project normally (Ctrl+Shift+B in VS Code or via terminal with `cmake` and `make`);
3. Connect your BitDogLab via USB cable and put the Pico into boot mode (hold the BOOTSEL button while plugging in the cable);
4. Copy the generated `.uf2` file to the storage drive that appears (RPI-RP2);
5. The Pico will automatically reboot and start executing the code;
<br />
Tip: Use the Raspberry Pi Pico extension in VS Code to import the program as a Pico project, using SDK 2.1.0.

---

## Files

- `src/TLMGame.c`: Main project code;
- `src/libraries/joystick.c`: .c file of the library for using the joystick with ADC;
- `src/libraries/joystick.h`: .h file of the library for using the joystick with ADC;
- `src/libraries/ssd1306_i2c.c`: I2C communication library .c file for the OLED display;
- `src/libraries/inc/ssd1306.h`: .h file with function definitions for the OLED display I2C communication library (this is included in the main code);
- `src/libraries/inc/ssd1306_font.h`: Main project code;
- `src/libraries/inc/ssd1306_i2c.h`: I2C communication library .h file for the OLED display with definitions and structures;

- `assets/joystick_demo.jpeg`: Image of the BitDogLab operating with the program;

---

## 🖼️ Project Images

### Joystick Reader:
<img src="./assets/joystick_demo.jpeg" width="400">

---

## 📜 License
MIT License - MIT GPL-3.0.

---

# Leitor de Joystick  

Este programa implementa um leitor de valores medidos pelo ADC receptor dos sinais do joystick disposto na BitDogLab.
Nele, o display OLED apresenta os valores lidos nos eixos Y e X, respectivamente.
<br />

---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                         |
| Display OLED I2C   | SDA: GPIO14 / SCL: GPIO15 |
| Joystick           | GPIO 22 (pull-up), GPIOs 26 e 27 com ADC|

---

## Execução

1. Abra o projeto no VS Code, usando o ambiente com suporte ao SDK do Raspberry Pi Pico (CMake + compilador ARM);
2. Compile o projeto normalmente (Ctrl+Shift+B no VS Code ou via terminal com cmake e make);
3. Conecte sua BitDogLab via cabo USB e coloque a Pico no modo de boot (pressione o botão BOOTSEL e conecte o cabo);
4. Copie o arquivo .uf2 gerado para a unidade de armazenamento que aparece (RPI-RP2);
5. A Pico reiniciará automaticamente e começará a executar o código;
<br />
Sugestão: Use a extensão da Raspberry Pi Pico no VScode para importar o programa como projeto Pico, usando o sdk 2.1.0.

---

##  Arquivos

- `src/TLMGame.c`: Código principal do projeto;
- `src/libraries/joystick.c`: .c da biblioteca para uso do joystick com ADC;
- `src/libraries/joystick.h`: .h da biblioteca para uso do joystick com ADC;
- `src/libraries/ssd1306_i2c.c`: .c da biblioteca de comunicação i2c com display OLED;
- `src/libraries/inc/ssd1306.h`: .h com definições de voids da biblioteca de comunicação i2c com display OLED (esta é incluida no código principal);
- `src/libraries/inc/ssd1306_font.h`: Código principal do projeto;
- `src/libraries/inc/ssd1306_i2c.h`: .h da biblioteca de comunicação i2c com display OLED com definições e estruturas;

- `assets/joystick_demo.jpeg`: Imagem da Bitdog operando com o programa;

---

## 🖼️ Imagens do Projeto

### Leitor de Joystick:
<img src="./assets/joystick_demo.jpeg" width="400">
---

## 📜 Licença
MIT License - MIT GPL-3.0.

---
