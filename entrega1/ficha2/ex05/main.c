#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(void){

	int vec1[1000], vec2[1000], i, fd[2], sum= 0, j;

	for(i = 0; i< 1000; i++){

		vec1[i] = i;
		vec2[i] = 1000-i;

	}

	pid_t pids[5];

	pipe(fd);

	for(i = 0; i<5; i++){

		pids[i] = fork();
		if( pids[i] == 0)
		break;

	}

	if( i >= 0 && i < 5){

		close(fd[0]);

		for( j = (i * 200); j< (200 * (i+1)); j++){

			sum = sum + *(vec1 + j)  + *(vec2 + j);

		}

		write(fd[1], &sum, sizeof(sum));

		close(fd[1]);

		exit(0);

	}

	if( i == 5){

		close(fd[1]);

		int finalresult = 0, reader;

		while(read(fd[0], &reader, sizeof(reader))>0){

			finalresult = finalresult + reader;

		}	
		close(fd[0]);

		printf("Resultado final: %d\n", finalresult);
	
	}

	return 0;

}
