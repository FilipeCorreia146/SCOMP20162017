#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
	int barCode;
	char* name;
	float price;

} product;

typedef struct {
	int barCode;
	int id;
} productId;

int main(void){

	const int CHILD_NUM = 3, PROCESS_NUM =4;

	int fd[PROCESS_NUM][2], i;

	productId prId;

	pid_t pid;

	for(i = 0; i< PROCESS_NUM; i++){

		pipe(fd[i]);

	}

	for(i = 0; i< CHILD_NUM; i++){

		pid = fork();
		
		if(pid == 0){

			break;

		}

	}

	if( pid > 0){

		product pList[CHILD_NUM];
		pList[0].barCode = 1;
		pList[0].name = "Laptop";
		pList[0].price = 1299.99;

		pList[1].barCode = 2;
		pList[1].name = "Tablet";
		pList[1].price = 699.99;

		pList[2].barCode = 3;
		pList[2].name = "Smartphone";
		pList[2].price = 299.99;

		close(fd[3][1]);

		product * p;

		for(i = 0; i<CHILD_NUM; i++){

			int j;

			read(fd[3][0], &prId, sizeof(productId));

				for(j = 0; j<CHILD_NUM; j++){


				if(pList[j].barCode == prId.barCode){

					p = &pList[j];

				}

			}

			close(fd[i][0]);

			write(fd[i][1], p, sizeof(product));
			

			close(fd[i][1]);

		}

		close(fd[3][0]);

	}

	if(pid == 0){
	
		prId.barCode = i+1;
		prId.id = i;
		product p;

		close(fd[3][0]);

		write(fd[3][1], &prId, sizeof(productId));

		read(fd[i][0], &p, sizeof(product));

		close(fd[i][1]);

		close(fd[3][1]);

		printf("Código: %d|Nome: %s|Preço: %.2f\n", p.barCode, p.name, p.price);

		close(fd[i][0]);


	}

	return 0;
}

