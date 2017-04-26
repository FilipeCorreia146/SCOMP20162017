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
	pid_t pid;
	sem_t *semaforo;

	/*O semáforo inicia-se a 0 uma vez que não existe partilha de dados entre os processos*/
	if ((semaforo = sem_open("semaforo", O_CREAT | O_EXCL, 0644, 0)) == SEM_FAILED) {
        perror("Erro no sem_open()");
        exit(1);
    }
	
	pid = fork();
	
	if(pid == 0) {
		/*filho*/
		sem_wait(semaforo);
		printf("Eu sou o filho\n");
		exit(0);
	}
	
	printf("Eu sou o pai\n");
	sem_post(semaforo);
	
	 /* fechar/apagar o semaforo */
    if(sem_close(semaforo) < 0) {
        perror("sem_close()");
        exit(EXIT_FAILURE);
    }
  
    if (sem_unlink("semaforo") < 0) {
        perror("sem_unlink()");
        exit(EXIT_FAILURE);
    }
	
	
	return 0;
}
