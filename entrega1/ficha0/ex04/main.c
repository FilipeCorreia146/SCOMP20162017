#include <stdio.h>
#include "subtracao.h"

int main(){
	int vec [5] = {1,2,3,4,5}; 
	int elem = 5;
	int valor = 1;
	int i;
	
	subtracao(vec,elem,valor);
	for (i = 0; i < elem; i++)
	{
		printf("%d ", *(vec+i));
	}
	

	return 0;
}
