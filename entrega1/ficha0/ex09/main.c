#include <stdio.h>
#include "soma_multiplos_x.h"

int main(void){

	int x;

	char vec [] = { 31, 112, 13, 25, 105, 52, 32, 26, 23, 3,4,0};

	printf("Por favor introduza x: ");

	scanf("%d", &x);

	int soma;

	soma = soma_multiplos_x(vec, x);

	printf("A soma dos multiplos do terceiro bit de x é: %u\n", soma);

return 0;
}
