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

## 🖼️ Imagens do Projeto

### Ainda não disponíveis
Projeto em curso, próximo da finalização

---

## 📹 Vídeos do Protótipo

- **Parte 1 - Lógica do Semáforo**: [YouTube](https://youtu.be/ATb_XiY7H3M)
- **Parte 2 - Conexão BLE**: [YouTube](https://youtube.com/shorts/KMRO6cxgSq0?feature=share)

---

## 📜 Licença
MIT License - MIT GPL-3.0.

---
