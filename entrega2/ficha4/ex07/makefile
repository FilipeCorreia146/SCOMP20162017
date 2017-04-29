atendedor: atendedor.c ex07.h
	gcc -lrt -lm -lpthread -Wall -g -o atendedor atendedor.c
	
cliente: cliente.c ex07.h
	gcc -lrt -lm -lpthread -Wall -g -o cliente cliente.c
	
clean:
	rm -f cliente atendedor

run_cliente: cliente 
	./cliente
	
run_atendedor: atendedor
	./atendedor
