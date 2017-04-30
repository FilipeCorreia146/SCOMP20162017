all: cliente servidor main

cliente: cliente.c 
	gcc -lrt -lm -lpthread -Wall -g -o cliente cliente.c
	
servidor: servidor.c 
	gcc -lrt -lm -lpthread -Wall -g -o servidor servidor.c
	
main: main.c cliente servidor
	gcc -lrt -lm -lpthread -Wall -g -o main main.c
	
clean:
	rm -f main cliente servidor

run: main
	./main
