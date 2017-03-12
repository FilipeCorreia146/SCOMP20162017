#include <stdio.h>
#include <stdlib.h>

char * resize(char * input){

	char * ret = NULL;

	int cont = 0;

	while(input != '\0'){

		ret = realloc( ret, sizeof(char) * cont++);

		*(ret+ cont-1) = *(input);

		input++;

	}

	return ret;

}
