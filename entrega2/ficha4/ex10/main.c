#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include "ex10.h"	


int main(){
	/*Para executar o leitor e o escritor*/
	int fd, fd2, i;
	int data_size = 100 * sizeof(char);
	int size_contadores = sizeof(contadores);
	sem_t *semaforo_contadores, *semaforo_escritores;
	pid_t pid;
	
	fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd <0) {
		perror("Erro no shm_open");
		exit(1);
	}
	
	if(ftruncate(fd, data_size) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	
	char *shared_data = (char *) mmap(NULL, data_size, PROT_READ | PROT_WRITE, 
	MAP_SHARED, fd, 0);


	fd2 = shm_open(SHM_CONTADORES, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd2 < 0) {
		perror("Erro no shm_open");
		exit(1);
	}

	if(ftruncate(fd2, size_contadores) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	
	contadores *cont = (contadores *) mmap(NULL, size_contadores, PROT_READ | PROT_WRITE,
	 MAP_SHARED, fd2, 0);
	
	if((semaforo_contadores = sem_open("semaforo_contadores", O_CREAT, 0644, 1)) == SEM_FAILED){
		perror("Erro no sem_open");
		exit(-1);
	}
	
	if((semaforo_escritores = sem_open("semaforo_escritores", O_CREAT, 0644, 1)) == SEM_FAILED){
		perror("Erro no sem_open");
		exit(-1);
	}
	
	for(i = 0; i < 10; i++){
		pid = fork();
		if(pid == 0){
			if((i % 2) == 0){
				execlp("./escritor", "escritor", (char*)NULL);
				exit(0);
			}else{
				execlp("./leitor", "leitor", (char*)NULL);
				exit(0);
			}
		}
	}
	
	for(i = 0; i < 10; i++){
		wait(NULL);
	}
	
	if(munmap(shared_data, data_size)<0) {
		perror("Erro no munmap");
		exit(5);
	}

	if(close(fd)<0) {
		perror("Erro no close");
		exit(6);
	}
	
	if(shm_unlink(SHM_NAME) < 0) {
		exit(5);
	}
	
	
	if(munmap(cont, size_contadores)<0) {
		perror("Erro no munmap");
		exit(5);
	}

	if(close(fd2)<0) {
		perror("Erro no close");
		exit(6);
	}
	
	if(shm_unlink(SHM_CONTADORES) < 0) {
		exit(5);
	}	
	
	
	if (sem_unlink("semaforo_contadores") < 0) {
		perror("sem_unlink()");
		exit(EXIT_FAILURE);
	}
	
	if (sem_unlink("semaforo_escritores") < 0) {
		perror("sem_unlink()");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}

	
