main: main.o invert.o
	gcc -Wall -g main.o invert.o -o invert

main.o: main.c invert.h
	gcc -Wall -g -c main.c

invert.o: invert.c
	gcc -Wall -g -c invert.c

run: main
	./invert

clean: 
	rm *.o invert
