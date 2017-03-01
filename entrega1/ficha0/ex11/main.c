#include <stdio.h>

int main(void){

	char ** vec = NULL;

	char * entry = NULL;

	vec = (char **) malloc ( sizeof(char*));

	int cont = 0;

	while( cont < 20){

		printf("Por favor introduza um nome: ")

		char * input = read_string();

		*vec = input;

		cont++;

		vec = (char **) realloc(vec, (sizeof(char*) * cont) + sizeof(char*);

		vec++;

	}


	

return 0;
}
