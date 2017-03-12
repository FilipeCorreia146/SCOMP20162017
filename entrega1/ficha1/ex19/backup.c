#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void backup( char *  file){

	pid_t pid;

	pid = fork();

	if(pid < 0){

		perror("Erro no fork");

		exit(-1);

	}

	if( pid == 0){

		char * command[] = { "cp", file, "./backup", (char*) NULL};

		execvp(command[0], command);

		perror("Erro ao iniciar a cópia");

		exit(-1);
	}

	if(pid > 0){

		int status;

		wait(&status);

		if(!WIFEXITED(status)){

				printf("Ocorreu um erro ao copiar o ficheiro");

			}

		}

}


