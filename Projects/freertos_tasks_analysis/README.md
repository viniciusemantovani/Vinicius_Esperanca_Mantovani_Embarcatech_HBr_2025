# Embedded Systems Projects - EmbarcaTech 2025

Author: **Vinícius Esperança Mantovani**

Course: Embedded Systems Technological Residency

Institution: EmbarcaTech - HBr

Campinas, June 2025

---

# Task: FreeRTOS Guide #1 - EmbarcaTech 2025

This is a simple program using FreeRTOS, where the main LED of the BitDogLab periodically changes its color, while the buzzer, in parallel, emits sounds periodically. Finally, buttons A and B function, respectively, as a way to suspend the LED task (the LED freezes in its state at the moment of the press) and to suspend the Buzzer task, so that the Buzzer remains silenced if that was its state during the button press, or continues emitting sound if that was its state when pressed.

---

## Bill of Materials (BOM): 

| Component             | BitDogLab Connection         |
|-----------------------|------------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                   |
| Buttons (two)         | GPIOs 5 and 6 (pull-up)      |  
| Buzzer                | PWM: GPIO21                  |
| RGB LED               | GPIOs 11, 12 and 13 (output) |

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

- `src/main.c`: Main project code;
- `src/hal/buzzer_pwm.c`: Buzzer library .c file;
- `include/buzzer_pwm.h`: Buzzer library .h file;
- `include/FreeRTOSConfig.h`: Header file for FreeRTOS configuration;
  
---

## 🖼️ Project Image


---

## Reflection:

### What happens if all tasks have the same priority?

In FreeRTOS, when tasks have the same priority, they share equal CPU time when ready. In this case, there would be a possibility of a button click going unidentified because another task is executing at the exact moment of its press.

### Which task consumes the most CPU time?

The task that consumes the most time is the one with the highest priority.

### What would be the risks of using polling without priorities?

Allowing tasks that should be executed immediately—in the case of sensing and actuation, for example—to be delayed by another task that is using the CPU at that given moment.

---

## 📜 License
GNU GPL-3.0.

# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: **Vinícius Esperança Mantovani**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, Junho de 2025

---

# Tarefa: Roteiro de FreeRTOS #1 - EmbarcaTech 2025

Este é um programa simples usando FreeRTOS, no qual o LED principal da BitDogLab altera periodicamente sua cor, enquanto que o buzzer mantém-se, em paralelo a isso, emitindo sons periodicamente. Finalmente, tem-se os botões A e B funcionando, respectivamente, como formas de suspender a task do LED (LED congela como estava no momento do pressionamento) e, suspender a task do Buzzer, de modo que o Buzzer se mantém silenciado, caso este fosse seu estado durante o pressionamento do botão ou, emitindo som, caso este fosse o estado no pressionamento.

---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                |
| Botões (dois)      | GPIOs 5 e 6 (pull-up)        |  
| Buzzer             | PWM: GPIO21                  |
| LED RGB            | GPIOs 11, 12 e 13 (output)   |
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

- Preencha o caminho para o folder da RP Pi Pico (em "mount_point=$(find -maxdepth 1 -type d -name "RPI-RP*" | head -n 1)")
- Execute o script compile_flash (./compile_flash)

---

##  Arquivos

- `src//main.c`: Código principal do projeto;
- `src/hal/buzzer_pwm.c`: .c da biblioteca do Buzzer;
- `include/buzzer_pwm.h`: .h da biblioteca do Buzzer;
- `include/FreeRTOSConfig.h`: .h header para configuração do FreeRTOS;
  
---

## 🖼️ Imagem do projeto


---

## Reflexão:

### O que acontece se todas as tasks tiverem a mesma prioridade?

No FreeRTOS, quando as tarefas têm a mesma prioridade, têm tempos iguais de CPU quanto prontas. Nesse caso, haveria a possibilidade de o clique de um botão não ser identificado por conta de outra tarefa estar sendo executada no momento de seu pressionamento.

### Qual tarefa consome mais tempo da CPU?

A tarefa que consome mais tempo é aquela de maior prioridade.

### Quais seriam os riscos de usar polling sem prioridades?

Permitir que tarefas que deveriam ser executadas imediatamente no caso de sensoriamento e atuação, por exemplo, fossem retardadas por outra tarefa que usa a CPU nesse determinado momento.

---

## 📜 Licença
GNU GPL-3.0.
