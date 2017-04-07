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

int main(){
	int data_size = sizeof(Numbers);
	int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	srand(time(NULL));
	int i;
	
	if(fd <0){
		perror("Erro na criação da memória partilhada");
		exit(1);
	}
	if(ftruncate(fd, data_size) < 0){
		perror("Erro no truncate");
		exit(2);
	}
	Numbers* shared_data = (Numbers*) mmap(NULL, data_size, PROT_READ | PROT_WRITE, 
		MAP_SHARED, fd, 0);
	
	if(shared_data == NULL){
		perror("Erro na criação da memória partilhada");
		exit(3);
	}
	
	for (i = 0; i < ARRAY_SIZE; i++){
		shared_data->array[i] = rand()%20+1;
		
	}
	shared_data->flag = 1; /*Para indicar que o writer já foi executado*/
	
	
	if(munmap(shared_data, data_size) <0){
		perror("Erro");
		exit(4);
	}
	
	if(close(fd) <0){
		perror("Erro");
		exit(5);
	}
	
	return 0;
}
