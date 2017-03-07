#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

char cria_gemeos(pid_t lista [2]){

	pid_t pid = getpid();

	int check = 0;

	while(check!=2){
		
		if(pid > 0){
		
		pid = fork();

		lista[check] = pid;

		}
		if(pid < 0){

			exit(-1);

		}
		if(pid ==0){

			if(check ==0){
				return 'a';
			}else{
				return 'b';
			}

		}

		check++;

	}

return 'p';

}
