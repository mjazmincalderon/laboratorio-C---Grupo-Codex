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
c.paso = 3600;
    iniciar_simulacion(&s, &c, 0);
    avanzar_turno(&s);
    assert(s.estado.fase == FASE_NUCLEO);
    cerca(s.estado.tiempo, c.t1, 1e-12);
    cerca(s.estado.altura, r.y1, 1e-9);
    avanzar_turno(&s);
    assert(s.finalizada && s.estado.fase == FIN_CORTE);
    cerca(s.estado.altura, c.altura_corte, 1e-9);
    cerca(s.estado.velocidad, r.v2, 1e-9);
    i = s.cantidad;
    avanzar_turno(&s);
    assert(s.cantidad == i);
    iniciar_simulacion(&s, &c, 1);
    avanzar_turno(&s);
    avanzar_turno(&s);
    assert(!s.finalizada && s.estado.fase == VUELO_LIBRE);
    avanzar_turno(&s);
    assert(s.finalizada && s.estado.fase == FIN_APOGEO);
    cerca(s.estado.velocidad, 0, 1e-12);
    cerca(s.estado.altura, r.altura_maxima, 1e-6);
    c.a1 = 10; c.a2 = 5; c.t1 = 10; c.altura_corte = 2000;
    c.gravedad = 10; c.paso = 7;
    assert(calcular_resultados(&c, &r));
    cerca(r.v1, 100, 1e-9);
    cerca(r.y1, 500, 1e-9);
    cerca(r.v2, sqrt(25000.0), 1e-9);
    cerca(r.altura_maxima, 3250, 1e-9);
    iniciar_simulacion(&s, &c, 1);
    for (i = 0; !s.finalizada && i < 100; i++) avanzar_turno(&s);
    assert(s.finalizada);
    cerca(s.estado.altura, 3250, 1e-9);

for (i = 1; i < s.cantidad; i++) {
        assert(s.historial[i].tiempo > s.historial[i-1].tiempo);
        assert(s.historial[i].altura >= s.historial[i-1].altura);
    }
    c.altura_corte = 500;
    assert(!validar_configuracion(&c, error, sizeof error));
    c = configuracion_predeterminada(); c.gravedad = 0;
    assert(!calcular_resultados(&c, &r));
    c = configuracion_predeterminada(); c.a1 = NAN;
    assert(!validar_configuracion(&c, error, sizeof error));
    c = configuracion_predeterminada(); c.paso = INFINITY;
    assert(!validar_configuracion(&c, error, sizeof error));
    c = configuracion_predeterminada(); c.altura_corte = 1000000000.0;
    c.paso = 0.01; c.gravedad = 0.01;
assert(!validar_configuracion(&c, error, sizeof error));
    c = configuracion_predeterminada(); c.paso = 0.01;
    iniciar_simulacion(&s, &c, 1);
    for (i = 0; !s.finalizada && i < 100000; i++) avanzar_turno(&s);
    assert(s.finalizada && s.cantidad == MAX_REGISTROS && s.omitidos > 0);
    cerca(s.estado.altura, 474285.7142857143, 1e-6);
    puts("OK: fisica, eventos, parametros, limites e historial.");
    return 0;
}
