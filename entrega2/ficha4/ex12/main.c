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

#define MAX_CLIENTES 10

int main(){
	sem_t *semaforo_cliente, *semaforo_espera, *semaforo_servidor;
	pid_t pid;
	int i;
	
	if((semaforo_espera = sem_open("semaforo_espera", O_CREAT, 0644, MAX_CLIENTES)) == SEM_FAILED) {
		perror("sem_open()");
		exit(-1);
	}
	
	if((semaforo_servidor = sem_open("semaforo_servidor", O_CREAT, 0644, 3)) == SEM_FAILED) {
		perror("sem_open()");
		exit(-1);
	}
	
	if((semaforo_cliente = sem_open("semaforo_cliente", O_CREAT, 0644, 0)) == SEM_FAILED) {
		perror("sem_open()");
		exit(-1);
	}
	
	for(i = 0; i < 10; i++) {
		pid = fork();
		if(pid == 0) {
			if(i<3){
				execlp("./servidor", "servidor", (char *) NULL);
				exit(0);
			} else {
				sleep(1);
				execlp("./cliente", "cliente", (char *) NULL);
				exit(0);
			}
		}
	}
	
	for(i = 0; i < 10; i++) {
		wait(NULL);
	}
	
	if (sem_unlink("semaforo_cliente") < 0) {
		perror("Erro no sem_unlink()");
		exit(EXIT_FAILURE);
	}
	
	if (sem_unlink("semaforo_servidor") < 0) {
		perror("Erro no sem_unlink()");
		exit(EXIT_FAILURE);
	}
	
	if (sem_unlink("semaforo_espera") < 0) {
		perror("Erro no sem_unlink()");
		exit(EXIT_FAILURE);
	}

	return 0;
	
}
