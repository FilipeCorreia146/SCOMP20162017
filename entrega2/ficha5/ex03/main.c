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
#include "func.h"


#define THREAD_NUM 5


int main(void) {
	
	time_t t;
	int i;
	pthread_t threads [THREAD_NUM];
	double totalBalance=0;
	my_struct * values;
	void* ret;
	srand((unsigned) time(&t));

	for(i=0; i<ARRAY_SIZE; i++) {
		balance[i] = rand()%1000;
	}


	for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&threads[i], NULL, thread_func, (void*)&i) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

	

	for(i=0; i<THREAD_NUM; i++) {
		pthread_join(threads[i], &ret);
		values = ((my_struct*) ret);
		totalBalance = totalBalance + values->sum;
	}

	printf("Balanço total: €%.2f\n", totalBalance);

	return 0;
}
