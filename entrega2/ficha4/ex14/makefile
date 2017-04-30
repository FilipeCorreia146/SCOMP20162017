all: sala visitantes main

sala: sala.c 
	gcc -lrt -lm -lpthread -Wall -g -o sala sala.c
	
visitantes: visitantes.c 
	gcc -lrt -lm -lpthread -Wall -g -o visitantes visitantes.c
	
main: main.c sala visitantes
	gcc -lrt -lm -lpthread -Wall -g -o main main.c
	
clean:
	rm -f visitantes sala main

run: main
	./main
