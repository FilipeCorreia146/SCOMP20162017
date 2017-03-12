#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include"cria_gemeos.h"

int main(void){

	const unsigned int TAMANHO = 6;

	int i;
	int reps = 3;

	pid_t lista[TAMANHO];
	char ret;

	for(i = 0; i<reps; i++){

		ret = cria_gemeos(lista + i*2);

		if( ret != 'p' ){
		
			printf("PID:%d, PPID:%d, Return:%c\n", getpid(), getppid(), ret);

			exit(ret);

		}

	}

	int j;

	int status;

	for(j = 0; j< 6; j++){

		waitpid(lista[j], &status, 0);

		if(WIFEXITED(status)){

			printf("TERMINOU O PROCESSO: PID: %d, Return: %c\n", lista [j], WEXITSTATUS(status));

		}

	 }

return 0;
}
