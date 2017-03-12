#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int sys(char ** command){

	pid_t pid;

	pid = fork();

	if( pid < 0){

		perror("Erro no fork");

		exit(-1);

	}
	if( pid == 0){

		execvp(command[0], command);

	}

	if( pid > 0){

		int status;

		wait(&status);

		if(WIFEXITED(status)){

			return status;

		}

	}

	return 0;

}

	

