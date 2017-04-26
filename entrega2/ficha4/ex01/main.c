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

#define CHILD_NUM 5
#define WRITE_NUM 200
#define FILE_NAME "ficheiro.txt"



int main(void) {

	pid_t pid;
	int i;
	sem_t *semaforo;
	FILE *fp;

	if((semaforo = sem_open("semaforo", O_CREAT|O_EXCL, 0644, 1)) == SEM_FAILED) {
		perror("No sem_open()");
		exit(1);
	}

	for(i=0; i< CHILD_NUM; i++) {
		pid = fork();

		if(pid==0) break;
	}

	if(pid<0) {
		perror("Forking error");
		exit(4);
	}

	if(pid==0) {
		sem_wait(semaforo);

		if((fp=fopen(FILE_NAME, "a"))<0){
			perror("Couldn't open file");
			exit(2);
		}

		for(i=0; i<WRITE_NUM; i++){
			fprintf(fp, "%d\n", i);
		}

		if(fclose(fp)<0){
			perror("Error closing file");
			exit(3);
		}

		sem_post(semaforo);
	}

	if(pid>0) {

		int num;

		for(i=0; i<CHILD_NUM; i++) {

			wait(NULL);

		}

		if((fp = fopen(FILE_NAME, "r"))<0) {
			perror("Error openning file");
			exit(4);
		}

		if(fp) {
			while(fscanf(fp, "%d", &num)!= EOF){
				printf("%d\n", num);
			}

		}

		if(fclose(fp)<0) {
			perror("Error closing file");
			exit(5);
		}

		if(sem_unlink("semaforo") < 0) {
			perror("Unlinking error");
			exit(6);
		}
	}


	return 0;
}
