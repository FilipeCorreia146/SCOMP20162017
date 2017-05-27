main: main.o func.o
	gcc -lrt -lm -Wall -g main.o func.o -o ex03 -lpthread

main.o: main.c func.h
	gcc -lrt -lm -Wall -g -c main.c -lpthread

func.o: func.c
	gcc -lrt -lm -Wall -g -c func.c -lpthread

run: main
	./ex03

clean: 
	rm *.o ex03
