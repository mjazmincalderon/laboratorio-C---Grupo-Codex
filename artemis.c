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

