#include <stdio.h>

int soma_multiplos_x (char *vec, int x){


	int temp, sum = 0;

	temp = x >> 16;

	temp = temp & 0xff;

	while( *vec != 0){

		if( temp == 0 || *vec % temp == 0){

		sum = sum + *vec;

		}

		vec++;
	}

return sum;

}
