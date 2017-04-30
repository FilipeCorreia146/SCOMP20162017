#include <fcntl.h>
#include <sys/types.h>
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
	char string[100];
	int fd, fd2;
	sem_t *semaforo_contadores, *semaforo_escritores;
	int data_size = 100 * sizeof(char);
	int size_contadores = sizeof(contadores);
	time_t tempo = time(NULL);
		
	fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd <0) {
		perror("Erro no shm_open");
		exit(1);
	}
	
	if(ftruncate(fd, data_size) < 0) {
		perror("Erro ftruncate");
		exit(2);
	}
	
	char *shared_data = (char *) mmap(NULL, data_size, PROT_WRITE,
	 MAP_SHARED, fd, 0);
	
	fd2 = shm_open(SHM_CONTADORES, O_CREAT| O_RDWR, S_IRUSR | S_IWUSR);
	
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
	
	
	if((semaforo_contadores = sem_open("semaforo_contadores", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open");
		exit(-1);
	}
	
	if((semaforo_escritores = sem_open("semaforo_escritores", O_CREAT)) == SEM_FAILED) {
		perror("Erro no sem_open");
		exit(-1);
	}
	
	/*Mais nenhum incrementar ou decrementar contadores*/
	sem_wait(semaforo_contadores);
	if(cont->leitores > 0) {
		printf("\nExistem leitores, não escreve\n");
		return -1;
	}
	/*Como só um escritor pode escrever, o semáforo é bloqueado*/
	sem_wait(semaforo_escritores);
	
	cont->escritores++;
	/*Desbloqueia os contadores*/
	sem_post(semaforo_contadores);

	sprintf(string, "Pid: %d, Tempo: %s", getpid(), ctime(&tempo));
	strcpy(shared_data, string);
	printf("\n Nºleitores:%d, Nºescritores: %d \n", cont->leitores, cont->escritores);
	
	/*Como o escritor já escreveu, desbloqueia*/
	sem_post(semaforo_escritores);
	/*Processo igual ao anterior*/
	sem_wait(semaforo_contadores);
	cont->escritores--;
	sem_post(semaforo_contadores);
	
	printf("Escritor terminou\n");
	
	
	return 0;
}

