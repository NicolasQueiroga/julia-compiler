# Status dos testes

![git status](http://3.129.230.99/svg/NicolasQueiroga/my-logcomp)

---

# Instruções de execução
### Estrutura de pastas

```
.
├── README.md
├── CMakeLists.txt
├── bin
├── build
├── include
├── lib
└── src
```

- Os roteiros serão desenvolvidos na raiz do repositório, contendo os seguintes arquivos e pastas:
  - O arquívo `CMakeLists.txt` contém as instruções de *compilação* do projeto.
  - A pasta `src` conterá o arquivo fonte do projeto (`main.cpp`).
  - A pasta `build` conterá os arquivos gerados pelo `cmake`.
  - A pasta `bin` conterá o executável do projeto.
  - A pasta `lib` conterá as bibliotecas necessárias para o projeto.
  - A pasta `include` conterá os arquivos de cabeçalho necessários para o projeto.
  

### Passos para executar o projeto

- Para executar o projeto, é necessário ter o `cmake` instalado.
  - Para macOS, basta executar o seguinte comando:
  ```bash
  brew install cmake
  ```
  - Para Linux, basta executar o seguinte comando 
  ```bash
  sudo apt install cmake
  ```

- Dentro do diretorio do projeto `roteiroX`, basta seguir os seguintes passos:
```bash
mkdir build
cd build
cmake ..
make
../bin/main "1+1+2"
```
  
- Para remover os feedbacks que tanto o comando `cmake` quanto o comando `make` geram, basta executa-los do seguinte jeito:
```bash
cmake .. > /dev/null
make .. > /dev/null
../bin/main "1+1+2"
```
