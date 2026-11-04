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
