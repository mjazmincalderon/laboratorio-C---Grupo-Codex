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
