## 📹 Vídeos do Protótipo

- **Parte 1 - Lógica do Semáforo**: [YouTube](https://youtu.be/ATb_XiY7H3M)
- **Parte 2 - Conexão BLE**: [YouTube Shorts](https://youtube.com/shorts/KMRO6cxgSq0?feature=share)

## Compilação

Para compilar e gravar este projeto, pode-se usar o script "build_flash.sh" no linux. No entanto, no Windows, é necessário, ainda a compilação diretamente com CMake e Make.

Passos para compilação e gravação com CMake:
- Crie uma pasta "build" no repositório do projeto;
- No terminal, acesse a pasta "cd build";
- Execute "cmake ..";
- Execute "make";
- Copie o ".uf2" para o diretório da Pi Pico.
