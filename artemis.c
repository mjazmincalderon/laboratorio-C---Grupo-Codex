#include "artemis.h"
#include "validaciones.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

Configuracion configuracion_predeterminada(void)
{
    Configuracion c = {20.0, 12.5, 120.0, 160000.0, 9.8, 10.0};
    return c;
}

int validar_configuracion(const Configuracion *c, char *error, unsigned capacidad)
{
    const char *mensaje = NULL;
    if (!isfinite(c->a1) || c->a1 < 0.01 || c->a1 > 100.0 ||
        !isfinite(c->a2) || c->a2 < 0.01 || c->a2 > 100.0)
        mensaje = "Las aceleraciones deben estar entre 0.01 y 100 m/s^2.";
    else if (!isfinite(c->t1) || c->t1 < 0.01 || c->t1 > 3600.0)
        mensaje = "El tiempo de desacople debe estar entre 0.01 y 3600 s.";
    else if (!isfinite(c->altura_corte) || c->altura_corte < 1.0 ||
             c->altura_corte > 1000000000.0)
        mensaje = "La altura de corte debe estar entre 1 y 1000000000 m.";
    else if (!isfinite(c->gravedad) || c->gravedad < 0.01 || c->gravedad > 100.0)
        mensaje = "La gravedad debe estar entre 0.01 y 100 m/s^2.";
    else if (!isfinite(c->paso) || c->paso < 0.01 || c->paso > 3600.0)
        mensaje = "El paso debe estar entre 0.01 y 3600 s.";
    else if (c->altura_corte <= 0.5 * c->a1 * c->t1 * c->t1)
        mensaje = "La altura de corte debe superar la altura del desacople (y1).";
    if (!mensaje) {
        double v1 = c->a1 * c->t1;
        double distancia = c->altura_corte - 0.5 * c->a1 * c->t1 * c->t1;
        double v2 = sqrt(v1 * v1 + 2.0 * c->a2 * distancia);
        double dt2 = 2.0 * distancia / (v1 + v2);
        double turnos = ceil(c->t1 / c->paso) + ceil(dt2 / c->paso) +
                        ceil(v2 / c->gravedad / c->paso);
        if (turnos > MAX_TURNOS)
            mensaje = "La simulacion excederia 1000000 turnos. Aumente el paso temporal.";
    }
    if (capacidad) snprintf(error, capacidad, "%s", mensaje ? mensaje : "");
    return mensaje == NULL;
}

int calcular_resultados(const Configuracion *c, Resultados *r)
{
    char error[160];
    double distancia;
    if (!validar_configuracion(c, error, sizeof error)) return 0;
    r->v1 = c->a1 * c->t1;
    r->y1 = 0.5 * c->a1 * c->t1 * c->t1;
    distancia = c->altura_corte - r->y1;
    r->v2 = sqrt(r->v1 * r->v1 + 2.0 * c->a2 * distancia);
    /* Forma racionalizada: evita restar dos velocidades muy parecidas. */
    r->duracion_fase2 = 2.0 * distancia / (r->v1 + r->v2);
    r->tiempo_corte = c->t1 + r->duracion_fase2;
    r->altura_maxima = c->altura_corte + r->v2 * r->v2 / (2.0 * c->gravedad);
    r->tiempo_apogeo = r->tiempo_corte + r->v2 / c->gravedad;
    r->aceleracion_g = c->a1 / c->gravedad;
    return 1;
}

int configurar(Configuracion *c)
{
    Configuracion nueva;
    char error[160];
    for (;;) {
        puts("\nUnidades SI. Use punto o coma decimal, sin separadores de miles.");
        if (!leer_real("a1 (m/s^2): ", 0.01, 100.0, &nueva.a1) ||
            !leer_real("a2 (m/s^2): ", 0.01, 100.0, &nueva.a2) ||
            !leer_real("Tiempo del desacople (s): ", 0.01, 3600.0, &nueva.t1) ||
            !leer_real("Altura de apagado (m): ", 1.0, 1000000000.0, &nueva.altura_corte) ||
            !leer_real("Gravedad (m/s^2): ", 0.01, 100.0, &nueva.gravedad) ||
            !leer_real("Paso por turno (s): ", 0.01, 3600.0, &nueva.paso)) return 0;
        if (validar_configuracion(&nueva, error, sizeof error)) {
            *c = nueva;
            puts("Configuracion guardada.");
            return 1;
        }
        printf("Configuracion incompatible: %s\nVuelva a ingresar los parametros.\n", error);
    }
}

void mostrar_configuracion(const Configuracion *c)
{
    printf("\na1: %.3f m/s^2 | a2: %.3f m/s^2\n", c->a1, c->a2);
    printf("Desacople: %.3f s | Apagado: %.3f m\n", c->t1, c->altura_corte);
    printf("Gravedad: %.3f m/s^2 | Paso: %.3f s\n", c->gravedad, c->paso);
    puts("Condiciones iniciales: y0 = 0 m, v0 = 0 m/s.");
}

void mostrar_resultados(const Configuracion *c, const Resultados *r)
{
    puts("\nPREGUNTAS Y RESPUESTAS DEL ESCENARIO 1");
    puts("========================================");
    puts("\na) Que rapidez alcanza la nave al desacoplar los cohetes SRB");
    printf("   a los %.3f s y que altitud ha recorrido hasta ese punto?\n", c->t1);
    printf("\n   Respuesta: v1 = %.3f m/s; y1 = %.3f m (%.3f km).\n",
           r->v1, r->y1, r->y1 / 1000.0);

    puts("\nb) Cual es la rapidez maxima que alcanza la nave Orion al apagar");
    printf("   sus motores a los %.3f m de altitud?\n", c->altura_corte);
    printf("\n   Respuesta: v2 = %.3f m/s.\n", r->v2);
    printf("   Duracion fase 2: %.6f s; tiempo total de ascenso propulsado: %.6f s.\n",
           r->duracion_fase2, r->tiempo_corte);

    printf("\nc) Si los motores fallaran a los %.3f m y la nave quedara\n", c->altura_corte);
    printf("   en caida libre con g = %.3f m/s^2, cual seria la altitud maxima\n", c->gravedad);
    puts("   respecto de la plataforma antes de comenzar a caer?");
    printf("\n   Respuesta: hmax = %.3f m (%.3f km).\n",
           r->altura_maxima, r->altura_maxima / 1000.0);
    printf("   Tiempo desde apagado hasta apogeo: %.6f s.\n", r->v2 / c->gravedad);

    puts("\nd) Exprese la aceleracion maxima de la primera fase como multiplo");
    puts("   de la gravedad terrestre (g).");
    printf("\n   Respuesta: aceleracion neta de la primera fase = %.6f g.\n", r->aceleracion_g);
    printf("   Carga aparente ideal (a1 + g)/g: %.6f veces el peso.\n",
           1.0 + r->aceleracion_g);
    puts("\nNota: las aceleraciones dadas son netas; no se resta g durante la propulsion.");
    puts("========================================");
}
