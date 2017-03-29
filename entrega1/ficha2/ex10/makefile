ex10: main.o 
	gcc main.o -o ex10
	
main.o: main.c 
	gcc -Wall -ansi -c main.c -o main.o

run: ex10
	./ex10

clean:
	rm *.o ex10
