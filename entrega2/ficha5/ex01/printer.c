#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "ex01.h"

void* thread_printer(void *arg){

	info i = *((info*) arg);

	printf("Numero: %d\n", i.numero);
	printf("Nome: %s\n", i.nome);
	printf("Morada: %s\n", i.morada);

	pthread_exit((void*)NULL);
}
