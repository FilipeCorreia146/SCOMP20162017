#include <stdio.h>

void invert(int *vec, int n, float *vec2){

	int i;

	for(i=0; i<n; i++){

		*(vec2+i) = 1.0f / *(vec+i);

	}


}	
