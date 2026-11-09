# Simulador Artemis — Grupo Codex

Trabajo Final Integrador de Algoritmos y Estructuras de Datos — UTN Facultad Regional Resistencia.  
**Escenario 1: Ascenso y propulsión del SLS.**

## 1. Integrantes y comisión

**Comisión:** K 1.3

| Integrante | Legajo |
|---|---|
| [macarena Jazmin calderon] | [28023] |
| Lucio Tomás Binaghi | 28436 |
| [Tomas Misael Alcorta] | [28391] |
| [Guadalupe  Denise Mac Lachlan] | [28483] |
| [Elias Ezequiel Bentolila] | [28363] |

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

| Consulta o tarea | Uso de la IA | Cómo se comprobó |
|---|---|---|
| Desarrollar el escenario 1 en C a partir de la consigna. | Generación de la versión inicial, organización de los módulos y aplicación de las fórmulas físicas. | Compilación con GCC y comparación de los resultados con las ecuaciones del escenario. |
| Mostrar las preguntas antes de sus respuestas y agregar el nombre del grupo. | Ajuste del menú y de la presentación de los resultados. | Ejecución del programa y revisión de la opción 4. |
| Revisar errores y probar la simulación. | Preparación de pruebas de física, validación e historial. | Ejecución de las pruebas en C y contraste de 60 misiones con parámetros variados: 30 nominales y 30 con fallo. |
| Resolver problemas de compilación y preparar la entrega. | Revisión de los comandos de GCC, organización de archivos y redacción del README. | Verificación de los comandos y de los archivos incluidos en el proyecto. |
