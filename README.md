# C-Codes - Bibliotecas e Jogos em C

[🇧🇷 Português](#-português) | [🇺🇸 English](#-english)

---

## 🇧🇷 Português

Desenvolvido por **João Lucas Mayrinck**, Bacharel em Sistemas de Informação pela Universidade Federal de Viçosa (UFV). Este projeto reúne implementações manuais de funções matemáticas, manipuladores de string e jogos clássicos, focando em lógica pura sem a necessidade de dependências externas complexas.

A ideia central da biblioteca é reinventar a roda (no bom sentido acadêmico), implementando cálculos de precisão, raízes e logaritmos na "força bruta" e lógica matemática pura, em vez de depender das bibliotecas `<math.h>` e `<string.h>` do C.

### 🌐 Site do Projeto (Jogue Online)

Explore a [página oficial do projeto no GitHub Pages](https://jluckmay.github.io/C-Codes/)! Nela, você pode:
- Consultar a documentação completa das funções e bibliotecas.
- **Jogar no navegador:** Os jogos (como o Jogo dos 21 Palitos) foram reescritos em JavaScript para que você possa testar a lógica da IA diretamente pela web, sem precisar compilar nada.
- Baixar os arquivos do projeto.
- Alternar facilmente entre os temas Claro/Escuro e idiomas (Português/Inglês).

### 🚀 Funcionalidades

A biblioteca original foi refatorada e dividida em módulos para melhor desempenho e organização:

- **`math_f.h`**: Lógica aritmética. Inclui funções como potência (`pot`), raízes com precisão de 0.000001 (`raiz`), logaritmos (`log_f`), fatoriais e arredondamentos.
- **`morse_f.h`**: Conversor de Código Morse otimizado. Substitui cadeias massivas de `if/else` por uma *Lookup Table* estática, garantindo traduções rápidas e eficientes de texto para Morse (`atom`) e Morse para texto (`mtoa`).
- **`string_f.h`**: Manipulação de textos e arrays de caracteres. Implementações próprias de conversão de bases numéricas (`bin`, `itob`, `btoi`), além de conversões numéricas clássicas (`itoa`, `ftoa`).
- **`system_f.h`**: Utilitários do sistema. Funções para lidar com manipulação de arquivos, datas reconstruídas a partir do *Unix Timestamp* (`temp`), limpeza de tela cross-platform e interações no terminal.

### 📋 Pré-requisitos

Para compilar e instalar o projeto no seu computador, você precisa ter o compilador **GCC** e a ferramenta **Make** instalados no seu sistema operacional:

- **Linux (Ubuntu/Debian):**
  Abra o terminal e instale o pacote essencial de build:
  
    sudo apt update && sudo apt install build-essential

- **macOS:**
  Abra o terminal e instale as ferramentas de linha de comando da Apple:
  
    xcode-select --install

- **Windows:**
  Recomendamos instalar o GCC e o Make através do [MSYS2](https://www.msys2.org/). Baixe o instalador pelo site e siga as instruções para instalar o pacote `mingw-w64-gcc` e `make`.

### 🛠️ Instalação Global

Você pode instalar as bibliotecas no diretório nativo do seu sistema operacional e adicionar os jogos diretamente ao seu PATH. Isso permite usar os arquivos em qualquer projeto futuro e rodar os jogos de qualquer lugar.

**Passo 1:** Abra o terminal na pasta raiz do projeto e compile os arquivos executando o Makefile:

    make

**Passo 2:** Execute o script de instalação correspondente ao seu sistema operacional:

- **Linux e macOS:**

    chmod +x install.sh
    ./install.sh

- **Windows:**
  Basta dar um duplo clique no arquivo `install.bat` ou executá-lo pelo Prompt de Comando:

    install.bat

**Uso Global em seus Projetos:**
Após a instalação, você pode compilar qualquer projeto pessoal C avisando o compilador padrão:

    gcc meu_programa.c -o meu_programa

*Obs para Windows:* Lembre-se de adicionar a flag `-I C:\C-Codes\include` na compilação, conforme instruído pelo `install.bat`.

Desde que você inclua o agregador principal no topo do seu código C:

    #include <more_f.h>

### ⚙️ Compilação Local 

Caso você não queira instalar o projeto globalmente no seu sistema, execute apenas o comando `make` na pasta raiz.
Isso irá compilar todos os arquivos `.c` e gerar os executáveis (`campominado`, `21palitos` e `conversormorse`) apenas na sua pasta atual. Para apagar os executáveis gerados, basta rodar `make clean`.

### 🎮 Jogos Inclusos

O projeto inclui jogos executáveis diretamente no terminal. Se você realizou a instalação global, basta digitar os comandos abaixo de qualquer diretório (ou usar `./nome_do_jogo` se compilou apenas localmente):

- `campominado` : Jogo clássico de Campo Minado, com implementação de "Flood Fill" recursivo e sistema de records em arquivo texto.
- `21palitos` : Desafie o computador no Jogo dos 21 Palitos, que conta com uma IA matemática programada para (quase) sempre vencer.
- `conversormorse` : Ferramenta interativa de linha de comando para codificar e decodificar mensagens em Código Morse.

### 📧 Contato
Desenvolvedor: João Lucas Mayrinck  
Email: joao-d@ufmg.br

---

## 🇺🇸 English

Developed by **João Lucas Mayrinck**, Information Systems Bachelor by the Federal University of Viçosa (UFV). This project brings together manual implementations of mathematical functions, string manipulators, and classic games, focusing on pure logic without the need for complex external dependencies.

The core idea of the library is to "reinvent the wheel" (in a good, academic way), implementing precision calculations, roots, and logarithms through "brute force" and pure mathematical logic, rather than relying on C's standard `<math.h>` and `<string.h>` libraries.

### 🌐 Project Website (Play Online)

Explore the [official project page on GitHub Pages](https://jluckmay.github.io/C-Codes/)! There, you can:
- Check out the full documentation of functions and libraries.
- **Play in your browser:** The games (like the 21 Sticks Game) have been rewritten in JavaScript so you can test the AI logic directly online, without needing to compile anything.
- Download project files.
- Easily toggle between Light/Dark themes and languages (Portuguese/English).

### 🚀 Features

The original library was refactored and divided into modules for better performance and organization:

- **`math_f.h`**: Arithmetic logic. Includes functions such as power (`pot`), roots with 0.000001 precision (`raiz`), logarithms (`log_f`), factorials, and rounding.
- **`morse_f.h`**: Optimized Morse Code converter. Replaces massive `if/else` chains with a static *Lookup Table*, ensuring fast and efficient translations from text to Morse (`atom`) and Morse to text (`mtoa`).
- **`string_f.h`**: Text and character array manipulation. Custom implementations of numeric base conversions (`bin`, `itob`, `btoi`), as well as classic numeric conversions (`itoa`, `ftoa`).
- **`system_f.h`**: System utilities. Functions for handling file manipulation, dates reconstructed from *Unix Timestamps* (`temp`), cross-platform screen clearing, and terminal interactions.

### 📋 Prerequisites

To compile and install the project on your computer, you must have the **GCC** compiler and the **Make** tool installed on your operating system:

- **Linux (Ubuntu/Debian):**
  Open the terminal and install the essential build package:
  
    sudo apt update && sudo apt install build-essential

- **macOS:**
  Open the terminal and install the Apple command line tools:
  
    xcode-select --install

- **Windows:**
  We recommend installing GCC and Make through [MSYS2](https://www.msys2.org/). Download the installer from the website and follow the instructions to install the `mingw-w64-gcc` and `make` packages.

### 🛠️ Global Installation

You can install the libraries in your OS's native directory and add the games directly to your PATH. This allows you to use the files in any future project and run games from anywhere.

**Step 1:** Open the terminal in the root folder of the project and compile the files by running the Makefile:

    make

**Step 2:** Run the installation script corresponding to your operating system:

- **Linux and macOS:**

    chmod +x install.sh
    ./install.sh

- **Windows:**
  Just double-click the `install.bat` file or run it via the Command Prompt:

    install.bat

**Global Usage in your Projects:**
After installation, you can compile any personal C project using the standard compiler:

    gcc my_program.c -o my_program

*Note for Windows:* Remember to add the `-I C:\C-Codes\include` flag when compiling, as instructed by the `install.bat` output.

As long as you include the main aggregator at the top of your C code:

    #include <more_f.h>

### ⚙️ Local Compilation 

If you prefer not to install the project system-wide, simply execute the `make` command in the root folder.
This will compile all `.c` files and generate the executables (`campominado`, `21palitos`, and `conversormorse`) only in your current directory. To clean up the generated executables, simply run `make clean`.

### 🎮 Included Games

The project includes games that are executable directly in the terminal. If you performed the global installation above, just type the commands below from any directory (or use `./game_name` if you compiled only locally):

- `campominado` : Classic Minesweeper game, featuring recursive "Flood Fill" implementation and a text file high-score system.
- `21palitos` : Challenge the computer in the 21 Sticks Game, featuring a mathematical AI programmed to (almost) always win.
- `conversormorse` : Interactive command-line tool to encode and decode messages in Morse Code.

### 📧 Contact
Developer: João Lucas Mayrinck  
Email: joao-d@ufmg.br