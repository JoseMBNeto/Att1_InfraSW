processflow: main.o tarefas.o processos.o separador.o
	gcc main.o tarefas.o processos.o separador.o -o processflow

main.o: main.c
	gcc -c main.c

separador.o: separador.c separador.h
	gcc -c separador.c

tarefas.o: tarefas.c tarefas.h
	gcc -c tarefas.c

processos.o: processos.c processos.h
	gcc -c processos.c

log:
	script -a evidencias.log -c "date; whoami; pwd; bash"

clean:
	rm -f *.o processflow

.PHONY: clean log