#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "ex05.h"

void * thread_func(void* arg) {

	int threadNum = (int)arg;
	int i;

	while(threadVerify!=threadNum) {
		pthread_mutex_lock(&mutex);
	}

	threadVerify=threadVerify+1;

	printf("Thread num: %d\n", threadNum);

	for(i=threadNum*CALCULATE_NUM; i<CALCULATE_NUM*(threadNum+1); i++) {
		resultados[i] = dados[i]*2+10;
		printf("%d\n", resultados[i]);
	}

	pthread_mutex_unlock(&mutex);

	pthread_exit((void*)NULL);
}
