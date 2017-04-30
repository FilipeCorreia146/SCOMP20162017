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
#include "ex10.h"	

int main(){
	int fd, fd2;
	sem_t *semaforo_contadores, *semaforo_escritores;
	int data_size = 100 * sizeof(char);
	int size_contadores = sizeof(contadores);
		
	fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd <0) {
		perror("Erro no shm_open");
		exit(1);
	}
	
	if(ftruncate(fd, data_size) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	
	char *shared_data = (char *) mmap(NULL, data_size, PROT_READ,
	 MAP_SHARED, fd, 0);
	
	fd2 = shm_open(SHM_CONTADORES, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd2 < 0) {
		perror("Erro no shm_open");
		exit(1);
	}

	if(ftruncate(fd2, size_contadores) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	/*Memória partilhada para os contadores de leitores e escritores*/
	contadores *cont = (contadores *) mmap(NULL, size_contadores, PROT_READ | PROT_WRITE,
	 MAP_SHARED, fd2, 0);
	
	
	if((semaforo_contadores = sem_open("semaforo_contadores", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open");
		exit(-1);
	}
	
	if((semaforo_escritores = sem_open("semaforo_escritores", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open");
		exit(-1);
	}
	
	/*Nenhum incrmementa nem decrementa os contadores*/
	sem_wait(semaforo_contadores);
	cont->leitores++;
	
	/*É 1 para que apenas um dos leitores faça wait*/
	if(cont->leitores == 1) {
		sem_wait(semaforo_escritores);
	}
	
	/*Para libertar os contadores para outros leitores*/
	sem_post(semaforo_contadores);
	printf("\n String: %s , Nº leitores: %d \n", shared_data, cont->leitores);
	sem_wait(semaforo_contadores);
	cont->leitores--;
	
	/*Casoo não existam leitores o escritor pode escrever*/
	if(cont->leitores == 0) {
		sem_post(semaforo_escritores);
	}
	
	sem_post(semaforo_contadores);
	printf("Leitor terminou");
	
	
	return 0;
}
