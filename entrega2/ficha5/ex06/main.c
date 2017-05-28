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

pthread_mutex_t mutex[3];

char * hora() {
	char * str = (char *) malloc (20 * sizeof(char)); 
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
			
	sprintf(str, "%dhh%dmm%dss\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	
	return str;
		
}

void* viagem(void *arg) {
	int type = *(int *) arg;
	char * hora_partida, *hora_chegada;

	if(type == 0) {
		hora_partida = hora();
		printf("\nComboio ligação A-D partiu às %s", hora_partida);
		pthread_mutex_lock(&mutex[0]);
		printf("\nComboio de A-D na linha A-B");
		sleep(3);
		pthread_mutex_unlock(&mutex[0]);
		pthread_mutex_lock(&mutex[1]);
		printf("\nComboio de A-D na linha B-D");
		sleep(4);
		pthread_mutex_unlock(&mutex[1]);
		hora_chegada = hora();
		printf("\nComboio ligação A-D tempo de viagem: %s | %s", hora_partida, hora_chegada);
	}else {
		hora_partida = hora();
		printf("\n\nComboio ligação C-A partiu às %s", hora_partida);
		pthread_mutex_lock(&mutex[2]);
		printf("\nComboio de C-A na linha C-B");
		sleep(2);
		pthread_mutex_unlock(&mutex[2]);
		pthread_mutex_lock(&mutex[0]);
		printf("\nComboio de C-A na linha B-A");
		sleep(3);
		pthread_mutex_unlock(&mutex[0]);
		hora_chegada = hora();
		printf("\nComboio ligação C-A tempo de viagem: %s | %s", hora_partida, hora_chegada);
	}
	pthread_exit(NULL);	
}


int main(int argc, char **argv) {
	pthread_t threads[4];
	int i;
	int args[4];
	
	for(i = 0; i < 3; i++) {
		pthread_mutex_init(&mutex[i], NULL);
	}
	
	for (i = 0; i < 4; i++) {
		args[i] = i % 2;/*Porque os tipos são só 0 ou 1*/
		if(pthread_create(&threads[i], NULL, viagem,(void*)&args[i]) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

	for (i = 0; i < 4; i++) {
		pthread_join(threads[i], NULL);
	}
	return 0;
}

