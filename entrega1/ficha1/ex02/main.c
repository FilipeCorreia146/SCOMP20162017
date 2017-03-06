#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid_filho1;
	pid_t pid_filho2;
	int status1;
	int status2;
	
	pid_filho1 = fork();
	if(pid_filho1<0){
		perror("Erro no fork");
		exit(-1);
	}
	
	if(pid_filho1>0){
		pid_filho2 = fork();
		if(pid_filho2<0){
			perror("Erro no fork");
			exit(-1);
		}
	}
	if(pid_filho2 == 0){
		printf("Eu sou o 2º filho\n");		
		exit(2);
	}
	if(pid_filho1 >0 && pid_filho2 >0){
		waitpid(pid_filho1,&status1,0);
		waitpid(pid_filho2, &status2,0);
		printf("Eu sou o pai\n");
	}
	
		
	 if(pid_filho1 == 0){
	
		printf("Eu sou o 1º filho\n");
		sleep(5);
		exit(1);
	}
	
	/*if (WIFEXITED(status2)) - não necessita desta condição pois só o pai
	 * é que chega lá*/
	printf("Filho 1 retornou o valor:%d\n",WEXITSTATUS(status1));
	printf("Filho 2 retornou o valor:%d\n",WEXITSTATUS(status2));
	printf("Eu sou o pai com o pid = %d\n", getppid());
	
	
	
	
	
	
	
	return 0;
}
