#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct{
	int num;
	char nome[100];
} est;

int main(){
	est estrutura;
	pid_t pid;
	int fd[2];
	
	if(pipe(fd) == -1){
		perror("Falha na criação de pipe");
		exit(-1);
	}
	
	pid = fork();
	if(pid <0){
		perror("Erro no fork");
		exit(-1);
	}
	
	if(pid>0){
		close(fd[0]);
		printf("Número: ");
		scanf("%d%*c", &estrutura.num);
		printf("Nome: ");
		fgets(estrutura.nome, 100, stdin);
		write(fd[1], &estrutura.num, sizeof(int));
		write(fd[1], &estrutura.nome, sizeof(estrutura.nome));
		close(fd[1]);
		wait(NULL);
	}else{
		close(fd[1]);
		read(fd[0], &estrutura.num, sizeof(estrutura.num));
		read(fd[0], &estrutura.nome, sizeof(estrutura.nome));
		printf("Número lidos do pipe: %d\n",estrutura.num);
		printf("Nome lido do pipe: %s", estrutura.nome);
		close(fd[0]);
	}
	
	
	
	return 0;
}
