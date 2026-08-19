#ifndef TAREFAS_H
#define TAREFAS_H

typedef struct Tarefas{
    char *nomeTarefa;
    char **argumentos;
    int quantidadeArgumentos;
    char *arquivoEntrada;
    char *arquivoSaida;
    int modoSaida;
}Tarefas;


#endif