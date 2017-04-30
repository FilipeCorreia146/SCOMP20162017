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
#include "ex13.h"

int main(int argc, char** argv) {

	char name[6];
	int i, priority, val;
	sem_t *full[N_PRIORITIES];
	sem_t *mutex;
	sem_t *empty[N_PRIORITIES];
	int data_size = sizeof(buffer);

	for(i=0;i< N_PRIORITIES; i++) {

		sprintf(name, "full%d", i);

		if((full[i] = sem_open(name, O_CREAT, 0644, 0)) == SEM_FAILED) {
			perror("Error at first semaphore");
			exit(-1);
		}
	}

	if((mutex = sem_open("mutex", O_CREAT, 0644,1)) == SEM_FAILED)  {
		perror("Error at second semaphore");
		exit(-1);
	}

	for(i=0; i<N_PRIORITIES; i++) {

		sprintf(name, "empt%d", i);

		if((empty[i] = sem_open(name, O_CREAT, 0644, LINE_SIZE)) == SEM_FAILED) {
			perror("Error at third semaphore");
			exit(-1);
		}
	}

	int fd = shm_open(SHM_NAME, O_CREAT| O_RDWR, S_IRUSR | S_IWUSR);

	if(fd<0) {
		perror("Error creating file");
		exit(-1);
	}

	if(ftruncate(fd, data_size) < 0) {
		perror("Error defining size");
		exit(-1);
	}

	buffer * shared_data = (buffer *) mmap(NULL, data_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if(shared_data == NULL) {
		perror("Mapping error");
		exit(-1);
	}

	for(i=0; i<N_PRIORITIES; i++) {
		sem_getvalue(full[i],&val);
		if(val>0) {
			priority=i;
			break;
		}
	}

	sem_wait(full[priority]);
	sem_wait(mutex);

	printf("Prioridade: %d, Mensagem: %s.\n", priority, shared_data->priorityQueue[priority][val-1]);

	sem_post(mutex);
	sem_post(empty[priority]);


	if(munmap(shared_data, data_size)<0) {

		perror("Unmapping error");
		exit(-1);

	}

	if(close(fd)<0) {

		perror("Closing error");
		exit(-1);

	}

	if((argc>1) && (strcmp( "-rm", argv[1]) == 0)) {

		if(shm_unlink(SHM_NAME) <0) {	
			perror("Error removing shared memory");
			exit(-1);
		}
		
		if(sem_close(mutex)<0) {
			perror("Error closing mutual exclusion semaphore");
			exit(-1);
		}
		
		for(i=0;i< N_PRIORITIES; i++) { 
			if(sem_close(full[i]) <0) {
				perror("Error closing semaphore");
				exit(-1);
			}

			if(sem_close(empty[i]) <0) {
				perror("Error closing semaphore");
				exit(-1);
			}
		}

		if(sem_unlink("mutex")<0) {
			perror("Error unlinking mutual exclusion semaphore");
			exit(-1);
		}

		for(i=0;i< N_PRIORITIES; i++) { 

			sprintf(name, "full%d", i);
			if(sem_unlink(name) <0) {
				perror("Error unlinking semaphore");
				exit(-1);
			}
			
			sprintf(name, "empt%d", i);
			if(sem_unlink(name) <0) {
				perror("Error unlinking semaphore");
				exit(-1);
			}

		}

	}
	

	return 0;
}

