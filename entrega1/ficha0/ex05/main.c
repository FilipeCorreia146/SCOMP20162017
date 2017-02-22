#include <stdio.h>
#include "invert.h"

int main(void){

	int n;

	n = 10;

	int vec [] = { 0,2,3,513,514,5132,345,135,3214,321};

	float vec2 [10] = {0};


	int sum, i = 0;

	invert(vec, n, vec2);


	for(i = 0; i<n; i++){

		printf("Element: %d Inverse:%f\n",*(vec+i), *(vec2+i));
	

	}

	return 0;

}
