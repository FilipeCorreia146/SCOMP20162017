#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void){
	int num_filhos = 3;
	pid_t pid [num_filhos];
	int f;
	int i;
	
	pid[0] = fork();
	if(pid <0){
		perror("Erro ao criar o processo.");
		exit(-1);
	}
	for(f=0; f<2; f++){
		if(pid>0){
			printf("Eu sou o pai \n");
			pid[f+1] = fork();
		}
		else{
			sleep(1);
			exit(f+1);
		}
	}
	for(i = 0; i < num_filhos; i++){
		if(pid[i] >0){
			for(f = 0; f < num_filhos; f++){
				wait(NULL);
			}
	
	return 0;	
}

