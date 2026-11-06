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
typedef struct {
    double v1, y1, v2, duracion_fase2, tiempo_corte;
    double altura_maxima, tiempo_apogeo, aceleracion_g;
} Resultados;

typedef enum { FASE_SRB, FASE_NUCLEO, VUELO_LIBRE, FIN_CORTE, FIN_APOGEO } Fase;

typedef struct {
    double tiempo, altura, velocidad;
    Fase fase;
} Estado;
typedef struct {
    Configuracion configuracion;
    Resultados resultados;
    Estado estado;
    Estado historial[MAX_REGISTROS];
    int cantidad, fallo, finalizada, omitidos;
} Simulacion;

Configuracion configuracion_predeterminada(void);
int validar_configuracion(const Configuracion *c, char *error, unsigned capacidad);
int calcular_resultados(const Configuracion *c, Resultados *r);
int configurar(Configuracion *c);
void mostrar_configuracion(const Configuracion *c);
void mostrar_resultados(const Configuracion *c, const Resultados *r);
void iniciar_simulacion(Simulacion *s, const Configuracion *c, int fallo);
void avanzar_turno(Simulacion *s);
void ejecutar_simulacion(Simulacion *s);
void mostrar_historial(const Simulacion *s);
void mostrar_reporte(const Simulacion *s);
int exportar_historial(const Simulacion *s, const char *ruta);
const char *nombre_fase(Fase fase);
void mostrar_ayuda(void);

#endif

