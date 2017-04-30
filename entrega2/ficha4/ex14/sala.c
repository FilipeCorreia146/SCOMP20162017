#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <time.h>
#include <semaphore.h>

int main(){
	int fd, *num_visitantes;
	sem_t *semaforo_visitantes, *semaforo_sala;
	int data_size = sizeof(int);
	int i, j;
	
	fd = shm_open("/ex14", O_CREAT |O_RDWR, S_IRUSR|S_IWUSR);

	if(fd < 0){
		perror("Erro no shm_open");
		exit(1);
	}

	if(ftruncate(fd, data_size) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}

	num_visitantes = (int*) mmap(NULL, data_size, PROT_READ|PROT_WRITE,
	 MAP_SHARED, fd, 0);

	if((semaforo_sala = sem_open("semaforo_sala", O_CREAT, 0644, 1)) == SEM_FAILED){
		perror("Erro no sem_open");
		exit(-1);
	}
	
	if((semaforo_visitantes = sem_open("semaforo_visitantes", O_CREAT, 0644, 5)) == SEM_FAILED){
		perror("Erro no sem_open");
		exit(-1);
	}

	for (i = 0; i < 3; i++) { /*Número de sessões em vez de infinitas*/
		sem_wait(semaforo_sala);
		printf("Começou exposição\n");
		sleep(10);
		sem_post(semaforo_sala);
		printf(" %d pessoas na exposição\n", *num_visitantes);

		for(j = 0; j < *num_visitantes; j++){
			sem_post(semaforo_visitantes);
		}
		i++;
		*num_visitantes = 0;
	}
	
	if(munmap(num_visitantes, data_size)<0) {
		perror("Erro no munmap");
		exit(5);
	}

	if(close(fd)<0) {
		perror("Erro no close()");
		exit(6);
	}
	
	
	return 0;
}
