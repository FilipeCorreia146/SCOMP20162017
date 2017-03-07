#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include"cria_gemeos.h"

int main(void){

	int i;
	int reps = 3;

	pid_t lista[2];
	char ret;

	for(i = 0; i<reps; i++){

		ret = cria_gemeos(lista);

		if( ret == 'a'){
		
			printf("PID:%d, PPID:%d, Return:%c\n", getpid(), getppid(), ret);

			exit(0);

		}

		if( ret == 'b'){
			int status;

			waitpid(lista[0], &status, 0);

			printf("PID:%d, PPID: %d, Return:%c\n", getpid(), getppid(), ret);

			exit(0);

		}else{
			int status;

			waitpid(lista[0],&status, 0);

			waitpid(lista[1], &status, 0);

			printf("PID1: %d, PID2: %d\n", lista[0], lista[1]);

		}
	}

return 0;
}
