#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include "M.h"

int main(void){

	pid_t pid;

	int i ,check = 1;

	char a []  = "A";

	char b [] = "B";

	for( i = 0; i<2; i++){

		if(check ==1){

			pid = fork();

	
			if( pid < 0){

				exit(-1);

			}
			if( pid > 0){

				M(a);

			}else{

				M(b);

				pid = fork();

				if( pid < 0){

					exit(-1);

				}

				if( pid > 0){

					M(a);

					check = 0;

				}

			}

		}

	}	

	return 0;
}
