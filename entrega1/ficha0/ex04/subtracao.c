#include <stdio.h>

int subtracao(int *vec, int elem, int valor){
	if(elem == 0){
		return 0;
	}else{
		*vec = *vec - valor;
		return subtracao(vec+1, elem-1, valor);
		
	}
	
	
}
