#include <stdio.h>
#include "sumPairs.h"

int main(void){

	int n;

	n = 10;

	int vec [] = { 0,2,3,513,514,5132,345,135,3214,321};

	int sum;

	sum=sumPairs(vec, n);
	
	printf("The sum of the pair elements is: %d\n", sum);

	return 0;
	
}
