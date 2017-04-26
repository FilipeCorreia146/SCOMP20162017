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
#include "countlines.h"

#define LINE_LIMIT 10
#define CHILD_NUM 7

int main(int argc, char * argv[]) {
	
	FILE *fp;
	pid_t pid;
	sem_t * semaforo;
	int i;

	if((semaforo = sem_open("semaforo", O_CREAT|O_EXCL, 0644, 1)) < 0) {
		perror("Error opening semaphore");
		exit(1);
	}

	for(i=0; i<CHILD_NUM; i++) {
		pid = fork();
		if(pid==0) break;
	}

	if(pid<0) {
		perror("Forking error!");
		exit(2);
	}
	if(pid==0) {
		sem_wait(semaforo);

		if((fp=fopen(argv[1],"a"))<0) {
			perror("Couldn't open file");
			exit(3);
		}

		if(countlines(argv[1]) <= LINE_LIMIT) {
			fprintf(fp,"Eu sou o processo com o PID %d\n", getpid());
		} else {
			printf("Não são permitidas mais de 10 linhas por ficheiro!\n");
		}

		sleep(2);

		if(fclose(fp)<0) {
			perror("Error closing file");
			exit(4);
		}

		sem_post(semaforo);
	}

	if(pid>0) {

		for(i=0; i<CHILD_NUM; i++) {
			wait(NULL);
		}

		if(sem_unlink("semaforo")<0) {
			perror("Error unlinking semaphore");
			exit(5);
		}
	}

	return 0;
}
