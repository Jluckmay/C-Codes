#!/bin/bash

# 1. Compilar os jogos usando o Makefile
echo "Compilando programas..."
make

# 2. Instalar as Bibliotecas (_f.h) no diretório de include do sistema
echo "Instalando bibliotecas em /usr/local/include..."
sudo cp Biblioteca/*_f.h /usr/local/include/

# 3. Instalar os Executáveis no PATH
echo "Instalando jogos em /usr/local/bin..."
sudo mv campominado 21palitos conversormorse /usr/local/bin/

echo "Instalação concluída com sucesso!"
echo "Agora você pode usar #include <more_f.h> e rodar os jogos pelo terminal."