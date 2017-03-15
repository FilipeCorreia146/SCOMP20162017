#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int fd[2];
	int num;
	char nome[100];
	
	if(pipe(fd) == -1){
		perror("Falha no pipe");
		exit(-1);
	}
	pid = fork();
	if(pid<0){
		perror("Falha no fork");
		exit(-1);
	}
	if(pid>0){
		close(fd[0]);
		printf("Número: ");
		scanf("%d%*c", &num);
		printf("Nome: ");
		fgets(nome, 100, stdin);
		write(fd[1], &num, sizeof(num));
		write(fd[1], &nome, sizeof(nome));
		close(fd[1]);
		wait(NULL);
	} else{
		close(fd[1]);
		read(fd[0], &num, sizeof(num));
		read(fd[0], &nome, sizeof(nome));
		printf("Número lido do pai: %d\n", num);
		printf("Nome lido do pai: %s\n", nome);
		close(fd[0]);
	}
	
	
	
	
	return 0;
}
