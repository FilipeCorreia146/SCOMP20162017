void subtracao(int *vec, int elem, int valor){
	int i = 0;
	
	while(i<elem){
		*(vec+i) = *(vec+i)-valor;
		i++;
	}
	
}
