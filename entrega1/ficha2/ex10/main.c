#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t pid = 1, ppid;
	int fd[6][2];
	int j, num, auxiliar, i;
	
	srand(getpid());
	for (i = 0; i < 6; i++){
		pipe(fd[i]);
	}
	
	auxiliar = rand();
	write(fd[0][1], &auxiliar, sizeof(int));
	ppid = getpid();
	
	write(fd[0][1], &ppid, sizeof(pid_t));
	printf("número: %d, pid: %d\n", auxiliar, getpid());
	
	for (i = 0; i < 6; i++){
		if(pid > 0){
			pid = fork();
		} else{
			for (j = 0; j < 6; j++){
				if(j != i-1 && j != i){
					close(fd[j][0]);
					close(fd[j][1]);
				}else if(j == i-1){
					close(fd[j][1]);
				} else if(j == i){
					close(fd[j][0]);
				}				
			}
			read(fd[i-1][0], &num, sizeof(int));
			read(fd[i-1][0], &ppid, sizeof(pid_t));
			close(fd[i-1][0]);
			srand(getpid());
			auxiliar =  rand();
			printf("Num anterior: %d, pid: %d | Num: %d, Pid: %d\n", num, ppid, auxiliar,
			getpid());
			if(num < auxiliar){
				write(fd[i][1], &auxiliar, sizeof(int));
				ppid = getpid();
				write(fd[i][1], &ppid, sizeof(pid_t));
			}else{
				write(fd[i][1], &num, sizeof(int));
				write(fd[i][1], &ppid, sizeof(pid_t));
			}
			close(fd[i][1]);
			exit(0);
		}
	}
	
	for (i = 0; i < 6; i++){
		if(i != 5){ /*Para não fechar o ultimo pipe que vem do processo 5
			para o pai*/
			close(fd[i][0]);
		}
		close(fd[i][1]);
	}
	
	
	for (i = 0; i < 6; i++){
		wait(NULL);
	}
	
	read(fd[5][0], &num, sizeof(int));
	read(fd[5][0], &ppid, sizeof(pid_t));
	close(fd[5][0]);
	printf("Número vencedor: %d, Pid: %d\n", num, ppid);
	
	return 0;
}
