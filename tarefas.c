#include <stdlib.h>
#include "tarefas.h"

Tarefas criarTarefa (char *nome, char **palavras, int quantiaPalavras){

    Tarefas tarefaNova;
    tarefaNova.nomeTarefa = nome;

    tarefaNova.argumentos = malloc ((quantiaPalavras + 1) * sizeof(char *));
    
    for (int i=0; i < quantiaPalavras; i++){
        tarefaNova.argumentos[i] = palavras[i];
    }
    
    tarefaNova.argumentos[quantiaPalavras] = NULL;
    tarefaNova.quantidadeArgumentos = quantiaPalavras;
    tarefaNova.arquivoEntrada = NULL;
    tarefaNova.arquivoSaida = NULL;
    tarefaNova.modoSaida = 0;

    return tarefaNova;
}