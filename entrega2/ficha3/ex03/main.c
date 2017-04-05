#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define SHM_NAME "/shm_ex03"
#define NUM_REPS 10000000

int main(void){

	int data_size = sizeof(int);

	int fd = shm_open(SHM_NAME, O_CREAT|O_EXCL| O_RDWR, S_IRUSR | S_IWUSR);

	if(fd < 0){

		perror("Error creating file");
		exit(1);

	}
	
	if(ftruncate(fd, data_size) < 0){

		perror("Error defining size");
		exit(2);
	}

	int * shared_data = (int *) mmap(NULL, data_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	if(shared_data == NULL){

		perror("Mapping error");
		exit(3);

	}

	*shared_data = 100;

	int i = 0;

	pid_t pid;

	pid = fork();

	if(pid < 0){

		perror("Error on fork");
		exit(4);

	}

	if( pid > 0){

		for(i = 0; i<NUM_REPS; i++){

			*shared_data+=1;
			*shared_data-=1;

			printf("Shared data: %d\n", *shared_data);

		}

	}
	if(pid == 0){

		for(i = 0; i<NUM_REPS; i++){

			*shared_data+=1;
			*shared_data-=1;

			printf("Shared data: %d\n", *shared_data);

		}

		exit(8);

	}

	if(munmap(shared_data, data_size)<0){

		perror("Unmapping error");
		exit(5);

	}


	if(close(fd) < 0) {

		perror("Error closing shared memory");
		exit(6);

	}

	if(shm_unlink(SHM_NAME) <0){
			
		perror("Error removing shared memory");
		exit(7);
	}

	return 0;

}
