#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(void){

	srand(time(NULL));

	const int SALDO_INICIAL = 20;

	int saldo = SALDO_INICIAL, usrNumb, fd[2], fd1[2], pMsg, cMsg;

	pid_t pid;

	pipe(fd);

	pipe(fd1);

	pid = fork();

	if(pid < 0){

		perror("Falha no pipe!");

	}

	if( pid > 0){

		close(fd[0]);
		close(fd1[1]);

		do{

			printf("Saldo: %d\n Introduza um inteiro de 1 a 5\n(-1) - Terminar o jogo\n", saldo);

			scanf("%d", &usrNumb);

			while( !(usrNumb >= 1 && usrNumb <= 5)){

				if( usrNumb == -1) break;

				printf("O número tem de ser entre 1 e 5\nPor favor reintroduza: ");

				scanf("%d", &usrNumb);

			}

			pMsg = (usrNumb == -1) ?  0 : 1;

			write(fd[1], &pMsg, sizeof(int));

			read(fd1[0], &cMsg, sizeof(int));

			printf("Resultado: %d\n", cMsg);

			saldo = (cMsg == usrNumb) ? saldo + 10 : saldo - 5;

			write(fd[1], &saldo, sizeof(int));

			if(saldo < 5){

				printf("Acabaram os créditos!\n");

				break;

			}
		

		}while( usrNumb != -1);

		printf("Obrigado por ter jogado!\n");

		close(fd[1]);
		close(fd1[0]);

		wait(NULL);

		exit(0);

	}

	if( pid == 0){

		close(fd[1]);
		close(fd1[0]);

		do{

			read(fd[0], &pMsg, sizeof(int));

			if( pMsg == 1){

				cMsg = (rand() % 5) + 1;

				write(fd1[1], &cMsg, sizeof(int));

			}else{
				cMsg = 0;

				write(fd1[1],&cMsg, sizeof(int));

			}	

			read(fd[0], &saldo, sizeof(int));

			if(saldo < 5){

				break;

			}


		}while(pMsg != 0);

		close(fd[0]);
		close(fd1[1]);
		exit(0);

	}

	return 0;

}
