#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "ex01.h"

int main (int argc, char** argv){

	int data_size = sizeof(aluno);

	int fd = shm_open(SHM_NAME, O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);

	if(fd < 0){

		perror("Error creating file");
		exit(1);

	}
	
	if(ftruncate(fd, data_size) < 0){

		perror("Error defining size");
		exit(2);
	}

	aluno * shared_data = (aluno *) mmap(NULL, data_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if(shared_data == NULL){

		perror("Mapping error");
		exit(3);

	}

	printf("Numero: %d\n", shared_data->numero);
	printf("Nome: %s\n", shared_data->nome);

	if(munmap(shared_data, data_size)<0){

		perror("Unmapping error");
		exit(4);

	}

	if((argc>1) && (strcmp( "-rm", argv[1]) == 0)){

		if(shm_unlink(SHM_NAME) <0){
			
			perror("Error removing shared memory");
			exit(5);
		}else{

			if(close(fd) <0){

				perror("Error closing shared memory");
				exit(6);
			}

		}

	}

	return 0;

}
