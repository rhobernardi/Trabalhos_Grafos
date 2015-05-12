SOURCES = lista.c
HEADERS = graph.h lista.h fila.h
CC = gcc -std=c99

all: programa

programa: main.c $(SOURCES) $(HEADERS)
	$(CC) main.c $(SOURCES) -o programa

zip:
	@rm -rf *~ *.o
	@rm -rf *.zip
	@zip -r exercicio3.zip $(HEADERS) $(SOURCES) main.c entrada.txt Makefile

run:
	./programa # < entrada.txt