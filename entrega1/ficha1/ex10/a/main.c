#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "procurar_num.h"


int main (void){

	int vec_size = 100000;
	int vec[vec_size];
	int num = 99000;
	int num_processos = 5;
	pid_t pid[num_processos];
	int status[num_processos];
	int i;

	for(i = 0; i < vec_size; i++){
		vec[i] = i;
	}

	
	for(i = 0; i < num_processos; i++){
		pid[i] = fork();
		if(pid[i] < 0){
			perror("Erro no fork");
			exit(-1);
		}
		if(pid[i] == 0){
			if(procurar_num(vec + (20000*i), num) == 1){
				exit(i+1);
			}
			exit(0);
		}
	}

	
	for(i = 0; i < num_processos; i++){
		waitpid(pid[i], &status[i], 0);
	}

	i = 0;
	while(WEXITSTATUS(status[i]) == 0){/*Para encontrar o processo que 
		encontrou o num*/
		i++;
	}

	

	if(i < num_processos){
		printf("Processo:%d\n", WEXITSTATUS(status[i]));

	}else{

		printf("Número não encontrado\n");

	}

	return 0;

}
