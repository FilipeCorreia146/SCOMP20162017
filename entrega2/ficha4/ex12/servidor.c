#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>

#define MAX_CLIENTES 10

int main(){
	sem_t *semaforo_cliente, *semaforo_espera, *semaforo_servidor;
	int i;
	
	if((semaforo_cliente = sem_open("semaforo_cliente", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open()");
		exit(-1);
	}
	
	if((semaforo_espera = sem_open("semaforo_espera", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open()");
		exit(-1);
	}
	
	if((semaforo_servidor = sem_open("semaforo_servidor", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open()");
		exit(-1);
	}
	
	
	for(i = 0; i < 2; i++){
		/*Quando semaforo passa a 1, existe um cliente*/
		sem_wait(semaforo_cliente);
		int num_clientes;
		sem_getvalue(semaforo_espera, &num_clientes);
		/*Para verificar se existe clientes*/
		if(num_clientes != MAX_CLIENTES) {
			/*Para verificar se exite servidores livres*/
			if(sem_trywait(semaforo_servidor) > -1) {
				/*Para diminuir o número de clientes na fila de espera*/
				sem_post(semaforo_espera);
				printf("Cliente atendido\n");
				sleep(1);
				printf("Saiu cliente da fila\n");
				/*Ficou mais um servidor livre*/
				sem_post(semaforo_servidor);	
			}
		}
	}
	
	return 0;
}
	
