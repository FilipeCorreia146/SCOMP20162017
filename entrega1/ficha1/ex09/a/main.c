#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(void){

	pid_t pid;

	int i, j, num= 1000001;

	pid = fork();

	if(pid < 0){

		exit(-1);

	}

	if(pid ==0){

		num = num -200000;

	}

	for(i = 0; i<4; i++){

		if(pid == 0){

			pid = fork();
			num = num -200000;

		}	

	}

	wait(NULL);

	for(j = 0; j< 200000; j++){

		printf("%d\n", num++);

	}

	return 0;
}
