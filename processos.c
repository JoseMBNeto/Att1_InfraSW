#define _GNU_SOURCE //stdup estava dependendo desse define para funcionar
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "processos.h"
#include <sys/wait.h>

static char *diretorioAtual = NULL;

void definirDiretorio(char *caminho){
    diretorioAtual = strdup(caminho);
}

pid_t processarTarefa(Tarefas tarefa){

    pid_t pid = fork();

    if (pid == 0){

        if (diretorioAtual != NULL){
            int resultado = chdir(diretorioAtual);
            if (resultado == -1){
                fprintf(stderr, "Nao foi possivel mudar o diretorio\n");
                exit(1);
            }
        }

        if (tarefa.arquivoEntrada != NULL){
            int descritorEntrada = open(tarefa.arquivoEntrada, O_RDONLY);
            if (descritorEntrada == -1){
                fprintf(stderr, "Arquivo de entrada nao encontrado\n");
                exit(1);
            }
            dup2(descritorEntrada, 0);
        }

        if (tarefa.arquivoSaida != NULL){
            int descritorSaida = 0;
            if (tarefa.modoSaida == 1){
                descritorSaida = open(tarefa.arquivoSaida, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }else if (tarefa.modoSaida == 2){
                descritorSaida = open(tarefa.arquivoSaida, O_WRONLY | O_CREAT | O_APPEND, 0644);
            }

            if (descritorSaida == -1){
                fprintf(stderr, "Arquivo de saida nao encontrado\n");
                exit(1);
            }
            dup2(descritorSaida, 1);
        }

        execvp(tarefa.argumentos[0], tarefa.argumentos);

        fprintf(stderr, "O programa não pode ser executado");
        exit(1);

    }else if (pid > 0){
        return pid;
    }else{
        fprintf(stderr, "Não foi possível processar a tarefa, tente novamente\n");
        return -1;
    }
}

void processoSequencia(Tarefas *lista, int quantidade){
    
    for (int i = 0; i < quantidade; i++){
        pid_t pid = processarTarefa(lista[i]);

        if (pid > 0){
            int status = 0;
            waitpid(pid, &status, 0);       
        }
    }
}

void processoParalelo(Tarefas *lista, int quantidade){
    pid_t *pids = malloc((quantidade) * sizeof(pid_t));
    
    for (int i = 0; i < quantidade; i++){
        pids[i] = processarTarefa(lista[i]);
    }

    for (int i = 0; i < quantidade; i++){
        if (pids[i] > 0){
            int status = 0;
            waitpid(pids[i], &status, 0);
        }
    }
    free(pids);
}