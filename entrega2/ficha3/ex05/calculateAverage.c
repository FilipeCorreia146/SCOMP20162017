#include <stdio.h>

float calculateAverage(int * vec, int vecSize) {

	int i, sum=0;

	float average;

	for(i=0; i<vecSize; i++) {
		sum=sum+*(vec+i);
	}

	average = sum/(float)vecSize;

	return average;
}
