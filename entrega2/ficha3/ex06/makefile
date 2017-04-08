ex06: main.c ex06.h
	gcc -lrt -lm -Wall -g main.c -o ex06
	
clean:
	rm -f *.o ex06
	
run_ex06: ex06
	./ex06

delete_memory: ex06
	./ex06 r-m
	
run: delete_memory
