main: main.o
	gcc -Wall -g main.o -o executar

main.o: main.c
	gcc -Wall -g -c main.c

run: main
	./executar

clean: 
	rm *.o executar
