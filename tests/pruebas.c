#include "artemis.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

static void cerca(double obtenido, double esperado, double tolerancia)
{
    assert(fabs(obtenido - esperado) <= tolerancia);
}

int main(void)
{
    Configuracion c = configuracion_predeterminada();
    Resultados r;
    Simulacion s;
    char error[160];
    int i;
    assert(calcular_resultados(&c, &r));
    cerca(r.v1, 2400.0, 1e-9);
    cerca(r.y1, 144000.0, 1e-9);
    cerca(r.v2 * r.v2, 6160000.0, 1e-7);
    cerca(r.altura_maxima, 474285.7142857143, 1e-6);
    cerca(r.aceleracion_g, 20.0 / 9.8, 1e-12);
    cerca(r.y1 + r.v1*r.duracion_fase2 +
          0.5*c.a2*r.duracion_fase2*r.duracion_fase2, c.altura_corte, 1e-7);
