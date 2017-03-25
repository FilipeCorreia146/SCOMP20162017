#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){

	int num, i = 0, final = 1;

	read(0, &num, sizeof(num));

	for(i = 1; i <=  num; i++){
	
		final *= i;

	}

	write(1, &final, sizeof(num));

	return 0;

}
