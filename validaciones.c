#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#define TAM_LINEA 256
static int leer_linea(const char *mensaje, char *linea, size_t capacidad)
{
    int ch;
    size_t longitud;
    for (;;) {
        fputs(mensaje, stdout);
        fflush(stdout);
        if (!fgets(linea, (int)capacidad, stdin)) return 0;
        longitud = strlen(linea);
        if (longitud > 0 && linea[longitud - 1] == '\n') return 1;
        ch = getchar();
        if (ch == EOF || ch == '\n') return 1;
        while ((ch = getchar()) != '\n' && ch != EOF) { }
        puts("Entrada demasiado larga. Vuelva a intentar.");
    }
}

static int solo_espacios(const char *texto)
{
    while (isspace((unsigned char)*texto)) texto++;
    return *texto == '\0';
}
int leer_entero(const char *mensaje, int minimo, int maximo, int *valor)
{
    char linea[TAM_LINEA], *fin;
    long numero;
    while (leer_linea(mensaje, linea, sizeof linea)) {
        errno = 0;
        numero = strtol(linea, &fin, 10);
        if (fin != linea && solo_espacios(fin) && errno != ERANGE &&
            numero >= minimo && numero <= maximo) {
            *valor = (int)numero;
            return 1;
        }
        printf("Ingrese un entero entre %d y %d.\n", minimo, maximo);
    }
    return 0;
}
int leer_real(const char *mensaje, double minimo, double maximo, double *valor)
{
    char linea[TAM_LINEA], *fin;
    double numero;
    size_t i;
    while (leer_linea(mensaje, linea, sizeof linea)) {
        /* Admite coma decimal; no se admiten separadores de miles. */
        for (i = 0; linea[i]; i++) if (linea[i] == ',') linea[i] = '.';
        errno = 0;
        numero = strtod(linea, &fin);
        if (fin != linea && solo_espacios(fin) && errno != ERANGE &&
            isfinite(numero) && numero >= minimo && numero <= maximo) {
            *valor = numero;
            return 1;
        }
        printf("Ingrese un numero finito entre %.2f y %.2f, sin miles.\n",
               minimo, maximo);
    }
    return 0;
}

int leer_caracter(const char *mensaje, const char *permitidos, char *valor)
{
    char linea[TAM_LINEA], *inicio;
    char caracter;
    while (leer_linea(mensaje, linea, sizeof linea)) {
        inicio = linea;
        while (isspace((unsigned char)*inicio)) inicio++;
        caracter = (char)tolower((unsigned char)*inicio);
        if (caracter && solo_espacios(inicio + 1) &&
            strchr(permitidos, caracter)) {
            *valor = caracter;
            return 1;
        }
        printf("Ingrese un solo caracter de: %s.\n", permitidos);
    }
    return 0;
}



