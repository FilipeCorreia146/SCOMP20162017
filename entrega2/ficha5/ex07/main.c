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
#include "ex07.h"

#define THREAD_NUM 3

int main(void) {

  pthread_t threads[THREAD_NUM];
  pthread_t otherThreads[THREAD_NUM];
  int i;
  custo = 0;

  fillVector();

	if( (pthread_mutex_init(&mux, NULL)) != 0) {
		perror("Error creating mutex lock");
		exit(0);
	}

  if( (pthread_mutex_init(&cMux, NULL)) != 0) {
		perror("Error creating mutex lock");
		exit(0);
	}

  for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&threads[i], NULL, sort_func, (void*)&i) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

  for(i=0; i<THREAD_NUM; i++) {
		pthread_join(threads[i], NULL);
	}

  for(i=0; i<THREAD_NUM; i++) {
		if(pthread_create(&otherThreads[i], NULL, calc_func, (void*)&i) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

  for(i=0; i<THREAD_NUM; i++) {
    pthread_join(otherThreads[i], NULL);
  }

  pthread_mutex_destroy(&mux);
  pthread_mutex_destroy(&cMux);
  printf("Hipermercado com o preço mais baixo: %d\n", menorCusto);

  return 0;
}
