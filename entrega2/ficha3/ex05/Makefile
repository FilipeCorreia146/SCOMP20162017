main: main.o calculateAverage.o calculateHighest.o calculateLowest.o
	gcc -lrt -lm -Wall -g main.o calculateAverage.o calculateHighest.o calculateLowest.o -o ex06

main.o: main.c calculateAverage.h calculateHighest.h calculateLowest.h
	gcc -lrt -lm -Wall -g -c main.c

calculateLowest.o: calculateLowest.c
	gcc -lrt -lm -Wall -g -c calculateLowest.c

calculateHighest.o: calculateHighest.c
	gcc -lrt -lm -Wall -g -c calculateHighest.c

calculateAverage.o: calculateAverage.c
	gcc -lrt -lm -Wall -g -c calculateAverage.c

run: main
	./ex06

clean: 
	rm *.o ex06
