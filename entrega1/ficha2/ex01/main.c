#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	int fd[2];

	pipe(fd);

	pid_t pid;

	pid = fork();

	if( pid < 0 ){

		exit(-1);

	}

	if( pid > 0){

		close(fd[0]);

		pid_t my_pid;

		my_pid = getpid();

		printf("PID: %d\n", my_pid);

		write(fd[1], &my_pid, sizeof(my_pid));

		close(fd[1]);

		wait(NULL);

	}

	if( pid == 0){

		close(fd[1]);

		pid_t ppid;

		read(fd[0], &ppid, sizeof(ppid));

		printf("PID pai: %d\n", ppid);

		close(fd[0]);

		exit(0);

	}

	return 0;

}
