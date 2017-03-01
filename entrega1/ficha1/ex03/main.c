#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	pid_t pid;

	int i;

	for(i=0; i<4; i++)
		pid = fork();

	printf("Sistemas de Computadores\n");

	return 0;
}
