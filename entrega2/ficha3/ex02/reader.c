#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include "ex02.h"

int main(int argc, char* argv[]){
	
	int data_size = sizeof(Numbers);
	int fd = shm_open(SHM_NAME, O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	int average = 0;
	int i, sum = 0;
	
	if(fd <0){
		perror("Erro");
		exit(1);
	}
	if(ftruncate(fd, data_size) < 0){
		perror("Erro");
		exit(2);
	}
	Numbers* shared_data = (Numbers*) mmap(NULL, data_size, PROT_READ | PROT_WRITE, 
		MAP_SHARED, fd, 0);
		
	if(shared_data == NULL){
		exit(3);
	}
	
	do {
		//espera
	} while(shared_data->flag != 1);    /*só pode ler quando a flag estiver a 1*/
	
	for (i = 0; i < ARRAY_SIZE; i++ ) {
		sum = sum + shared_data->array[i] ;
		average = (sum) / (ARRAY_SIZE);
	}

	printf("Average: %d\n", average);
	
	if(munmap(shared_data, data_size)<0){
		exit(4);
	}
	
	if(close(fd) < 0){
		exit(6);
	}
	
	if((argc > 1) && (strcmp("-rm", argv[1]) == 0)){ 
		if(shm_unlink(SHM_NAME) < 0){
			exit(5);
		}
	}
	
	
	
	
	return 0;
}
