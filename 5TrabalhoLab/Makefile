SOURCES = lista.c graph.c
HEADERS = graph.h lista.h fila.h
CC = gcc -std=c99

all: programa

programa: main.c $(SOURCES)
	$(CC) -g main.c $(SOURCES) -o programa

zip:
	@rm -rf *~ *.o
	@rm -rf *.zip
	@zip -r exercicio5.zip $(HEADERS) $(SOURCES) main.c entrada.txt Makefile

run:
	./programa < entrada.txt