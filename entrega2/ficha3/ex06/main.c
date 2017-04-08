#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include "ex06.h"

int main(int argc, char* argv[]){
	int num_processes = 10;
	int i;
	char *j, *z;
	char aux[ARRAY_SIZE];
	pid_t pid;
	FILE *file;
	int data_size = sizeof(Search)*num_processes;
	int fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd <0) {
		perror("Erro");
		exit(1);
	}
	
	if(ftruncate(fd, data_size) < 0) {
		perror("Erro");
		exit(2);
	}
	
	Search* shared_data = (Search*) mmap(NULL, data_size, PROT_READ | PROT_WRITE, 
		MAP_SHARED, fd, 0);
	if(shared_data == NULL) {
		exit(3);
	}
	
	for (i = 0; i < num_processes; i++) {
			printf("Qual o nome ou path do ficheiro?\n");
			scanf("%s", (shared_data+i)->path);
			
			printf("Qual a palavra a procurar?\n");
			scanf("%s", (shared_data+i)->word);
			
	}
	
	for (i = 0; i < num_processes; i++) {
		pid = fork();
		if(pid < 0){
			perror("Erro no fork");
			exit(-1);
		}
		if(pid == 0) {
			file = fopen((shared_data+i)->path, "r");
			if(file == NULL){
				perror("Erro na abertura do ficheiro");
				exit(-1);
			}
			while(fgets(aux, ARRAY_SIZE, file)) {
				for (j = aux; strstr(j,(shared_data+i)->word) != NULL; j = z+1) {
					z = strstr(j,(shared_data+i)->word);
					(shared_data+i)->num_occurrences++;
				}
			}
			fclose(file);
			exit(0);
		}
	}
	
		
	for (i = 0; i < num_processes; i++) {
		wait(NULL);
	}
	
	for (i = 0; i < num_processes; i++) {
		printf("\nFilho: %d\nNúmero de ocorrências: %d", i+1, (shared_data+i)->num_occurrences);
	}
	
	
	if(munmap(shared_data, data_size)<0){
		exit(4);
	}
	
	if(close(fd) < 0){
		exit(6);
	}
	
	if(shm_unlink(SHM_NAME) < 0){
			exit(5);
	}
	
	
	return 0;
}

