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

#define CHILD_NUM 7
#define FILE_NAME "ficheiro.txt"

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

		if((fp=fpopen(FILE_NAME,"a"))<0) {
			perror("Couldn't open file");
			exit(3);
		}

		fprintf(fp,
	}
	if(pid>0) {
	}

	return 0;
}
