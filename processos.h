#ifndef PROCESSOS_H
#define PROCESSOS_H

#include <sys/types.h>
#include "tarefas.h"

pid_t processarTarefa (Tarefas tarefa);
void processoSequencia (Tarefas *listaTarefas, int quantia);
void processoParalelo (Tarefas *listaTarefas, int quantia);

#endif