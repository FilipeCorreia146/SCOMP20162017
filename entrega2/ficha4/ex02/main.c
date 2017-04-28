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
	int i, order;
	sem_t *sem1;
	sem_t *sem2;
	sem_t *sem3;
	sem_t *sem4;
	sem_t *sem5;
	FILE *fp;

	if((sem1 = sem_open("semaforo1", O_CREAT|O_EXCL, 0644, 1)) == SEM_FAILED) {
		perror("No sem_open()");
		exit(1);
	}
	if((sem2 = sem_open("semaforo2", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("No sem_open()");
		exit(2);
	}
	if((sem3 = sem_open("semaforo3", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("No sem_open()");
		exit(3);
	}
	if((sem4 = sem_open("semaforo4", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("No sem_open()");
		exit(4);
	}
	if((sem5 = sem_open("semaforo5", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("No sem_open()");
		exit(5);
	}

	for(i=0; i< CHILD_NUM; i++) {
		pid = fork();
		order = i+1;
		if(pid==0) break;
	}

	if(pid<0) {
		perror("Forking error");
		exit(6);
	}

	if(pid==0) {

		switch(order) {

			case 1:
				sem_wait(sem1);
				break;
			case 2:
				sem_wait(sem2);
				break;
			case 3: 
				sem_wait(sem3);
				break;
			case 4: 
				sem_wait(sem4);
				break;
			case 5:
				sem_wait(sem5);
				break;
			default:
				break;
		}


		if((fp=fopen(FILE_NAME, "a"))<0) {
			perror("Couldn't open file");
			exit(7);
		}

		for(i=0; i<WRITE_NUM; i++) {
			fprintf(fp, "%d\n", i+((order-1)*200));
		}

		if(fclose(fp)<0) {
			perror("Error closing file");
			exit(8);
		}

		switch(order) {

			case 1:
				sem_close(sem1);
				sem_post(sem2);
				break;
			case 2: 
				sem_close(sem2);
				sem_post(sem3);
				break;
			case 3:
				sem_close(sem3);
				sem_post(sem4);
				break;
			case 4: 
				sem_close(sem4);
				sem_post(sem5);
				break;
			case 5:
				sem_close(sem5);
				 break;
			default: 
				 break;
		}
	}

	if(pid>0) {

		int num;

		for(i=0; i<CHILD_NUM; i++) {

			wait(NULL);

		}

		if((fp = fopen(FILE_NAME, "r"))<0) {
			perror("Error openning file");
			exit(9);
		}

		if(fp) {
			while(fscanf(fp, "%d", &num)!= EOF) {
				printf("%d\n", num);
			}

		}

		if(fclose(fp)<0) {
			perror("Error closing file");
			exit(10);
		}

		if(sem_unlink("semaforo1") < 0) {
			perror("Unlinking error");
			exit(11);
		}
		if(sem_unlink("semaforo2") < 0) {
			perror("Unlinking error");
			exit(12);
		}
		if(sem_unlink("semaforo3") < 0) {
			perror("Unlinking error");
			exit(13);
		}
		if(sem_unlink("semaforo4") < 0) {
			perror("Unlinking error");
			exit(14);
		}
		if(sem_unlink("semaforo5") < 0) {
			perror("Unlinking error");
			exit(15);
		}
	}


	return 0;
}
