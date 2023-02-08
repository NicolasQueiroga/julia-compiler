# Status dos testes

![git status](http://3.129.230.99/svg/NicolasQueiroga/my-logcomp)

---

# Instruções de execução


```
.
├── README.md
├── CMakeLists.txt
├── bin
├── build
└── src
```
### Estrutura de pastas
- Os roteiros serão desenvolvidos em pastas com o nome do roteiro, por exemplo, o roteiro 0 será desenvolvido na pasta `roteiro0`, contendo os seguintes arquivos e pastas:
  - O arquívo `CMakeLists.txt` contém as instruções de *compilação* do projeto.
  - A pasta `src` conterá o arquivo fonte do projeto (`main.cpp`).
  - A pasta `build` conterá os arquivos gerados pelo `cmake`.
  - A pasta `bin` conterá o executável do projeto.
  - A pasta `libs` conterá as bibliotecas necessárias para o projeto.
  - A pasta `include` conterá os arquivos de cabeçalho necessários para o projeto.
  

### Passos para executar o projeto

- Para executar o projeto, é necessário ter o `cmake` instalado.
  - Para macOS, basta executar o comando `brew install cmake`.
  - Para Linux, basta executar o comando `sudo apt install cmake`.

- Dentro do diretorio do projeto `roteiroX`, basta seguir os seguintes passos:
  - `mkdir build`
  - `cd build`
  - `cmake ..`
  - `make`
  - `../bin/main`
  

