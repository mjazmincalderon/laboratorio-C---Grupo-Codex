# Simulador Artemis — Grupo Codex

Trabajo Final Integrador de Algoritmos y Estructuras de Datos — UTN Facultad Regional Resistencia.  
**Escenario 1: Ascenso y propulsión del SLS.**

## 1. Integrantes y comisión

**Comisión:** [Completar]

| Integrante | Legajo |
|---|---|
| [Nombre y apellido] | [Legajo] |
| [Nombre y apellido] | [Legajo] |
| [Nombre y apellido] | [Legajo] |
| [Nombre y apellido] | [Legajo] |
| [Nombre y apellido] | [Legajo] |

## 2. Escenario y reglas

El simulador representa el ascenso vertical del cohete SLS con la nave Orion. Parte del reposo y acelera a **20 m/s²** hasta el desacople de los propulsores sólidos (SRB), a los **120 s**. Luego sigue con una aceleración de **12,5 m/s²** hasta el apagado de motores, a **160 000 m** de altura.

En el **modo nominal**, la simulación termina al apagar los motores. En el **modo de fallo**, la nave sigue subiendo por inercia hasta que su velocidad llega a cero en el apogeo. Se usa un modelo de MRUV, con gravedad constante de **9,8 m/s²** y sin resistencia del aire.

Desde el menú se pueden cambiar los parámetros, consultar las respuestas de la consigna, iniciar una misión y ver o exportar el historial. Durante la misión, **1** avanza un turno, **2** la completa automáticamente y **0** la interrumpe. Cada turno se detiene si alcanza un evento, como el desacople, el apagado o el apogeo.

## 3. Funcionamiento

El simulador está escrito en **C** y funciona por consola. Está dividido en los siguientes archivos:

| Archivo | Función |
|---|---|
| `main.c` | Muestra el menú y coordina las opciones del programa. |
| `artemis.h` | Define constantes, estructuras, fases y prototipos de la simulación. |
| `artemis.c` | Realiza los cálculos físicos, actualiza el estado de la nave y genera los reportes y el CSV. |
| `validaciones.h` y `validaciones.c` | Declaran e implementan la lectura segura de enteros, reales y caracteres. |
| `tests/pruebas.c` | Comprueba resultados físicos, cambios de fase y límites del historial. |

La simulación guarda la configuración, los resultados y el estado actual en estructuras. En cada turno actualiza el tiempo, la altura, la velocidad y la fase. Un arreglo almacena los estados de la misión para poder consultarlos o exportarlos después. Las funciones de validación rechazan entradas incorrectas y permiten volver a intentarlo.

## 4. Compilación y ejecución

Se necesita **GCC**. Abrir una terminal en la carpeta que contiene `main.c`.

**Windows — Git Bash:**

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c artemis.c validaciones.c -o artemis.exe -lm
./artemis.exe
```

**Windows — PowerShell:** también se puede usar el script incluido.

```powershell
.\compilar.bat
.\artemis.exe
```

**Linux o macOS con GCC:**

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c artemis.c validaciones.c -o artemis -lm
./artemis
```

Para ejecutar las pruebas con GNU Make, usar `make test`.

## 5. Registro de uso de inteligencia artificial

**Herramienta utilizada:** Codex de OpenAI.

| Consulta | Uso de la IA | Cómo se verificó |
|---|---|---|
| Desarrollar el escenario 1 de Artemis en C. | Generación de la versión inicial del simulador, organización en módulos y ajustes del menú y los resultados. | Se compiló con GCC y se compararon los resultados con las fórmulas del escenario. |
| Revisar el programa y preparar la entrega. | Ayuda para crear pruebas en C y redactar el README. | Se ejecutaron las pruebas y se comprobaron las instrucciones de compilación y ejecución. |

