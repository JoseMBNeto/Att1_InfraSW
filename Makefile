processflow: main.o tarefas.o processos.o
	gcc main.o tarefas.o processos.o -o processflow

teste: teste.o tarefas.o processos.o
	gcc teste.o tarefas.o processos.o -o teste

main.o: main.c
	gcc -c main.c

teste.o: teste.c
	gcc -c teste.c

tarefas.o: tarefas.c tarefas.h
	gcc -c tarefas.c

processos.o: processos.c processos.h
	gcc -c processos.c

log:
	script -a evidencias.log -c "date; whoami; pwd; bash"

clean:
	rm -f *.o processflow

.PHONY: clean log