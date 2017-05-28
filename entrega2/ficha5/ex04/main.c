#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <time.h>
#include <pthread.h>

#define NUM_POR_THREAD 1000

typedef struct totoloto{
	int numeros[5];
} totoloto;

totoloto data[10000];
int cont[49];
pthread_mutex_t mutex [49];/*É um array para que se bloqueie apenas uma posição
							em vez de todo o array*/

void* thread_count(void *arg){
	int pos = *(int *) arg;
	int i, j, num;
	totoloto chave;
	
	for(i = (NUM_POR_THREAD*pos); i < (NUM_POR_THREAD*pos)+NUM_POR_THREAD; i++) {
		chave = data[i];
		for(j = 0; j < 5; j++) {
			num = chave.numeros[j];
			num--;
			pthread_mutex_lock(&mutex[num]);
			cont[num]++;
			pthread_mutex_unlock(&mutex[num]);
		}
	}
	pthread_exit(NULL);	
}

int main(int argc, char **argv) {
	pthread_t threads[10];
	int i, j;
	int args[10];
	srand(time(0));/*Para se obter números diferentes*/
	
	for (i = 0; i < 49; i++){
		pthread_mutex_init(&mutex[i], NULL);
	}
	
	for(i = 0; i < 10000; i++) {
		printf("\n\nChave número %d\n", i+1);
		for(j = 0; j < 5; j++) {
			data[i].numeros[j] = rand()%49+1;
			printf(" %d ", data[i].numeros[j]);
		}
	}
	
	for (i = 0; i < 10; i++) {
		args[i] = i;
		if(pthread_create(&threads[i], NULL, thread_count,(void*)&args[i]) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}
	
	for (i = 0; i < 10; i++) {
		pthread_join(threads[i], NULL);
	}
	
	printf("\n\nContadores\n"); /*Contador de um dado número*/
	for(i = 0; i < 49; i++) {
		printf(" %d ", cont[i]);
	}
	
	return 0;
}
