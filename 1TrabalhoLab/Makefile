all: Graph main Compile clean run
	

Compile:
	gcc -o teste Graph.h main.c

main:
	gcc -c main.c

Graph:
	gcc -c Graph.h

code: clean
	#gedit src/* include/* Makefile
	subl Graph.h main.c Makefile

clean:
	@find -name "*~" | xargs rm -rf
	rm -rf *.o *.gch #obj/*.o
	#rm -rf bin/*

zip: clean
	@rm -f Lab1.zip
	@zip -r Lab1.zip *.c *.h Makefile

run:
	#bin/GameUSP
	./teste
