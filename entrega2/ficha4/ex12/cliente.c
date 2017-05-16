#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>
#include <sys/mman.h>
#include <string.h>

int main(){
	
	sem_t *semaforo_cliente, *semaforo_espera, *semaforo_servidor;
	
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
	
	/*Para ver se a fila não está cheia*/
	if(sem_trywait(semaforo_espera) < 0) {
		printf("Fila de espera cheia\n");
	} else {
		printf("Cliente para a fila\n");
		/*Avisa o servidor de que existem clientes na fila*/
		sem_wait(semaforo_espera);
		/*Avisa o servidor que chegou um cliente*/
		sem_post(semaforo_cliente);
	}
	
	
	return 0;
}
