#include <stdio.h>
#include <stdlib.h>

int palindrome(char * str, int check){

	char * temp = NULL;

	temp = (char *)  malloc( sizeof(str) );

	int cont = 0;

	while( *str != 0){

		if( (* str > 65 && * str < 91) || (* str > 96 && * str < 123) ){

			*temp = *str;
			temp++;
			cont++;
		}

		str++;

	}

	temp = temp - cont;

	int i;

	for(i = 0; i< cont; i++){

		if( *(temp+i) != *(temp + cont -1 -i) && *(temp+i) != *(temp + cont -1 -i)-32 && *(temp+i)-32 != *(temp + cont -1 -i)){

		check =1;

		}
	}

return check;

}
