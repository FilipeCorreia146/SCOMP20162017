main: main.o printer.o
	gcc -lrt -lm -Wall -g main.o printer.o -o ex01 -lpthread

main.o: main.c ex01.h printer.h
	gcc -lrt -lm -Wall -g -c main.c -lpthread

printer.o: printer.c
	gcc -lrt -lm -Wall -g -c printer.c -lpthread

run: main
	./ex01

clean: 
	rm *.o ex01
