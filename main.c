#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc > 2){
        printf("Falhou\n");
        exit(1);
    }

    FILE *pont_arquivo = NULL;
    int modo = 0;

    if (argc == 2){
           modo = 1;
           printf("Modo workflow\n");
           pont_arquivo = fopen(argv[1], "r");
           if (pont_arquivo == NULL){
            printf("Não foi possível abrir o arquivo\n");
            exit(1);
           }
    }else{
        modo = 0;
        printf("Modo interativo\n");
    }
    return 0;
    
}