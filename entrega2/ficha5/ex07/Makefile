main: main.o func.o fillVector.o
	gcc -lrt -lm -Wall -g main.o func.o fillVector.o -o ex07 -lpthread

main.o: main.c ex07.h
	gcc -lrt -lm -Wall -g -c main.c -lpthread

func.o: func.c ex07.h
	gcc -lrt -lm -Wall -g -c func.c -lpthread

fillVector.o: fillVector.c ex07.h
	gcc -lrt -lm -Wall -g -c fillVector.c -lpthread

run: main
	./ex07

clean:
	rm *.o ex07
