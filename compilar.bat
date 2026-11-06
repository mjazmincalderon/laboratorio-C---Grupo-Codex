@echo off
setlocal
cd /d "%~dp0"
where gcc >nul 2>nul
if errorlevel 1 (
    echo No se encontro GCC. Agregue el compilador de MinGW o MSYS2 al PATH.
    exit /b 1
)
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 main.c artemis.c validaciones.c -o artemis.exe -lm
if errorlevel 1 exit /b 1
echo Compilacion correcta. Ejecute artemis.exe
