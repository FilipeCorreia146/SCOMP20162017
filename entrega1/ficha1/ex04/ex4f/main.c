#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void){

	pid_t pid;
	int f;
	int status;
	
	pid = fork();
	if(pid <0){
		perror("Erro ao criar o processo.");
		exit(-1);
	}
	for(f=0; f<2; f++){
		if(pid>0){
			printf("Eu sou o pai \n");
			pid = fork();
		}
		else{
			sleep(1);
		}
	}
	wait(&status);
	
	return 0;	
}

