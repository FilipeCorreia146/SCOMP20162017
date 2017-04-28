main: main.o countlines.o
	gcc -lrt -lm -Wall -g main.o countlines.o -o ex04 -lpthread

main.o: main.c countlines.h
	gcc -lrt -lm -Wall -g -c main.c -lpthread

countlines.o: countlines.c
	gcc -Wall -g -c countlines.c

clean:
	rm -f ex04

run: main
	./ex04 default.txt
