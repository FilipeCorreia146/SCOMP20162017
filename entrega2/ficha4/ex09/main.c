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
#define BUFFER_SIZE 10

typedef struct{
	int array [10];
	int pos;
	int end;
}buffer;

int main(void) {

	int i;
	pid_t pid;
	sem_t *full;
	sem_t *mutex;
	sem_t *empty;
	int data_size = sizeof(buffer);

	if((full = sem_open("full", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("Error at first semaphore");
		exit(-1);
	}

	if((mutex = sem_open("mutex", O_CREAT|O_EXCL, 0644,1)) == SEM_FAILED)  {
		perror("Error at second semaphore");
		exit(-1);
	}

	if((empty = sem_open("empty", O_CREAT|O_EXCL, 0644, BUFFER_SIZE)) == SEM_FAILED) {
		perror("Error at third semaphore");
		exit(-1);
	}

	int fd = shm_open(SHM_NAME, O_CREAT|O_EXCL| O_RDWR, S_IRUSR | S_IWUSR);

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

	shared_data->pos = 0;

	for(i = 0; i<CHILD_NUM; i++) {
		pid = fork();
		if(pid == 0){
			break;
		}
	}
	
	if(pid<0) {
		perror("Fork error");
		exit(-1);
	}
	
	if(pid==0) {
		int number = 0;
		do {
			sem_wait(empty);
			sem_wait(mutex);

			shared_data->array[shared_data->pos] = number;
			shared_data->pos = shared_data->pos + 1;
			number++;

			sem_post(mutex);
			sem_post(full);

		} while(shared_data->end != (VALUES-1));
		
		exit(1);
	}

	if(pid>0) {

		do {
			sem_wait(full);
			sem_wait(mutex);

			printf("%d\n", shared_data->array[shared_data->pos]);
			shared_data->pos = shared_data->pos - 1;
			shared_data->end = shared_data->end + 1;

			sem_post(mutex);
			sem_post(empty);

		} while(shared_data->end != (VALUES -1));

		if(sem_close(mutex)<0) {
			perror("Error closing mutual exclusion semaphore");
			exit(-1);
		}
		
		if(sem_close(full)<0) {
			perror("Error closing full semaphore");
			exit(-1);
		}

		if(sem_close(empty)<0) {
			perror("Error closing empty semaphore");
			exit(-1);
		}
		
		if(sem_unlink("empty")<0) {
			perror("Error unlinking empty semaphore");
			exit(-1);
		}
		
		if(sem_unlink("full")<0) {
			perror("Error unlinking full semaphore");
			exit(-1);
		}

		if(sem_unlink("mutex")<0) {
			perror("Error unlinking mutual exclusion semaphore");
			exit(-1);
		}
	}
	
	if(munmap(shared_data, data_size)<0) {
		perror("Unmapping error");
		exit(-1);
	}

	if(close(fd)<0) {
		perror("Error closing shared memory");
		exit(-1);
	}

	if(shm_unlink(SHM_NAME)<0) { 
		perror("Error closing shared memory");
		exit(-1);
	}

	return 0;
}
