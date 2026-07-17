# Galton Board

This program implements a digital twin of the Galton Board experiment.

---

## Bill of Materials (BOM): 

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                         |
| I2C OLED Display      | SDA: GPIO14 / SCL: GPIO15 |
| Buttons (two)         | GPIOs 5 and 6 (pull-up)   |

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

- `src/app/main.c`: Main project code;
- `src/hal/ssd1306.c`: OLED library .c file;
- `include/ssd1306.h`: OLED library .h file;
- `include/fonts/font.h`: Font .h file used by the OLED library;

- `assets/galton_board_operante.jpeg`: Galton Board in operation;
---

## 🖼️ Project Images

### BitDogLab operating the Galton Board:
<img src="./assets/galton_board_operante.jpeg" width="400">

---

## 📜 License
MIT License - MIT GPL-3.0.

---

# Galton Board

Este programa implementa um digital twin do experimento Galton Board.

---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                         |
| Display OLED I2C   | SDA: GPIO14 / SCL: GPIO15 |
| Botões (dois)      | GPIOs 5 e 6 (pull-up)|

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

- `src/app/main.c`: Código principal do projeto;
- `src/hal/ssd1306.c`: .c da biblioteca do OLED;
- `include/ssd1306.h`: .h da biblioteca do OLED;
- `include/fonts/font.h`: .h da fonte usada pela biblioteca do OLED;

- `assets/galton_board_operante.jpeg`: Galton Board funcionando;
---

## 🖼️ Imagens do Projeto

### BitDogLab operando Galton Board:
<img src="./assets/galton_board_operante.jpeg" width="400">

---

## 📜 Licença
MIT License - MIT GPL-3.0.

---
