ex02: main.o subtracao.o
	gcc main.o subtracao.o -o ex02
	
subtracao.o: subtracao.c
	gcc -Wall -ansi -c subtracao.c -o subtracao.o
	
main.o: main.c subtracao.h
	gcc -Wall -ansi -c main.c -o main.o

run: ex02
	./ex02

clean:
	rm *.o ex02
