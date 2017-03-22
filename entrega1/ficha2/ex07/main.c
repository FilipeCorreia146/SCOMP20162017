#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	const int NUM_PROCESS = 10;

	pid_t pid[NUM_PROCESS];

	int fd[2], i;

	pipe(fd);

	for( i = 0; i< NUM_PROCESS; i++){

		pid[i] = fork();

		if(pid[i] == 0){

			break;

		}

	}

	if( i >= 0 && i< NUM_PROCESS){

		close(fd[1]);

		char readbuffer[5];

		int numbuffer;

		read(fd[0], &readbuffer, sizeof(readbuffer));

		read(fd[0], &numbuffer, sizeof(int));

		printf("%s, Round:%d, PID:%d\n", readbuffer, numbuffer, getpid());

		close(fd[0]);

		exit(numbuffer);

	}

	if( i  == NUM_PROCESS){

		close(fd[0]);

		char msg[5] = "Win!";

		for(i = 1; i<NUM_PROCESS+1; i++){

			sleep(2);

			write(fd[1], &msg, sizeof(msg));

			write(fd[1], &i, sizeof(i));

		}

		for(i = 0; i< NUM_PROCESS; i++){

			int status;			
			wait(&status);

			if(WIFEXITED(status)){

				printf("ROUND: %d\n", WEXITSTATUS(status));

			}

		}

		close(fd[1]);

	}

	return 0;
}
