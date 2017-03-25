#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
	pid_t pid;
	int fd[2];
	int string_size = 3000;
	char string [string_size];
	int j;
	
	
	if(pipe(fd) == -1){
		perror("Erro no pipe");
		exit(-1);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Erro no fork");
		exit(-1);
	}
	
	if(pid > 0){
		close(fd[0]);
		int i;
		for (i = 0; i < 100; i++){
			j = sprintf(string, "%s%s %d\n", string, "Linha", i);
		}
		sprintf(string, "%s%s", string, "\0");
		write(fd[1], &string, j+1); /*j+1 devido ao barra zero inserido 
		posteriormente*/
		close(fd[1]);
		wait(NULL);
	} else{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execlp("more", "/more", (char*)NULL);
		perror("Erro no exec");
		exit(-1);
	}
	
	
	return 0;
}
