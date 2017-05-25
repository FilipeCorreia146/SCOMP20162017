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

#define NUM_TO_SEARCH 300
int vec[1000];

void * thread_search(void *arg){
	int pos = *(int*) arg;
	int i;
	int *thread_number = NULL;
	for (i = pos*200; i <= (pos+1)*200; i++) {
		if(NUM_TO_SEARCH == vec[i]){
			thread_number = (int*) malloc(sizeof(int));
			*thread_number = pos +1;
			printf("Encontrei o número na posição:%d\n", i);
			pthread_exit((void *) thread_number);
		}
	}
	pthread_exit((void*)NULL);
}

int main(){
	int i, arg[5];
	pthread_t threads[5];
	void* returnedVal;
	int* pos;
	
	for (i = 0; i < 1000; i++) {
		vec[i] = i;
	}
	
	for (i = 0; i < 5; i++) {
		arg[i]=i;
		if(pthread_create(&threads[i], NULL, thread_search,(void*)&arg[i]) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}
	
	for (i = 0; i < 5; i++){
		pthread_join(threads[i], (void*)&returnedVal);
		pos = (int*)returnedVal;
		if(pos != NULL){
			printf("Thread que encontrou: %d\n", *pos);
			free(returnedVal);
		}
	}
	return 0;
}




