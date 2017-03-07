#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void){

	pid_t pid [3];
	int f;
	
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
		}
		
	}
	return 0;	
}

