sys: main.o sys.o split.o
	gcc main.o sys.o split.o -o sys
	
main.o: main.c split.h sys.h
	gcc -Wall -ansi -c main.c -o main.o

split.o: split.c
	gcc -Wall -ansi -c split.c -o split.o

sys.o: sys.c
	gcc -Wall -ansi -c sys.c -o sys.o

run: sys
	./sys

clean:
	rm *.o sys
