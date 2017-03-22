#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int vec_size = 1000;
	int vec1[vec_size];
	int vec2[vec_size];
	int result[vec_size];
	int num_proce = 5;
	int fd[num_proce][2];
	int i;
	int soma;
	pid_t pid;
	
	for (i = 0; i < vec_size; i++){
		vec1[i] = i;
		vec2[i] = i;
	}
	
	for (i = 0; i < num_proce; i++){
		if(pipe(fd[i]) == -1){
			perror("Erro na criação do pipe");
			exit(-1);
		}
	}
	
	for (i = 0; i < num_proce; i++){
		pid = fork();
		if(pid < 0){
			perror("Erro no fork");
			exit(-1);
		}
		if(pid == 0){
			int j;
			close(fd[i][0]);
			for (j = 200*i; j < j+200; j++){
				soma = vec1[j]+vec2[j];
				write(fd[i][1],&soma, sizeof(soma));
			}
			close(fd[i][1]);
			exit(0);
		}
	}
	
	for (i = 0; i < num_proce; i++){
		wait(NULL);
	}
	
	
	for (i = 0; i < num_proce; i++){
		int pos = 200*i;
		close(fd[i][1]);
		while(read(fd[i][0], &result[pos], sizeof(int)) > 0){
			pos++;
		}		
		close(fd[i][0]);
	}
	
	
	for (i = 0; i < 10; i++){
		printf("%d\n", result[i]);
	}
	
	
	
	return 0;
}
