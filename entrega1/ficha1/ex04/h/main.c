#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void){
	int num_processos = 3;
	pid_t pid [num_processos];
	int f;
	int status;

	for(f=0; f < num_processos; f++){
		pid[f] = fork();
		if(pid[f] < 0){
			perror("Erro no fork");
			exit(-1);
		}
		if(pid[f]==0){
			sleep(1);
			exit(f);
		}
		printf("Eu sou o pai\n");
	}
	
	waitpid(pid[1], &status, WNOHANG);
	
	return 0;	
}



