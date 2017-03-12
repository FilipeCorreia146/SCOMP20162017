int procurar_num(int* vec, int num){

	int i;
	for(i = 0; i < 20000; i++){
		if(*(vec+i) == num){
			return 1;
		}
	}
	return 0;

}
