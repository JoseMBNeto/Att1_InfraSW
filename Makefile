processflow: main.o 
	gcc main.o -o processflow

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o processflow

.PHONY: clean