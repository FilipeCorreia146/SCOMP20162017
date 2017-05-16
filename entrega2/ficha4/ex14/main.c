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
#include <sys/wait.h>

int main(){
	sem_t *semaforo_sala, *semaforo_visitante;
	pid_t pid;
	int i;

	if((semaforo_sala = sem_open("semaforo_sala", O_CREAT,0644, 1)) == SEM_FAILED){
		perror("Erro no sem_open");
		exit(-1);
	}

	if((semaforo_visitante = sem_open("semaforo_visitante", O_CREAT, 0644, 5)) == SEM_FAILED){
		perror("Erro no sem_open");
		exit(-1);
	}

	for(i = 0; i < 10; i++) { /*Como se existissem 9 visitantes para testar*/
		pid = fork();
		if(pid == 0){
			if(i == 0) {
				execlp("./sala", "sala",(char *) NULL);
				exit(0);
			} else {
				sleep(1);
				execlp("./visitantes", "visitantes", (char *) NULL);
				exit(0);
			}
		}
	}

	for(i = 0; i <10; i++) {
		wait(NULL);
	}

	if (sem_unlink("semaforo_sala") < 0) {
		perror("Erro no sem_unlink()");
		exit(EXIT_FAILURE);
	}
	
	if (sem_unlink("semaforo_visitante") < 0) {
		perror("Erro no sem_unlink()");
		exit(EXIT_FAILURE);
	}
	

	return 0;
}
