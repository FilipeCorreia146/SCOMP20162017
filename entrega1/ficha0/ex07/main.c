#include <stdio.h>
#include <stdlib.h>
#include "palindrome.h"

int main(void){

	char str [] = "Never odd or even";

	int check = 0;

	check = palindrome( str, check);

	if(check == 0){
	
		printf("É um palindrome!\n");

	}else{

		printf("Não é um palindrome\n");

	}

return 0;

}
