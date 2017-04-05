#include <stdio.h>

int calculateHighest(int * vec, int vecSize) {

	int maximum = 0, i;

	for(i=0; i<vecSize; i++) {
		if(*(vec+i) > maximum){

			maximum = *(vec+i);
		}
	}
	return maximum;
}
