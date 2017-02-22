main: main.o sumPairs.o
	gcc -Wall -g main.o sumPairs.o -o sumPairs

main.o: main.c sumPairs.h
	gcc -Wall -g -c main.c

sumPairs.o: sumPairs.c
	gcc -Wall -g -c sumPairs.c

run: main
	./sumPairs

clean: 
	rm *.o sumPairs
