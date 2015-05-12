all: Compile
	
Compile:
	gcc -std=c99 -g main.c Graph.h -o TADGrafos

main:
	gcc -c -g main.c

Graph:
	gcc -c -g Graph.h

code: clean
	#gedit * Makefile
	subl * 

clean:
	@find -name "*~" | xargs rm -rf
	rm -rf *.o *.gch

zip: Compile clean
	@rm TADGrafos
	@rm -f Lab2.zip
	@zip -r Lab2.zip *

run:
	./TADGrafos < entrada.txt