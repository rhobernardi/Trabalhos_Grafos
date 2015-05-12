all: Compile run
	
Compile:
	gcc -std=c99 main.c Graph.h -o TADGrafos

main:
	gcc -c main.c

Graph:
	gcc -c Graph.h

code: clean
	#gedit * Makefile
	subl * 

clean:
	@find -name "*~" | xargs rm -rf
	rm -rf *.o *.gch

zip: Compile clean
	@rm TADGrafos
	@rm -f Lab1.zip
	@zip -r Lab1.zip *

run:
	./TADGrafos < caso0.txt
	# ./TADGrafos < ./test_cases/case4.txt
	# ./TADGrafos < ./test_cases/case6.txt
	# ./TADGrafos < ./test_cases/case8.txt
	# ./TADGrafos < ./test_cases/case10.txt
	# ./TADGrafos < ./test_cases/case12.txt
	# ./TADGrafos < ./test_cases/case14.txt
	# ./TADGrafos < ./test_cases/case16.txt