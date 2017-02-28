main: main.o soma_multiplos_x.o
	gcc -Wall -g main.o soma_multiplos_x.o -o soma_multiplos_x

main.o: main.c soma_multiplos_x.h
	gcc -Wall -g -c main.c

soma_multiplos_x.o: soma_multiplos_x.c
	gcc -Wall -g -c soma_multiplos_x.c

run: main
	./soma_multiplos_x

clean: 
	rm *.o soma_multiplos_x
