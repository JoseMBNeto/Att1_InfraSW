#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    if (argc > 2){
        printf("Falhou\n");
        return -1;
    }

    FILE *pont_arquivo = NULL;
    int modo = 0;

    if (argc == 2){
           modo = 1;
           pont_arquivo = fopen(argv[1], "r");
           if (pont_arquivo == NULL){
            printf("Não foi possível abrir o arquivo");
            return -1;
           }
    }else{
        modo = 0;
    }
    return 0;
    
}