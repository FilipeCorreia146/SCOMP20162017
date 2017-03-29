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

int main (void){

	int data_size = sizeof(aluno);

	int fd = shm_open(SHM_NAME, O_CREAT|O_EXCL| O_RDWR, S_IRUSR | S_IWUSR);

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

	printf("Insert a number: ");
	scanf("%d", &shared_data->numero);

	printf("Insert a name: ");
	scanf("%s", shared_data->nome);

	if(munmap(shared_data, data_size)<0){

		perror("Unmapping error");
		exit(4);

	}

	if(close(fd)<0){

		perror("Closing error");
		exit(5);

	}

	return 0;

}
