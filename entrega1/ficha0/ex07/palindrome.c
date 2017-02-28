#include <stdio.h>
#include <stdlib.h>

int palindrome(char * str, int check){

	char * temp = NULL;

	temp = (char *) malloc( sizeof(char));

	int cont = 0;

	while( *str != 0){

		if( (* str > 65 && * str < 91) || (* str > 96 && * str < 123) ){

			*(temp+cont) = *str;
			cont++;
			temp = (char*) realloc( temp, cont +1);
		}

		str++;

	}

	int i;

	for(i = 0; i< cont; i++){

		if( *(temp+i) != *(temp + cont -1 -i) && *(temp+i) != *(temp + cont -1 -i)-32 && *(temp+i)-32 != *(temp + cont -1 -i)){

		check =1;

		}
	}

	free(temp);

return check;

}
