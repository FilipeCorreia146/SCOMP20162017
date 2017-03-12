#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int available_money = 25;
	int bet;
	pid_t pid;
	int status;
	int num_player;
	int num_pc = 0;

	printf("Dinheiro a apostar: ");
	scanf("%d", &bet);
	
	while(available_money > 0){
		printf("\nInsira um número entre 1 e 5\n");
		scanf("%d", &num_player);
		pid = fork();
		if(pid == 0){
			exit(execl("./batota", "batota", (char*)NULL));
		}
		waitpid(pid, &status, 0);
		num_pc = WEXITSTATUS(status);
		printf("%d", num_pc);
		if(num_player == num_pc){
			available_money = available_money + bet*2;
		} else{
			available_money = available_money - bet;
		}
		printf("\nDinheiro disponível: %d", available_money);
		printf("\nDinheiro a apostar: ");
		scanf("%d", &bet);
	}
	printf("\nPerdeu\n");
	
	return 0;

}
