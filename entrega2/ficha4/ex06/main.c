#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

int main(){
	int num_messages = 10;
	pid_t pid;
	sem_t *semaforo0, *semaforo1;
	int i;

	/*O semáforo inicia-se a 0 uma vez que não existe partilha de dados entre os processos*/
	if ((semaforo0 = sem_open("semaforo0", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
        perror("Erro no sem_open()");
        exit(1);
    }
    
    if ((semaforo1 = sem_open("semaforo1", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
        perror("Erro no sem_open()");
        exit(1);
    }
	
	pid = fork();
	
	for (i = 0; i < num_messages; i++) {
		
	
		if(pid == 0) {
			/*filho*/
			sem_wait(semaforo0);
			printf("Eu sou o filho\n");
			sem_post(semaforo1);
		} else {
			sem_post(semaforo0);
			printf("Eu sou o pai\n");
			sem_wait(semaforo1);
			
		}
	}
	
	/*Desta forma apenas um processo faz close e unlink*/
	if(pid > 0) {
		 /* fechar/apagar o semaforo */
		if(sem_close(semaforo0)< 0) {
			perror("sem_close()");
			exit(EXIT_FAILURE);
		}
		
		if(sem_close(semaforo1)< 0) {
			perror("sem_close()");
			exit(EXIT_FAILURE);
		}
	  
		if (sem_unlink("semaforo0") < 0) {
			perror("sem_unlink()");
			exit(EXIT_FAILURE);
		}
		
		if (sem_unlink("semaforo1") < 0) {
			perror("sem_unlink()");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
