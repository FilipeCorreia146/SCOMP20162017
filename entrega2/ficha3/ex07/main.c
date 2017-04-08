#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "ex07.h"

int main(void){

	int in=0; int out=0, cont = EXCHANGE_NUM;
	int data_size = sizeof(storage);
	int fd = shm_open(SHM_NAME, O_CREAT|O_EXCL| O_RDWR, S_IRUSR | S_IWUSR);
	pid_t pid;

	if(fd<0) {
		perror("Error creating file");
		exit(1);
	}
	
	if(ftruncate(fd, data_size) < 0) {
		perror("Error defining size");
		exit(2);
	}

	storage * shared_data = (storage *) mmap(NULL, data_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if(shared_data == NULL){
		perror("Mapping error");
		exit(3);
	}

	shared_data->counter = 0;

	pid = fork();

	if(pid<0) {
		perror("Error on fork");
		exit(4);
	}

	if(pid>0) {
		int nextProduced = 0;

		while(cont>=0) {

			nextProduced = nextProduced + 1;

				while(shared_data->counter == BUFFER_SIZE) sleep(1);
				
				shared_data->buffer[in] = nextProduced;
				in = (in+1) % BUFFER_SIZE;
				shared_data->counter++;
				cont--;
		}
	}

	if(pid==0) {
		int nextConsumed;

		while(cont>=0) {

			while(shared_data->counter==0) sleep(1);

			nextConsumed = shared_data->buffer[out];
			out = (out+1) % BUFFER_SIZE;
			shared_data->counter--;
			cont--;
			printf("Consumed: %d\n",nextConsumed);
		}

		exit(1);
	}

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

	return 0;

}
