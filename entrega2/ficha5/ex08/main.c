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

pthread_mutex_t mutex[15][16];
int tempos[15][16];

void* caracol1(void *arg) {
	time_t inicio, fim;
	unsigned long tempo = 0;
	int percurso[] = {0,1,4,5,6,8,9,10,11,15};
	int i = 0; 
	inicio = time(NULL);
	for(i = 0; i < 9; i++) {
		pthread_mutex_lock(&mutex[caminho[i]][caminho[i+1]]);
		sleep(tempos[caminho[i]][caminho[i+1]]);
		tempos[caminho[i]][caminho[i+1]] *=2;/*Para aumentar o tempo de passagem*/
		pthread_mutex_unlock(&mutex[caminho[i]][caminho[i+1]]);
	}
	fim = time(NULL);
	tempo = difftime(fim,inicio);	
	pthread_exit((void *) tempo);		
}

void* caracol2(void *arg) {
	time_t inicio, fim;
	unsigned long tempo = 0;
	int percurso[]  = {0,2,4,5,7,8,9,13,14,15};
	int i = 0; 
	inicio = time(NULL);
	for(i = 0; i < 10; i++){
		pthread_mutex_lock(&mutex[caminho[i]][caminho[i+1]]);
		sleep(tempos[caminho[i]][caminho[i+1]]);
		tempos[caminho[i]][caminho[i+1]] *=2; 
		pthread_mutex_unlock(&mutex[caminho[i]][caminho[i+1]]);
	}
	fim = time(NULL);
	tempo = difftime(fim,inicio);
	pthread_exit((void *) tempo);	
}

void* caracol3(void *arg){
	time_t inicio, fim;
	unsigned long tempo = 0;
	int percurso[]  = {0,3,4,5,7,9,10,12,15};
	int i = 0; 
	inicio = time(NULL);
	for(i = 0; i < 9; i++){
		pthread_mutex_lock(&mutex[caminho[i]][caminho[i+1]]);
		sleep(tempos[caminho[i]][caminho[i+1]]);
		tempos[caminho[i]][caminho[i+1]] *=2; 
		pthread_mutex_unlock(&mutex[caminho[i]][caminho[i+1]]);
	}
	fim = time(NULL);
	tempo = difftime(fim,inicio);
	pthread_exit((void *) tempo);		
}

void preencher_matrizes(void) {
	/*Preenche a matriz com os tempos de acordo com o enunciado*/
	tempos[0][1] = 5;
	tempos[0][2] = 5;
	tempos[0][3] = 5;
	tempos[1][4] = 4;
	tempos[2][4] = 4;
	tempos[3][4] = 4;
	tempos[4][5] = 3;
	tempos[5][6] = 5;
	tempos[5][7] = 5;
	tempos[6][8] = 6;
	tempos[7][8] = 6;
	tempos[7][9] = 4;
	tempos[8][9] = 4;
	tempos[9][10] = 5;
	tempos[10][11] = 5;
	tempos[10][12] = 5;
	tempos[9][13] = 5;
	tempos[11][14] = 3;
	tempos[12][14] = 3;
	tempos[13][14] = 5;
	tempos[14][15] = 3;
	
	/*Inicializa a matriz de mutex*/
	pthread_mutex_init(&mutex[0][1], NULL);
	pthread_mutex_init(&mutex[0][2], NULL);
	pthread_mutex_init(&mutex[0][3], NULL);
	pthread_mutex_init(&mutex[1][4], NULL);
	pthread_mutex_init(&mutex[2][4], NULL);
	pthread_mutex_init(&mutex[3][4], NULL);
	pthread_mutex_init(&mutex[4][5], NULL);
	pthread_mutex_init(&mutex[5][6], NULL);
	pthread_mutex_init(&mutex[5][7], NULL);
	pthread_mutex_init(&mutex[6][8], NULL);
	pthread_mutex_init(&mutex[7][8], NULL);
	pthread_mutex_init(&mutex[7][9], NULL);
	pthread_mutex_init(&mutex[8][9], NULL);
	pthread_mutex_init(&mutex[9][10], NULL);
	pthread_mutex_init(&mutex[10][11], NULL);
	pthread_mutex_init(&mutex[10][12], NULL);
	pthread_mutex_init(&mutex[9][13], NULL);
	pthread_mutex_init(&mutex[11][14], NULL);
	pthread_mutex_init(&mutex[12][14], NULL);
	pthread_mutex_init(&mutex[13][14], NULL);
	pthread_mutex_init(&mutex[14][15], NULL);
}

int main(int argc, char **argv) {
	pthread_t threads[3];
	int i;
	unsigned long resultados[3];
	unsigned long vencedor;
	int numCaracol;
	
	preencher_matrizes();
	
	if(pthread_create(&threads[0], NULL, caracol1, NULL) !=0) {
		perror("Error creating thread");
		exit(1);
	}
	
	if(pthread_create(&threads[1], NULL, caracol2, NULL) !=0) {
		perror("Error creating thread");
		exit(1);
	}
	
	if(pthread_create(&threads[2], NULL, caracol3, NULL) !=0) {
		perror("Error creating thread");
		exit(1);
	}

	for (i = 0; i < 3; i++) {
		pthread_join(threads[i], (void *) &resultados[i]);
	}
	
	printf("\n\Tempos:\nCaracol 1: %lu\nCaracol 2: %lu\nCaracol 3: %lu\n\n", resultados[0], resultados[1], resultados[2]); 
	
	vencedor = resultados[0];
	for (i = 1; i < 3; i++){
		if(resultados[i] < vencedor){
			numCaracol = i+1;
		}
	}
	
	printf("O caracol vencedor é o %d\n",numCaracol);
	
	
	return 0;
}
