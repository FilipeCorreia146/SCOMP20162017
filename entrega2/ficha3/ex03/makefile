main: main.o
	gcc -lrt -lm -Wall -g main.o -o ex03

main.o: main.c
	gcc -lrt -lm -Wall -g -c main.c

run: main
	./ex03

clean: 
	rm *.o ex03
