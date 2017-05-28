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
#include "ex09.h"

int main(void) {

  pthread_t threadLeitura;
  pthread_t threadsContagem[2];
  pthread_t threadPositivas;
  pthread_t threadNegativas;
  int i;
  nAlunoAtual = 0;
  nPositivas = 0;
  nNegativas = 0;
  pthread_mutex_init(&mux, NULL);
  pthread_mutex_init(&muxPN, NULL);
  pthread_cond_init(&positiva, NULL);
  pthread_cond_init(&lido, NULL);
  pthread_cond_init(&negativa, NULL);

  if(pthread_create(&threadLeitura, NULL, read_func,NULL) !=0) {
		perror("Error creating thread");
		exit(1);
	}

  for(i=0; i<2; i++) {
    if(pthread_create(&threadsContagem[i], NULL, calc_func,NULL)  !=0) {
  			perror("Error creating thread");
  			exit(1);
  		}
    }

  if(pthread_create(&threadPositivas, NULL, func_positiva, NULL)!=0) {
      perror("Error creating thread");
      exit(1);
  }

  if(pthread_create(&threadNegativas, NULL, func_negativa, NULL) !=0) {
      perror("Error creating thread");
      exit(1);
  }

  pthread_join(threadLeitura, NULL);
  for(i=0; i<2; i++) {
    pthread_join(threadsContagem[i], NULL);
  }
  pthread_join(threadPositivas, NULL);
  pthread_join(threadNegativas, NULL);

  pthread_mutex_destroy(&mux);
  pthread_mutex_destroy(&muxPN);
  pthread_cond_destroy(&negativa);
  pthread_cond_destroy(&positiva);
  pthread_cond_destroy(&lido);

  printf("Número de negativas: %d\n", nNegativas);
  printf("Número de positivas: %d\n", nPositivas);

  printf("=====================================================\n");

  return 0;
}
