#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	const int BUFFER_SIZE = 80;

	char buffer[BUFFER_SIZE];

	pid_t pid;

	int fd[2], n;

	if( pipe(fd) == -1){

		perror("Falha no pipe");
		return -1;

	}

	pid = fork();

	if( pid < 0){

		perror("Falha no fork!");

	}

	if( pid > 0){

		close(fd[1]);

		while((n = read(fd[0], buffer, 80)) > 0){

			buffer[n-1] = 0;
			printf("%s\n", buffer);

		}

		close(fd[0]);
		wait(NULL);
		exit(0);

	}
	if( pid == 0){

		close(fd[0]);

		dup2(fd[1],1);

		close(fd[1]);

		execlp("sort", "sort", "fx.txt", (char*) NULL);

		perror("Exec error");

		exit(1);

	}

	return 0;

}
