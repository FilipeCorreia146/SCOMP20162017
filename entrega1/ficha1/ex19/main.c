#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include "resize.h"
#include "backup.h"

int main(void){

	int finisher = 1;

	char file [70];

	while(finisher != 0){

		printf("1 - Backup\n0 - Sair\n");

		scanf("%d", &finisher);

		if(finisher != 0){

			printf("Introduza o nome do ficheiro a copiar: ");

			scanf("%s", file);

			if(file == NULL){

				printf("Não introduziu o nome do ficheiro!\n");
			}else{

			backup(file);
			}

		}

	}

	return 0;

}
