#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
	pid_t pid;
	int fd[2];
	FILE *file;
	int buffer_size = 100;
	char buffer[buffer_size];
	char file_name[100] = "dados.txt";
	
	if(pipe(fd) == -1){
		perror("Erro na criação do pipe");
		exit(-1);
	}
	
	pid = fork();
	if(pid<0){
		perror("Erro no fork");
		exit(-1);
	}
	if(pid>0){
		close(fd[0]);
		file = fopen(file_name, "r");
		if(!file){
			perror("Erro a abrir o ficheiro");
			exit(-1);
		}
		while(fgets(buffer, buffer_size, file)!=NULL){
			write(fd[1], buffer, buffer_size*sizeof(char));
		}		
		close(fd[1]);
		fclose(file);
		wait(NULL);
	}else{
		close(fd[1]);
		while(read(fd[0], buffer, buffer_size*sizeof(char))){
			printf("%s", buffer);
		}
		close(fd[0]);
	}
	
	
	return 0;
}
