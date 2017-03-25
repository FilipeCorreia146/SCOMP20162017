#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	const int NUM_PROCESSES = 3;

	int fd[2],i, fd1[2];

	pid_t pid[NUM_PROCESSES];

	if(pipe(fd) == -1){

		perror("Pipe falhou");
		return 1;

	}

	if(pipe(fd1) == -1){

		perror("Pipe falhou");
		return 2;

	}


     	for(i = 0; i < NUM_PROCESSES; i++){

		if((pid[i] = fork()) < 0){
			perror("Erro no fork");
		}
		if(pid[i] == 0){

			break;

		}

	}


	if( i == NUM_PROCESSES ){

		close(fd[1]);
		close(fd1[1]);
		close(fd1[0]);
		close(fd[0]);

		wait(NULL);
		wait(NULL);
		wait(NULL);

	}

	if( i == 0){

		close(fd1[0]);
		close(fd1[1]);
		
		close(fd[0]);
		
		dup2(fd[1], 1);
		
		close(fd[1]);

		execlp("ls","ls", "-la", NULL);
		perror("Erro no exec");
		exit(1);

	}

	if(i == 1){

		close(fd[1]);
		close(fd1[0]);

		dup2(fd[0], 0);

		dup2(fd1[1], 1);

		close(fd[0]);
		close(fd1[1]);


		execlp("sort", "sort", NULL);
		perror("Erro no exec");
		exit(2);

	}
	if( i == 2){

		close(fd[1]);
		close(fd[0]);
		close(fd1[1]);

		dup2(fd1[0], 0);

		close(fd[0]);

		execlp("wc", "wc", "-l", NULL);

		perror("Erro no exec");

		exit(3);

	}

	return 0;

}
