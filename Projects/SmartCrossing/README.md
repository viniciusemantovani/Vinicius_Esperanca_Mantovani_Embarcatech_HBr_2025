# Smart Crossing

This project implements a smart traffic light controller for pedestrian crosswalks, featuring a sensor to detect people waiting to cross. In this sense, it aims to serve everyone, containing an inclusion feature for people with disabilities who may need more time to cross. This feature is implemented via Bluetooth communication between the RP Pi Pico W boards and the smartphones of individuals requiring special accommodations. Furthermore, the system implements detection at both ends of the crosswalk, ensuring that pedestrians are always identified and served by the traffic light.

---

## Bill of Materials (BOM): 

| Component             | BitDogLab Connection      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                         |
| I2C OLED Display      | SDA: GPIO14 / SCL: GPIO15 |
| 5x5 WS2812B Matrix    | GPIO 7 with PIO configuration |

---

## Execution

To compile and flash this project, you can use the `build_flash.sh` script on Linux. However, on Windows, direct compilation with CMake and Make is still required.

Steps for compilation and flashing with CMake:
- Download the pico-sdk (clone from the GitHub page);
- Export the path with `export PICO_SDK_PATH=/path/to/pico-sdk`;
- Create a `build` folder in the project repository;
- In the terminal, access the folder with `cd build`;
- Run `cmake ..`;
- Run `make`;
- Copy the `.uf2` file to the Pi Pico directory.

---

## 📹 Prototype Videos

- **Part 1 - Traffic Light Logic**: [YouTube](https://youtu.be/ATb_XiY7H3M)
- **Part 2 - BLE Connection**: [YouTube](https://youtube.com/shorts/KMRO6cxgSq0?feature=share)

---

## 📜 License
MIT License - MIT GPL-3.0.

---

# Smart Crossing

Este projeto implementa um controlador inteligente de semáforos em faixas de pedestre, com sensor para detecção de pessoas no aguardo por atravessar. Nesse sentido, visa a atender a todas as pessoas, contendo feature de 
inclusão para pessoas com debilitações que necessitem de mais tempo para travessia. Essa feature é implementada por meio da comunicação bluetooth entre as placas RP PI Pico W e os celulares dos indivíduos que necessitem de tratamento especial. Além disso, o sistema implementa detecção em ambas as pontas da faixa de pedestre, permitindo que os pedestres sejam sempre identificados e atendidos pelo semáforo.

---

##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (Pi Pico W - RP2040) | -                |
| Display OLED I2C   | SDA: GPIO14 / SCL: GPIO15 |
| Matriz WS2812B 5x5 | GPIO 7 com configuração PIO |

---

## Execução

Para compilar e gravar este projeto, pode-se usar o script "build_flash.sh" no linux. No entanto, no Windows, é necessário, ainda a compilação diretamente com CMake e Make.

Passos para compilação e gravação com CMake:
- Baixe o pico-sdk (clone da página do github);
- exporte o caminho com "export PICO_SDK_PATH=/caminho/para/pico-sdk";
- Crie uma pasta "build" no repositório do projeto;
- No terminal, acesse a pasta "cd build";
- Execute "cmake ..";
- Execute "make";
- Copie o ".uf2" para o diretório da Pi Pico.

---

## 📹 Vídeos do Protótipo

- **Parte 1 - Lógica do Semáforo**: [YouTube](https://youtu.be/ATb_XiY7H3M)
- **Parte 2 - Conexão BLE**: [YouTube](https://youtube.com/shorts/KMRO6cxgSq0?feature=share)

---

## 📜 Licença
MIT License - MIT GPL-3.0.

---
