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

#define CHILD_NUM 2
#define VALUES 30
#define SHM_NAME "shm_ex09"

typedef struct{
	int array [10];
	int position;
	int end;
}buffer;

int main(void) {

	int i;
	pid_t pid;
	sem_t *producer;
	sem_t *consumer;
	int data_size = sizeof(buffer);
	int fd = shm_open(SHM_NAME, O_CREAT|O_EXCL| O_RDWR, S_IRUSR | S_IWUSR);

	if((producer = sem_open("producer", O_CREAT|O_EXCL, 0644, 1)) == SEM_FAILED) {
		perror("Error at first semaphore");
		exit(1);
	}

	if((consumer = sem_open("consumer", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("Error at second semaphore");
		exit(2);
	}

	if(fd<0) {
		perror("Error creating file");
		exit(3);
	}

	if(ftruncate(fd, data_size) < 0) {
		perror("Error defining size");
		exit(4);
	}

	buffer * shared_data = (buffer *) mmap(NULL, data_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if(shared_data == NULL) {
		perror("Mapping error");
		exit(5);
	}

	shared_data->position = 10;

	for(i = 0; i<CHILD_NUM; i++) {
		pid = fork();
		if(pid == 0){
			break;
		}
	}
	
	if(pid<0) {
		perror("Fork error");
		exit(6);
	}
	
	if(pid==0) {
		int incrementer = 0;
		sem_wait(producer);
		
		for(;;) {
			shared_data->position = shared_data->position - 1;
			shared_data->array[shared_data->position] = incrementer;
			if(shared_data->position == 0) {
				sem_post(consumer);
				sem_wait(producer);
			}
			if(shared_data->end == (VALUES-1)) {
				break;
			}
			incrementer++;
		}

		exit(1);
	}
	
	if(pid>0) {

		sem_wait(consumer);
		for(i=0; i<VALUES; i++) {
			printf("Valor: %d\n", shared_data->array[shared_data->position]);
			shared_data->position = shared_data->position + 1;
			shared_data->end = shared_data->end + 1;

			if(shared_data->position == 10) {
				sem_post(producer);
				sem_wait(consumer);
			}
		}

		if(sem_close(producer)<0) {
			perror("Error closing producer");
			exit(7);
		}
		
		if(sem_close(consumer)<0) {
			perror("Error closing consumer");
			exit(8);
		}
		
		if(sem_unlink("producer")<0) {
			perror("Error unlinking producer");
			exit(9);
		}
		
		if(sem_unlink("consumer")<0) {
			perror("Error unlinking consumer");
			exit(10);
		}

	}
	
	if(munmap(shared_data, data_size)<0) {
		perror("Unmapping error");
		exit(11);
	}

	if(close(fd)<0) {
		perror("Error closing shared memory");
		exit(12);
	}

	if(shm_unlink(SHM_NAME)<0) { 
		perror("Error closing shared memory");
		exit(13);
	}

	return 0;
}
