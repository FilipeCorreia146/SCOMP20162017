#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	pid_t pid;

	int num = 0, fd[2], fd2[2], factorial;

	pipe(fd);

	pipe(fd2);

	pid = fork();

	if(pid < 0){

		perror("Erro no fork");

	}
	if(pid > 0){

		close(fd[0]);
		close(fd2[1]);

		do{

			printf("Insira um número inteiro: ");

			scanf("%d", &num);

		}while(num < 0);

		write(fd[1], &num, sizeof(int));

		read(fd2[0], &factorial, sizeof(int));

		printf("Resultado: %d\n", factorial);


		close(fd[1]);
		close(fd2[0]);

	}

	if(pid == 0){

		close(fd[1]);
		close(fd2[0]);

		dup2(fd[0], 0);
		dup2(fd2[1], 1);

		execlp("./factorial", "factorial", NULL);
		perror("Erro ao executar exec");
		exit(0);


	}

	return 0;

}
