#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

typedef  struct{
    int codigo_cliente;
    int codigo_produto;
    int quantidade;
}registo;

int main(){
	int i;
	int num_registos = 50000;
	int num_proc = 10;
	registo vec[num_registos];
	int fd[num_proc][2];
	pid_t pid;
	srand(time(NULL));
	
	for (i = 0; i < 50000; i++){
		registo reg;
		reg.codigo_cliente = i;
		reg.codigo_produto = i+1;
		reg.quantidade = rand()%22+1; /*Vai de 1 a 22*/
		vec[i] = reg;
	}
	
	
	for (i = 0; i < num_proc; i++){
		if(pipe(fd[i]) == -1){
			perror("Erro na criação do pipe");
			exit(-1);
		}
	}
	
	
	for (i = 0; i < num_proc; i++){
		pid = fork();
		if(pid < 0){
			perror("Erro no fork");
			exit(-1);
		}
		if(pid == 0){
			int j;
			close(fd[i][0]);
			for (j = i*5000; j < j+5000; j++){
				if(vec[j].quantidade > 20){
					write(fd[i][1], &vec[j], sizeof(registo));
				}
			}			
			close(fd[i][1]);
			exit(0);
		}
	}
	
	
	registo maiores[num_registos];
	int pos;
	for (i = 0; i < num_proc; i++){
		pos = 0;
		close(fd[i][1]);
		while(read(fd[i][0], &maiores[pos], sizeof(registo)) > 0){
			pos++;
		}
		close(fd[i][0]);
	}
	
	for (i = 0; i < 50000; i++){
		printf("%d ", maiores[i].quantidade);
	}
	
	return 0;
}
