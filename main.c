#define _GNU_SOURCE //importei porque o getline não estava funcionando sem ele
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "separador.h"

int main(int argc, char *argv[]) {
    
    if (argc > 2){
        fprintf(stderr,"Falhou\n");
        exit(1);
    }

    FILE *pont_arquivo = NULL;
    int modo = 0;
    // 0 é interativo e 1 é workflow

    if (argc == 2){
           modo = 1;
           printf("Modo workflow\n");
           pont_arquivo = fopen(argv[1], "r");
           if (pont_arquivo == NULL){
            fprintf(stderr,"\nNão foi possível abrir o arquivo\n");
            exit(1);
           }
    }else{
        modo = 0;
        printf("Modo interativo\n");
    }
    
    char *linha = NULL;
    size_t tamanho = 0;

    while(true){
        
        ssize_t valorLinha;

        if (modo == 0){
            printf("processflow> ");
            valorLinha = getline(&linha, &tamanho, stdin);

            if (valorLinha == -1){
                break;
            }
        }else{
            valorLinha = getline(&linha, &tamanho, pont_arquivo);

            if(valorLinha == -1){
                break;
            }
            printf("%s", linha);
        }

        linha[strcspn(linha,"\n")] = '\0';

        if (strlen(linha) == 0){
            continue;
        }
        if(strcmp(linha, "exit") == 0){
            break;
        }

        //printf("Linha lida: %s\n", linha);

        //Testando o separador
        char *palavras[50];
        int quantidade = separarPalavras(linha, palavras);

        for (int i = 0; i < quantidade; i++){
            printf("palavra[%d] = %s\n", i, palavras[i]);
        }
    }

    if (modo == 1){
        fclose(pont_arquivo);
    }

    free(linha);

    return 0;
    
}