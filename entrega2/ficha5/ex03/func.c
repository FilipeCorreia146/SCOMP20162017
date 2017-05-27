#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "func.h"

void * thread_func(void* arg) {

	int value = *(int *)arg;
	int i, sum = 0;
	my_struct *ms = (my_struct*)malloc(sizeof(my_struct));

	for(i=TEMP_SIZE*value; i<TEMP_SIZE*(value+1); i++) {
		sum = sum +balance[i];
	}

	ms->sum =(double) sum;

	pthread_exit((void*)ms);
}
