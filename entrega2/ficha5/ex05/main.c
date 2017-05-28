#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>
#include "ex05.h"

int main(void) {

	srand(time(NULL));
	threadVerify = 0;

	if( (pthread_mutex_init(&mutex, NULL)) != 0) {
		perror("Error creating mutex lock");
		exit(0);
	}

	if( (pthread_cond_init(&cond, NULL)) != 0) {
		perror("Error creating mutex lock");
		exit(0);
	}

	pthread_t threads[THREAD_NUM];
	int i;

	for(i=0; i<DATA_SIZE; i++) {
		dados[i] = rand() %100;
	}

	for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&threads[i], NULL, thread_func, (void*)&i) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

	for(i=0; i<THREAD_NUM; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);

	return 0;
}
