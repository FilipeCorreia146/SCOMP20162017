main: main.o cria_gemeos.o
	gcc -Wall -g main.o cria_gemeos.o -o cria_gemeos

main.o: main.c cria_gemeos.h
	gcc -Wall -g -c main.c

cria_gemeos.o: cria_gemeos.c
	gcc -Wall -g -c cria_gemeos.c

run: main
	./cria_gemeos

clean: 
	rm *.o cria_gemeos
