ex12: main.o 
	gcc main.o -o ex12
	
main.o: main.c 
	gcc -Wall -ansi -c main.c -o main.o

run: ex12
	./ex12

clean:
	rm *.o ex12
