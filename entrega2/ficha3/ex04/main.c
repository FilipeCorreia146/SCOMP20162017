#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include "ex04.h"

int main(int argc, char* argv[]){
	int num_processes = 10;
	int elem = 1000;
	int num_searches = 100;
	int max = 0;
	int i, j;
	pid_t pid;
	int array[elem];
	srand(time(NULL));
	
	int data_size = sizeof(Biggest);
	int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	
	for (i = 0; i < elem; i++) {
		array[i] = rand()%1001; /*Vai de 0 a 1000*/
	}
	
	if(fd <0) {
		perror("Erro");
		exit(1);
	}
	if(ftruncate(fd, data_size) < 0) {
		perror("Erro");
		exit(2);
	}
	
	Biggest* shared_data = (Biggest*) mmap(NULL, data_size, PROT_READ | PROT_WRITE, 
		MAP_SHARED, fd, 0);
		
	if(shared_data == NULL) {
		exit(3);
	}
	
	for (i = 0; i < num_processes; i++){
		pid = fork();
		if(pid < 0) {
			perror("Erro no fork");
			exit(-1);
		}
		if(pid == 0){
			max = 0;
			for (j = i*num_searches; j < (i*num_searches)+num_searches; j++) {
				if(array[j] >= max) {
					max = array[j];
				}
			}
			shared_data->local_max_size[i] = max;	
			exit(1);	
		}
	}
	
	for (i = 0; i < num_processes; i++) {
		wait(NULL);
	}

	for (i = 0; i < 10; i++)
	{
		printf("%d\n",shared_data->local_max_size[i]);
	}
	

	max = 0;
	for (i = 0; i < ARRAY_SIZE; i++) {
		if(shared_data->local_max_size[i] >= max) {
			max = shared_data->local_max_size[i];
		}
	}
	printf("Global maximum: %d\n", max);

	if(munmap(shared_data, data_size)<0) {
		exit(4);
	}

	if(close(fd) < 0) {
		exit(6);
	}
	
	if(shm_unlink(SHM_NAME) < 0) {
		exit(5);
	}
	
	
	
	
	return 0;
}
