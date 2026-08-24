#define _GNU_SOURCE //importei porque o getline não estava funcionando sem ele
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "separador.h"
#include "tarefas.h"
#include "processos.h"

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

        char *palavras[50];
        int quantidade = separarPalavras(linha, palavras);

        if (strcmp(palavras[0], "task") == 0){
            if (quantidade < 3){
                fprintf(stderr, "\nQuantidade de argumentos errada para uma task\n");
                continue;
            }

            char *nomeTarefa = palavras[1];
            Tarefas novaTarefa = criarTarefa(nomeTarefa, &palavras[2], quantidade - 2);
            adicionarTarefa(novaTarefa);
            printf("\nTarefa cadastrada com sucesso\n");

        }else if (strcmp(palavras[0], "run") == 0){
            if (quantidade < 3){
                fprintf(stderr, "\nQuantidade de argumentos insuficientes para um run\n");
                continue;
            }

            char *modoExecucao = palavras[1];
            int tarefasCitadas = quantidade - 2;
            Tarefas tarefasExecutar[tarefasCitadas];
            int tarefasEncontradas = 0;

            for (int i = 0; i < tarefasCitadas; i++){
                char *nomeProcurar = palavras[2 + i];
                Tarefas *encontrada = buscarTarefa(nomeProcurar);

                if (encontrada == NULL){
                    fprintf(stderr, "Tarefa '%s' nao encontrada\n", nomeProcurar);
                }else{
                    tarefasExecutar[tarefasEncontradas] = *encontrada;
                    tarefasEncontradas++;
                }
            }

            if (tarefasEncontradas == 0){
                fprintf(stderr, "Nenhuma tarefa para executar\n");
                continue;
            }

            if (strcmp(modoExecucao, "sequential") == 0){
                processoSequencia(tarefasExecutar, tarefasEncontradas);
            }else if (strcmp(modoExecucao, "parallel") == 0){
                processoParalelo(tarefasExecutar, tarefasEncontradas);
            }else{
                fprintf(stderr, "Execucao desconhecida\n");
            }


        }else if(strcmp(palavras[0], "input") == 0){
            if (quantidade != 3){
                fprintf(stderr, "Quantidade de arguemntos errada para input, tente denovo\n");
                continue;
            }

            char *nomeTarefa = palavras[1];
            char *caminhoArquivo = palavras[2];
            Tarefas *tarefaEncontrada = buscarTarefa(nomeTarefa);

            if (tarefaEncontrada == NULL){
                fprintf(stderr, "A tarefa nao existe\n");
                continue;
            }

            tarefaEncontrada->arquivoEntrada = strdup(caminhoArquivo);

        }else if(strcmp(palavras[0], "output") == 0){
            if (quantidade != 3){
                fprintf(stderr, "Quantidade de arguemntos errada para output, tente denovo\n");
                continue;
            }

            char *nomeTarefa = palavras[1];
            char *caminhoArquivo = palavras[2];
            Tarefas *tarefaEncontrada = buscarTarefa(nomeTarefa);

            if (tarefaEncontrada == NULL){
                fprintf(stderr, "A tarefa nao existe\n");
                continue;
            }

            tarefaEncontrada->arquivoSaida = strdup(caminhoArquivo);
            tarefaEncontrada->modoSaida = 1;

        }else if(strcmp(palavras[0], "append") == 0){
            if (quantidade != 3){
                fprintf(stderr, "Quantidade de arguemntos errada para append, tente denovo\n");
                continue;
            }

            char *nomeTarefa = palavras[1];
            char *caminhoArquivo = palavras[2];
            Tarefas *tarefaEncontrada = buscarTarefa(nomeTarefa);

            if (tarefaEncontrada == NULL){
                fprintf(stderr, "A tarefa nao existe\n");
                continue;
            }

            tarefaEncontrada->arquivoSaida = strdup(caminhoArquivo);
            tarefaEncontrada->modoSaida = 2;

        }else if(strcmp(palavras[0], "workdir") == 0){
            if (quantidade != 2){
                fprintf(stderr, "Quantidade de arguemntos errada para workdir, tente denovo\n");
                continue;
            }

            char *caminho = palavras[1];

            if (access(caminho, F_OK) == -1){
                fprintf(stderr, "O diretorio nao existe\n");
                continue;
            }

            definirDiretorio(caminho);

        }else if (strcmp(palavras[0], "start") ==0){
            if (quantidade < 2){
                fprintf(stderr, "Quantidade de arguemntos errada para start, tente denovo\n");
                continue;
            }

            char *nomeTarefa = palavras[1];
            Tarefas *tarefaEncontrada = buscarTarefa(nomeTarefa);

            if (tarefaEncontrada == NULL){
                fprintf(stderr, "A tarefa nao existe\n");
                continue;
            }
            iniciarJobs(*tarefaEncontrada);

        }else if (strcmp(palavras[0], "jobs") == 0){

        }else if(strcmp(palavras[0], "wait")){

        }else{
        
            fprintf(stderr, "\nComando desconhecido, tente novamente!\n");
        }
    }

    if (modo == 1){
        fclose(pont_arquivo);
    }

    free(linha);

    return 0;
    
}