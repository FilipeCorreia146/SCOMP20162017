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
#include <time.h>
#include "ex07.h"

int main(int argc, char* argv[]){
	sem_t *semaforo, *semaforo1;
	int data_size = sizeof(info);

    int fd = shm_open(SHM_NAME, O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd <0) {
		perror("Erro no shm_open");
		exit(1);
	}
	
	if(ftruncate(fd, data_size) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	
	info* shared_data = (info*) mmap(NULL, data_size, PROT_READ | PROT_WRITE, 
		MAP_SHARED, fd, 0);
		
	if(shared_data == NULL) {
		perror("Erro no unmmap");
		exit(3);
	}
	
	if ((semaforo = sem_open("semaforo", O_CREAT)) == SEM_FAILED) {
        perror("Erro no sem_open()");
        exit(1);
    }
    
    if ((semaforo1 = sem_open("semaforo1", O_CREAT)) == SEM_FAILED) {
        perror("Erro no sem_open()");
        exit(1);
    }
    
    sem_post(semaforo1);
	sem_wait(semaforo);
	
	printf("Número do bilhete:%d", shared_data->bilhetes);
	
	if(sem_close(semaforo)< 0) {
		perror("sem_close()");
		exit(EXIT_FAILURE);
	}
	
	if(sem_close(semaforo1)< 0) {
		perror("Erro no sem_close()");
		exit(EXIT_FAILURE);
	}
		
	return 0;
}
