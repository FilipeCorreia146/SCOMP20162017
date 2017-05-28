main: main.o func.o obtem_Notas.o
	gcc -lrt -lm -Wall -g main.o func.o obtem_Notas.o -o ex09 -lpthread

main.o: main.c ex09.h
	gcc -lrt -lm -Wall -g -c main.c -lpthread

func.o: func.c ex09.h
	gcc -lrt -lm -Wall -g -c func.c -lpthread

obtem_Notas.o: obtem_Notas.c ex09.h
	gcc -lrt -lm -Wall -g -c obtem_Notas.c -lpthread

run: main
	./ex09

clean:
	rm *.o ex09
