#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void){

	pid_t p, a;

	p = fork();

	if(p < 0){

		printf("Erro  no primeiro fork\n");

		exit(-1);
	}

	a = fork();

	if(a < 0){

		printf("Erro no segundo fork\n");

		exit(-1);

	}

	printf("Sistemas de Computadores\n");

	return 0;

}
