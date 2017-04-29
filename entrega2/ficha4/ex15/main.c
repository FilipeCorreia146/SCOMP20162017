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

#define CAR_NUM 20

int main(void) {
	
	int i, val;
	sem_t *east; //*East traffic*//
	sem_t *west;//*West  traffic*//
	sem_t *bridge;//*No cars on the bridge*//
	pid_t pids[CAR_NUM];

	if((east = sem_open("east", O_CREAT|O_EXCL, 0664, 0)) == SEM_FAILED) {
		perror("Error at first semaphore");
		exit(-1);
	}

	if((west = sem_open("west", O_CREAT|O_EXCL, 0644, 0)) == SEM_FAILED) {
		perror("Error at second semaphore");
		exit(-1);
	}

	if((bridge = sem_open("bridge", O_CREAT|O_EXCL, 0644, 1)) == SEM_FAILED){
		perror("Error at third semapore");
		exit(-1);
	}

	for(i=0; i<CAR_NUM; i++){

		pids[i] = fork();

		if(pids[i]<0) {
			perror("Forking error");
			exit(-1);
		}

		if(pids[i]==0) {
			break;
		}

	}

	if(i%2 == 0) {
		printf("Carro n%d de este chegou à ponte\n", i);

		sem_getvalue(east, &val);
		if(val == 0) {
			sem_wait(bridge);
		}
		sem_post(east);

		printf("Carro n%d na ponte\n", i);

		sem_wait(east);

		printf("Carro n%d saiu da ponte\n", i);
		
		sem_getvalue(east, &val);
		if(val == 0){
			sem_post(bridge);
		}
	}

	if(i%2 != 0) {
		printf("Carro n%d de oeste chegou à ponte\n", i);

		sem_getvalue(west, &val);
		if(val == 0) {
			sem_wait(bridge);
		}
		sem_post(west);

		printf("Carro n%d na ponte\n", i);

		sem_wait(west);

		printf("Carro n%d saiu da ponte\n", i);

		sem_getvalue(west, &val);
		if(val == 0) {
			sem_post(bridge);
		}
	}

	if(i==CAR_NUM) {

		wait(NULL);

		if(sem_close(east)<0) {
			perror("Error closing semaphore(1)");
			exit(-1);
		}

		if(sem_close(west)<0) {
			perror("Error closing semaphore(2)");
			exit(-1);
		}

		if(sem_close(bridge)<0) {
			perror("Error closing semaphore(3)");
			exit(-1);
		}

		if(sem_unlink("east")<0) {
			perror("Error unlinking semaphore(1)");
			exit(-1);
		}

		if(sem_unlink("west")<0) {
			perror("Error unlinking semaphore(2)");
			exit(-1);
		}

		if(sem_unlink("bridge")<0) {
			perror("Error unlinking semaphore(3)");
			exit(-1);
		}

	}


	return 0;

}
