#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main( int argc, char ** argv){

	pid_t pid;

	int i;

	for(i=1; i< argc; i++){

		pid = fork();

		if( pid <0){

			perror("Erro no fork");

		}

		if( pid == 0){

			char * c[] = { argv[i], NULL};
			execvp(argv[i], c);
			printf("Falha ao executar %s.\n", argv[i]);
			exit(-1);
		}

	}

	for( i =1; i<argc; i++){

		wait(NULL);

	}

	return 0;

}
