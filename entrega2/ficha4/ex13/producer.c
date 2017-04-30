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
#include <time.h>

int main(void) {
	
	char name[6];
	int i, priority, val;
	sem_t *full[N_PRIORITIES];
	sem_t *mutex;
	sem_t *empty[N_PRIORITIES];
	int data_size = sizeof(buffer);
	srand(time(NULL));

	for(i=0;i< N_PRIORITIES; i++) {

		sprintf(name, "full%d", i);

		if((full[i] = sem_open(name, O_CREAT, 0644, 0)) == SEM_FAILED) {
			perror("Error creating  semaphore");
			exit(-1);
		}
	}

	if((mutex = sem_open("mutex", O_CREAT, 0644,1)) == SEM_FAILED)  {
		perror("Error creating semaphore");
		exit(-1);
	}

	for(i=0; i<N_PRIORITIES; i++) {

		sprintf(name, "empt%d", i);

		if((empty[i] = sem_open(name, O_CREAT, 0644, LINE_SIZE)) == SEM_FAILED) {
			perror("Error creating semaphore");
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

	priority = rand()%4;

	sem_wait(empty[priority]);
	sem_wait(mutex);

	sem_getvalue(full[priority], &val);

	printf("Insira uma mensagem: ");
	scanf("%40[0-9a-zA-Z ]", shared_data->priorityQueue[priority][val]);

	sem_post(mutex);
	sem_post(full[priority]);

	if(munmap(shared_data, data_size)<0){

		perror("Unmapping error");
		exit(-1);

	}

	if(close(fd)<0){

		perror("Closing error");
		exit(-1);

	}
	

	return 0;
}
