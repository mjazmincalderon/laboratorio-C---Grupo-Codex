#ifndef ARTEMIS_H
#define ARTEMIS_H

#define MAX_REGISTROS 4096
#define MAX_TURNOS 1000000
#define NOMBRE_GRUPO "Codex"

typedef struct {
    double a1, a2;          /* Aceleraciones NETAS hacia arriba, m/s^2. */
    double t1;              /* Instante de desacople, s. */
    double altura_corte;    /* Altura de apagado, m. */
    double gravedad;        /* Modulo de la gravedad, m/s^2. */
    double paso;            /* Duracion maxima de un turno, s. */
} Configuracion;
