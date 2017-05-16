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
#include "ex01.h"
#include "printer.h"

#define VEC_SIZE 5

int main(void) {

	int i;
	pthread_t threads [VEC_SIZE];
	info vec [VEC_SIZE];

	vec->numero = 1;
	strcpy(vec->nome, "NOME1");
	strcpy(vec->morada, "Morada1");
	(vec+1)->numero = 2;
	strcpy((vec+1)->nome, "NOME2");
	strcpy((vec+1)->morada, "Morada2");
	(vec+2)->numero = 3;
	strcpy((vec+2)->nome, "NOME3");
	strcpy((vec+2)->morada, "Morada3");
	(vec+3)->numero = 4;
	strcpy((vec+3)->nome, "NOME4");
	strcpy((vec+3)->morada, "Morada4");
	(vec+4)->numero = 5;
	strcpy((vec+4)->nome, "NOME5");
	strcpy((vec+4)->morada, "Morada5");

	for(i=0; i<VEC_SIZE; i++) {
		if(pthread_create(&threads[i], NULL, thread_printer,(void*)&vec[i]) !=0) {
			perror("Error creating thread");
			exit(1);
		}
	}

	for(i=0; i<VEC_SIZE; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;

}
