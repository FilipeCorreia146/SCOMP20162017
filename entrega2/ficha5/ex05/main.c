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
#include "ex05.h"

#define THREAD_NUM 5

int main(void) {

	threadVerify = 0;

	if( (pthread_mutex_init(&mutex, NULL)) != 0) {
		perror("Error creating mutex lock");
		exit(0);
	}

	pthread_t threads[THREAD_NUM];
	int i; 

	for(i=0; i<DATA_SIZE; i++) {
		dados[i] = i;
	}

	for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&threads[i], NULL, thread_func, (void*)&i) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}
