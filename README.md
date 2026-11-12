# Simulador Artemis — Grupo Codex
video: https://youtu.be/4GgxDYfJm_E
Trabajo Integrador de Algoritmos y Estructuras de Datos — UTN Facultad Regional Resistencia.  
**Escenario 1: Ascenso y propulsión del SLS.**

## 1. Integrantes y comisión

**Comisión:** K 1.3

| Integrante | Legajo |
|---|---|
| Macarena Jazmin Calderon | [28023] |
| Lucio Tomás Binaghi | [28436] |
| Tomas Misael Alcorta | [28391] |
| Guadalupe  Denise Mac Lachlan | [28483] |
| Elias Ezequiel Bentolila | [28363] |

## 2. Escenario y reglas

El simulador representa el ascenso vertical del cohete SLS con la nave Orion. Parte del reposo y acelera a **20 m/s²** hasta el desacople de los propulsores sólidos (SRB), a los **120 s**. Luego sigue con una aceleración de **12,5 m/s²** hasta el apagado de motores, a **160 000 m** de altura.

En el **modo nominal**, la simulación termina al apagar los motores. En el **modo de fallo**, la nave sigue subiendo por inercia hasta que su velocidad llega a cero en el apogeo. Se usa un modelo de MRUV, con gravedad constante de **9,8 m/s²** y sin resistencia del aire.

### Reglas de la simulación

- Desde el menú se pueden consultar, modificar o restaurar los parámetros, ver las respuestas de la consigna e iniciar una misión nominal o con fallo.
- Durante la misión, **1** avanza un turno, **2** completa la simulación automáticamente y **0** la interrumpe.
- El paso inicial es de **10 segundos**. Si el desacople, el apagado o el apogeo ocurre antes de que termine el turno, la simulación se detiene en ese evento.
- Los parámetros se ingresan en unidades del Sistema Internacional. La altura de apagado debe ser mayor que la altura alcanzada en el desacople.
- Después de una misión se puede consultar el reporte y exportar a `historial.csv` el tiempo, la altura, la velocidad y la fase registrados.

## 3. Funcionamiento

El programa está escrito en **C** y se ejecuta por consola. Al iniciarse, carga los valores de la consigna y muestra el menú principal. Desde ahí se pueden cambiar los parámetros, consultar los resultados de los cálculos o iniciar una misión.

El código se divide en módulos:

- `main.c`: muestra el menú, lee la opción elegida y llama a la función correspondiente.
- `artemis.h`: declara las estructuras que guardan la configuración, los resultados y el estado de la nave. También define las fases de vuelo.
- `artemis.c`: calcula el movimiento, ejecuta los turnos y genera los reportes y el archivo CSV.
- `validaciones.c` y `validaciones.h`: controlan que las entradas sean del tipo esperado y estén dentro de los rangos permitidos. Si un dato es inválido, se muestra un mensaje y se pide ingresarlo de nuevo.
- `tests/pruebas.c`: comprueba los cálculos, los cambios de fase y los límites del historial.

Al iniciar una misión, el programa calcula cuándo ocurren el desacople, el apagado y, si corresponde, el apogeo. En cada turno actualiza el **tiempo, la altura, la velocidad y la fase** con las fórmulas de movimiento. Si el turno alcanza un cambio de fase, se acorta para terminar justo en ese evento. El turno siguiente continúa desde la altura y la velocidad alcanzadas, con la aceleración de la nueva fase.

Los estados de la última misión se guardan en un arreglo. Al terminar o interrumpir la simulación, el programa muestra un reporte con los parámetros usados, el estado final y los resultados calculados. El historial se puede consultar desde el menú o exportar a `historial.csv`.

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
| Calcular la velocidad al desacople y la altura máxima en vuelo libre. | Se usó para generar una primera versión del simulador, que incluía la implementación de estas fórmulas en C. | Se compiló con GCC y se compararon los resultados con las fórmulas de MRUV y vuelo libre. |
| Mostrar las preguntas antes de sus respuestas y agregar el nombre del grupo. | Ajuste del menú y de la presentación de los resultados. | Se ejecutó el programa y se revisó la opción 4. |
| Revisar errores y probar la simulación. | Preparación de pruebas de física, validación e historial. | Se ejecutaron las pruebas en C y se contrastaron 60 misiones con parámetros variados: 30 nominales y 30 con fallo. |
| Resolver problemas de compilación y preparar la entrega. | Revisión de los comandos de GCC, organización de los archivos y redacción del README. | Se verificaron los comandos y los archivos incluidos en el proyecto. |
