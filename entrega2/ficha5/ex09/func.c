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

void * read_func(void * arg) {

  int i;

  printf("=====================================================\n");
  printf("Bem-Vindo ao Programa de cálculo de notas parciais!\n");

  for(i=0; i<N_ALUNOS; i++) {
    pthread_mutex_lock(&mux);
    obtem_Notas(i);
    pthread_cond_broadcast(&lido);
    nAlunoAtual = nAlunoAtual+1;
    pthread_mutex_unlock(&mux);
  }

  pthread_exit((void*) NULL);

}

  void * calc_func(void * arg) {

    while(nAlunoAtual<N_ALUNOS) {
      pthread_mutex_lock(&mux);
      pthread_cond_wait(&lido, &mux);

      array[nAlunoAtual].notaFinal = (array[nAlunoAtual].notaG1+array[nAlunoAtual].notaG2+array[nAlunoAtual].notaG3) /3;

      if(array[nAlunoAtual].notaFinal >= 50) {
        pthread_cond_broadcast(&positiva);
      }
      if(array[nAlunoAtual].notaFinal < 50) {
        pthread_cond_broadcast(&negativa);
      }
      pthread_mutex_unlock(&mux);
    }

    pthread_exit((void*) NULL);

  }

  void * func_negativa(void * arg) {
    while (nAlunoAtual<N_ALUNOS) {
      pthread_cond_wait(&negativa, &muxPN);
      nNegativas =  nNegativas+1;
    }

    pthread_exit((void*) NULL);

  }

  void * func_positiva(void * arg) {
    while (nAlunoAtual<N_ALUNOS) {

      pthread_cond_wait(&positiva, &muxPN);
      nPositivas =  nPositivas+1;
    }

    pthread_exit((void*) NULL);

  }
