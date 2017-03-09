ex10a: main.o procurar_num.o
	gcc main.o procurar_num.o -o ex10a
	
main.o: main.c procurar_num.h
	gcc -Wall -ansi -c main.c -o main.o

procurar_num.o: procurar_num.c
	gcc -Wall -ansi -c procurar_num.c -o procurar_num.o

run: ex10a
	./ex10a

clean:
	rm *.o ex10a
