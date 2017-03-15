ex02b: main.o 
	gcc main.o -o ex02b
	
main.o: main.c 
	gcc -Wall -ansi -c main.c -o main.o

run: ex02b
	./ex02b

clean:
	rm *.o ex02b
