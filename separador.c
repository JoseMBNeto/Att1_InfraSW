#include <string.h>
#include "separador.h"

int separarPalavras (char *linha, char **palavras){

    int contador = 0;

    char *palavra = strtok(linha, " ");

    while(palavra != NULL) {
        palavras[contador] = palavra;
        contador++;
        palavra = strtok(NULL, " ");
    }

    return contador;
}