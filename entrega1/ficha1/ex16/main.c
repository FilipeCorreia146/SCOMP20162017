#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void){
	char path[100] = "/bin/";
	char command[30];
	int status;
	int ret;
	pid_t pid;
	
	printf("\nInsira um comando\n");
	scanf("%s", command);
	
	while(strcmp(command, "sair") != 0){ /*É 0 se as strings forem iguais*/
		pid = fork();
		if(pid == 0){
			strcat(path, command);
			ret = execl(path, command, (char*)NULL);
			exit(ret); /*Apena executa se o execl falhar*/
		}
		wait(&status);
		printf("\nInsira um comando\n");
		scanf("%s", command);
	}
	
	return 0;
	
}
