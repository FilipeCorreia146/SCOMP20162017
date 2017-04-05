#include <stdio.h>

int calculateLowest(int * vec, int vecSize){

	int minimum = *vec, i;

	for(i=0; i<vecSize; i++) {
		if(*(vec+i) < minimum) {
			minimum = *(vec+i);
		}
	}

	return minimum;

}
