ex02a: main.o 
	gcc main.o -o ex02a
	
main.o: main.c 
	gcc -Wall -ansi -c main.c -o main.o

run: ex02a
	./ex02a

clean:
	rm *.o ex02a
