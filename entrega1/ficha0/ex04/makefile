ex04: main.o subtracao.o
	gcc main.o subtracao.o -o ex04
	
subtracao.o: subtracao.c
	gcc -Wall -ansi -c subtracao.c -o subtracao.o
	
main.o: main.c subtracao.h
	gcc -Wall -ansi -c main.c -o main.o

run: ex04
	./ex04

clean:
	rm *.o ex04
