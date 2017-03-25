factorial: factorial.o
	gcc -Wall -g factorial.o -o factorial

factorial.o: factorial.c
	gcc -Wall -g -c factorial.c

main: main.o
	gcc -Wall -g main.o -o ex15

main.o: main.c
	gcc -Wall -g -c main.c

run: main
	./ex15

clean: 
	rm *.o ex15
