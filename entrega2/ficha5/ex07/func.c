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

void * sort_func(void* arg) {

  int idMercado = *(int*) arg;
  int i, cont=0;
  idMercado = idMercado+1;

  pthread_mutex_lock(&mux);

  for(i=0; i<VEC_SIZE; i++) {

    if(idMercado == 1 && vec[i].id_h == 1) {
      vec1[cont] = vec[i];
      cont++;
    }
    if(idMercado == 2 && vec[i].id_h == 2) {
      vec2[cont] = vec[i];
      cont++;
    }
    if(idMercado == 3 && vec[i].id_h == 3) {
      vec2[cont] = vec[i];
      cont++;
    }

  }

  pthread_mutex_unlock(&mux);
	pthread_exit((void*)NULL);
}

void * calc_func(void* arg) {

  int val = *(int*) arg;
  int i;
  int sum;
  val = val+1;

  if(val == 1) {
    for(i=0; i<N_PRODUTOS; i++) {
      sum = sum + vec1[i].x;
    }
  }

  if(val == 2) {
    for(i=0; i<N_PRODUTOS; i++) {
      sum = sum + vec1[i].x;
    }
  }

  if(val == 3) {
    for(i=0; i<N_PRODUTOS; i++) {
      sum = sum + vec3[i].x;
    }
  }

  pthread_mutex_lock(&cMux);

  if(sum < custo) {
    custo = sum;
    menorCusto = val;
  }

  pthread_mutex_unlock(&cMux);

  pthread_exit((void*)NULL);

}
