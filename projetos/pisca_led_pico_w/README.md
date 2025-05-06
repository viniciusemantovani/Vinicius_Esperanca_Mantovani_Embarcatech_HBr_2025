# Pisca Led Modular

Este programa implementa um pisca led na Raspberry Pi Pico W, em seu led embutido ligado ao módulo WiFi.
A ideia neste projeto foi desenvolver o conhecimento e a habilidade de programação modular, conforme se pode notar pela organização dos arquivos.
---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| Pi Pico W - RP2040) | -                         |

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
- `src/drivers/led_embutido.c`: .c da camada de driver;
- `src/hal/hal_led.c`: .c da camada de hal;
- `src/include/hal_led.h`: .h da camada de hal;
- `src/include/led_embutido.h`: .h da camada de driver;

- `assets/pico_led_blink.jpeg`: Programa operante;
  
---

## 🖼️ Imagens do Projeto

### Led embutido da Pi Pico W piscando:
<img src="./assets/pico_led_blink.jpeg" width="400">

---

## 📜 Licença
MIT License - MIT GPL-3.0.

---
