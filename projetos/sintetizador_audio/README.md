
# Projetos de Sistemas Embarcados - EmbarcaTech 2025

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

