#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ** split(char * str){

	char * spltd;

	spltd = strtok( str, " ");

	char ** ret = NULL;

	int size = 0;

	while( spltd != NULL){

		ret = realloc(ret, sizeof(char *) * ++size);

		*(ret + size * (sizeof(char *))) = spltd;

		spltd = strtok( NULL, " ");

	}

	ret = realloc( ret, sizeof(char *) * ++size);

	*(ret + size * sizeof(char*)) = NULL;

	return ret;

}
