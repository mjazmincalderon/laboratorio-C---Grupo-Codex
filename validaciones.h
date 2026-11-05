#ifndef VALIDACIONES_H
#define VALIDACIONES_H
int leer_entero(const char *mensaje, int minimo, int maximo, int *valor);
int leer_real(const char *mensaje, double minimo, double maximo, double *valor);
int leer_caracter(const char *mensaje, const char *permitidos, char *valor);
#endif
