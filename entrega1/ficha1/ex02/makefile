ex02: main.o 
	gcc main.o -o ex02
	
main.o: main.c 
	gcc -Wall -ansi -c main.c -o main.o

run: ex02
	./ex02

clean:
	rm *.o ex02
