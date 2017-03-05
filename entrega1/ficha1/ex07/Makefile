main: main.o M.o
	gcc -Wall -g main.o M.o -o M

main.o: main.c M.h
	gcc -Wall -g -c main.c

M.o: M.c
	gcc -Wall -g -c M.c

run: main
	./M

clean: 
	rm *.o M
