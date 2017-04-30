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


int main() {
	int fd, *num_visitantes;
	sem_t *semaforo_visitantes;
	int data_size = sizeof(int);
	
	fd = shm_open("/ex14", O_CREAT |O_RDWR, S_IRUSR|S_IWUSR);

	if(fd < 0) {
		perror("Erro no shm_open()");
		exit(1);
	}

	if(ftruncate(fd, data_size) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	
	num_visitantes = (int*) mmap(NULL, data_size, PROT_READ|PROT_WRITE, 
	MAP_SHARED, fd, 0);

	if((semaforo_visitantes = sem_open("semaforo_visitantes", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open");
		exit(-1);
	}

	while(sem_trywait(semaforo_visitantes) < 0) {
		printf("Exposição cheia\n");
		sleep(5);
	}
	
	*num_visitantes += 1;
	printf("Entrou na sala\n");
	

	return 0;
}
