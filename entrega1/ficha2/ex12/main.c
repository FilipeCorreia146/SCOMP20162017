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
	char file_name [100] = "fx.txt";
	
	
	if(pipe(fd) == -1){
		perror("Erro na criação do pipe");
		exit(-1);
	}
	
	pid = fork();
	if(pid < 0){
		perror("Erro no fork");
		exit(-1);
	}
	
	if(pid > 0){
		long file_size;
		close(fd[0]);
		file = fopen(file_name, "r");
		fseek(file, 0, SEEK_END);
		file_size = ftell(file);
		fseek(file, 0, SEEK_SET);
		char buffer[file_size];
		fread(buffer, 1, file_size, file);
		write(fd[1], buffer, file_size);
		fclose(file);
		close(fd[1]);
		wait(NULL);
	} else {
		close(fd[1]);
		dup2(fd[0],0);
		close(fd[0]);
		execlp("od", "od", (char*)NULL);
		perror("Erro no exec");
		exit(-1);
	}
	
	
	
	return 0;
}
