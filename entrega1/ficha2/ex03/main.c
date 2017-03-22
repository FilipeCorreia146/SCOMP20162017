#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void){

	pid_t pid;

	int fd[2];

	pipe(fd);

	pid = fork();

	if(pid < 0){

		perror("Erro no fork");

		exit(-1);

	}

	if( pid > 0){

		close(fd[0]);

		char str[] = "Hello world!";

		int length;

		length = strlen(str) +1;

		write(fd[1], &length, sizeof(int));

		write(fd[1], str, strlen(str)+1);

		char str2 [] = "Goodbye!";

		length = strlen(str2) +1;

		write(fd[1], &length, sizeof(int));

		write(fd[1], str2, strlen(str2)+1);

		close(fd[1]);

		wait(NULL);

	}
	if( pid == 0){

		close(fd[1]);

		int readbuffer1;

		while(read(fd[0], &readbuffer1, sizeof(readbuffer1))>0){

			char readbuffer2[readbuffer1];

			read(fd[0], &readbuffer2, sizeof(readbuffer2));

			printf("%s\n", readbuffer2);

		}

		close(fd[0]);

	}


	return 0;

}
