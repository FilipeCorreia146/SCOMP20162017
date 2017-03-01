main: main.o read_names.o
	gcc -Wall -g main.o read_names.o -o read_names

main.o: main.c read_names.h
	gcc -Wall -g -c main.c

read_names.o: read_names.c
	gcc -Wall -g -c read_names.c

run: main
	./read_names

clean: 
	rm *.o read_names
