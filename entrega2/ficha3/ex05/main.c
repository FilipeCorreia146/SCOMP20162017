#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "ex05.h"
#include "calculateHighest.h"
#include "calculateLowest.h"
#include "calculateAverage.h"

int main (void) {
	pid_t pid;
	int i, cont=0, highest, lowest;
	float average;
	int data_size = sizeof(aluno);
	int fd = shm_open(SHM_NAME, O_CREAT|O_EXCL| O_RDWR, S_IRUSR | S_IWUSR);

	if(fd<0) {
		perror("Error creating file");
		exit(1);
	}
	
	if(ftruncate(fd, data_size)<0) {
		perror("Error defining size");
		exit(2);
	}

	aluno * shared_data = (aluno *) mmap(NULL, data_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if(shared_data==NULL) {
		perror("Mapping error");
		exit(3);
	}

	shared_data->flag=0;	
	pid = fork();

	if(pid<0) {
		perror("Forking error");
		exit(4);
	}

	if(pid>0) {
		printf("Insert name: \n");
		scanf("%s", shared_data->nome);
		printf("Insert number: \n");
		scanf("%d", &shared_data->numero);
		printf("Insert the subjects' grades:\n");
		for(i=0; i<NR_DISC; i++) {
			printf("Grade %d: ", i+1);
			scanf("%d", &shared_data->disciplinas[i]);
		}
		
		shared_data->flag=1;
		wait(NULL);

		if(munmap(shared_data, data_size)<0) {
			perror("Unmapping error");
			exit(5);
		}

		if(close(fd)<0) {
			perror("Error closing shared memory");
			exit(6);
		}

		if(shm_unlink(SHM_NAME)<0) {
			perror("Error removing shared memory");
			exit(7);
		}
	}

	if(pid==0) {

		while(shared_data->flag!=1) {
			sleep(1);
			cont+=1;
			if(cont>60) {
				perror("Operation time ended without response");
				exit(8);
			}
		}

		highest = calculateHighest(shared_data->disciplinas, NR_DISC);
		lowest = calculateLowest(shared_data->disciplinas, NR_DISC);
		average = calculateAverage(shared_data->disciplinas, NR_DISC);
		printf("The highest grade: %d\n", highest);
		printf("The lowest grade: %d\n", lowest);
		printf("The average: %0.2f\n", average);
		exit(9);
	}

	return 0;
}
