main: main.o
	gcc -Wall -g main.o -o ex01

main.o: main.c
	gcc -Wall -g -c main.c

run: main
	./ex01

clean: 
	rm *.o ex01
