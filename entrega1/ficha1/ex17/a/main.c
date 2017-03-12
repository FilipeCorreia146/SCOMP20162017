#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include "sys.h"

int main(int argc, char **argv){

	char ** command = NULL;

	command = malloc(sizeof(char*) * (argc-1));

	int i;

	for(i =1; i< argc; i++){

		command[i-1] = argv[i];

	}

	command [argc] = NULL;

	sys(command);

	return 0;
}
