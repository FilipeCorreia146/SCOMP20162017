sys: main.o sys.o
	gcc -Wall -g main.o sys.o -o sys
	
main.o: main.c sys.h
	gcc -Wall -g -ansi -c main.c -o main.o

sys.o: sys.c
	gcc -Wall -g -ansi -c sys.c -o sys.o

run: sys
	./sys

clean:
	rm *.o sys
