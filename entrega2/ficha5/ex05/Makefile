main: main.o func.o
	gcc -lrt -lm -Wall -g main.o func.o -o ex05 -lpthread

main.o: main.c ex05.h
	gcc -lrt -lm -Wall -g -c main.c -lpthread

func.o: ex05.h
	gcc -lrt -lm -Wall -g -c func.c -lpthread

run: main
	./ex05

clean: 
	rm *.o ex05
