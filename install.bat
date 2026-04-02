@echo off
echo =======================================
echo Instalador C-Codes para Windows
echo =======================================

:: Define as pastas de destino
set DEST_DIR=C:\C-Codes
set DEST_BIN=%DEST_DIR%\bin
set DEST_INC=%DEST_DIR%\include

:: Cria as pastas se não existirem
echo Criando diretorios em %DEST_DIR%...
if not exist "%DEST_BIN%" mkdir "%DEST_BIN%"
if not exist "%DEST_INC%" mkdir "%DEST_INC%"

:: Compila os jogos direto para a pasta bin
echo Compilando os jogos...
gcc "Jogos\CampoMinado.c" -o "%DEST_BIN%\campominado.exe"
gcc "Jogos\VintiumPalitusGame.c" -o "%DEST_BIN%\21palitos.exe"
gcc "Programas\CConversorDeCodigoMorse.c" -o "%DEST_BIN%\conversormorse.exe"

:: Copia as bibliotecas para a pasta include
echo Copiando bibliotecas...
copy "Biblioteca\*_f.h" "%DEST_INC%\" >nul

:: Adiciona a pasta bin ao PATH do Usuario usando PowerShell (Sem precisar de Admin)
echo Configurando variaveis de ambiente (PATH)...
powershell -Command "$userPath = [Environment]::GetEnvironmentVariable('Path', 'User'); if ($userPath -notmatch [regex]::Escape('%DEST_BIN%')) { [Environment]::SetEnvironmentVariable('Path', $userPath + ';%DEST_BIN%', 'User'); Write-Host 'Pasta bin adicionada ao PATH do usuario com sucesso!' } else { Write-Host 'A pasta bin ja estava no PATH.' }"

echo =======================================
echo Instalacao concluida com sucesso!
echo =======================================
echo.
echo IMPORTANTE: Feche este terminal e abra um novo para que o PATH atualizado seja carregado.
echo.
echo COMANDOS GLOBAIS DISPONIVEIS AGORA:
echo - campominado
echo - 21palitos
echo - conversormorse
echo.
echo PARA USAR AS BIBLIOTECAS NOS SEUS PROJETOS C:
echo Ao compilar, avise o GCC onde elas estao usando a flag -I:
echo gcc seu_codigo.c -I C:\C-Codes\include -o seu_programa.exe
echo.
pause