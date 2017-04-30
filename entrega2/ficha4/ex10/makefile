all: main leitor escritor

leitor: leitor.c 
	gcc -lrt -lm -lpthread -Wall -g -o leitor leitor.c
	
escritor: escritor.c 
	gcc -lrt -lm -lpthread -Wall -g -o escritor escritor.c
	
main: main.c leitor escritor ex10.h
	gcc -lrt -lm -lpthread -Wall -g -o main main.c
	
clean:
	rm -f main leitor escritor

run: main 
	./main
