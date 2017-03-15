#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void){

	pid_t pid;

	int fd[2];

	char readbuffer[80];

	pipe(fd);

	pid = fork();

	if(pid < 0){

		perror("Erro no fork");

		exit(-1);

	}

	if( pid > 0){

		close(fd[0]);

		char str[] = "Hello world!";

		write(fd[1], str, strlen(str));

		char str2 [] = "Goodbye!";

		write(fd[1], str2, strlen(str2)+1);

		close(fd[1]);

		wait(NULL);

	}
	if( pid == 0){

		close(fd[1]);

		while(read(fd[0],readbuffer, sizeof(readbuffer))>0){

			printf("%s\n", readbuffer);

		}

		close(fd[0]);

	}


	return 0;

}
