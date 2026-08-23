#define _GNU_SOURCE //stdup estava dependendo desse define para funcionar
#include <stdlib.h>
#include <string.h>
#include "tarefas.h"

static Tarefas *listaTarefas = NULL;
static int capacidade = 0;
static int quantidadeTarefas = 0;

Tarefas criarTarefa (char *nome, char **palavras, int quantiaPalavras){

    Tarefas tarefaNova;
    tarefaNova.nomeTarefa = strdup(nome);

    tarefaNova.argumentos = malloc ((quantiaPalavras + 1) * sizeof(char *));
    
    for (int i = 0; i < quantiaPalavras; i++){
        tarefaNova.argumentos[i] = strdup(palavras[i]);
    }
    
    tarefaNova.argumentos[quantiaPalavras] = NULL;
    tarefaNova.quantidadeArgumentos = quantiaPalavras;
    tarefaNova.arquivoEntrada = NULL;
    tarefaNova.arquivoSaida = NULL;
    tarefaNova.modoSaida = 0;

    return tarefaNova;
}

void adicionarTarefa(Tarefas novaTarefa){

    if (quantidadeTarefas == capacidade){
        if (capacidade == 0){
            capacidade = 4;
        }else{
            capacidade = capacidade * 2;
        }
        listaTarefas = realloc(listaTarefas, capacidade * sizeof(Tarefas));
    }
    listaTarefas[quantidadeTarefas] = novaTarefa;
    quantidadeTarefas++;
}

Tarefas *buscarTarefa(char *nome){

    for (int i = 0; i < quantidadeTarefas; i++){
        if (strcmp(listaTarefas[i].nomeTarefa, nome) == 0){
            return &listaTarefas[i];
        }
    }
    return NULL;
}