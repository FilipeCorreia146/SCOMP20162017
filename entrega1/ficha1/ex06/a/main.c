#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
	int i;
	int j;
	int vec_length = 100000;
	int result[vec_length];
	int vec [vec_length];
	pid_t pid;
	int status;
	
	for (i = 0; i < vec_length; i++){ /*Preenche o vetor com números random*/
		vec[i] = i;
	}
	
	pid = fork();
	
	if(pid<0){
		perror("Erro no fork");
		exit(-1);
	}

	if(pid == 0){
		j = 0;
		vec_length = 50000;
	} else{
		j = 50000;
		vec_length = 100000;
	}
	
	for (i = j; i < vec_length; i++){
		result[i] = vec[i]*4 + 20;
	}

	wait(&status);
	if(pid == 0){
		printf("\nresult: ");
		for(i = 0; i < 50000; i++){
			printf("%d, ", result[i]);
		}
	}else{
		for(i = 50000; i < 100000; i++){
			printf("%d, ", result[i]);
		}
	}

	
	return 0;
	
}
