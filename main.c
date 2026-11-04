#include "artemis.h"
#include "validaciones.h"
#include <stdio.h>

int main(void)
{
    Configuracion configuracion = configuracion_predeterminada();
    Resultados resultados;
    Simulacion simulacion;
    int opcion, hay_simulacion = 0;

    do {
        puts("\n==============================================================");
        puts("                      A R T E M I S");
        puts("           Escenario 1 - Ascenso y propulsion del SLS");
        puts("                Proyecto del Grupo " NOMBRE_GRUPO);
        puts("==============================================================");
        puts("                         MENU PRINCIPAL");
        puts("--------------------------------------------------------------");
        puts("  CONFIGURACION");
        puts("    [1] Ver parametros actuales");
        puts("    [2] Modificar parametros");
        puts("    [3] Restaurar valores de la consigna");
        puts("\n  CALCULOS Y SIMULACION");
        puts("    [4] Ver preguntas y respuestas del escenario");
        puts("    [5] Simular ascenso nominal");
        puts("    [6] Simular fallo al apagar motores");
        puts("\n  REPORTES Y AYUDA");
        puts("    [7] Ver ultimo historial y reporte");
        puts("    [8] Exportar ultimo historial a CSV");
        puts("    [9] Consultar ayuda y formulas");
        puts("--------------------------------------------------------------");
        puts("    [0] Salir del simulador");
        puts("==============================================================");
        if (!leer_entero("  Elegi una opcion [0-9]: ", 0, 9, &opcion)) break;
        switch (opcion) {
            case 1: mostrar_configuracion(&configuracion); break;
            case 2:
                if (!configurar(&configuracion)) return 0;
                break;
            case 3:
                configuracion = configuracion_predeterminada();
                puts("Parametros restaurados.");
                break;
            case 4:
                if (calcular_resultados(&configuracion, &resultados))
                    mostrar_resultados(&configuracion, &resultados);
                break;
            case 5:
            case 6:
                iniciar_simulacion(&simulacion, &configuracion, opcion == 6);
                hay_simulacion = 1;
                ejecutar_simulacion(&simulacion);
                break;
            case 7:
                if (hay_simulacion) {
                    mostrar_historial(&simulacion);
                    mostrar_reporte(&simulacion);
                } else puts("Primero ejecute una simulacion.");
                break;
            case 8:
                if (!hay_simulacion) puts("Primero ejecute una simulacion.");
                else if (exportar_historial(&simulacion, "historial.csv"))
                    puts("Historial exportado en historial.csv (carpeta de ejecucion).");
                else puts("No se pudo escribir el archivo. Revise los permisos y el disco.");
                break;
            case 9: mostrar_ayuda(); break;
            case 0: break;
        }
        } while (opcion != 0);
            puts("Fin del simulador.");
            puts("Gracias por usar el proyecto del Grupo " NOMBRE_GRUPO ".");
        return 0;
        }
