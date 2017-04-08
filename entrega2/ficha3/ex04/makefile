ex04: main.c ex04.h
	gcc -lrt -lm -Wall -g main.c -o ex04 

clean:
	rm -f *.o ex04

run_ex04: ex04 
	./ex04

delete_memory: ex04
	./ex04 -rm

run: delete_memory



