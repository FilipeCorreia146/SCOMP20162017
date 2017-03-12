#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include "sys.h"
#include "split.h"

int main(int argc, char **argv){

	char * command = argv[1];

	sys(command);

	return 0;
}
