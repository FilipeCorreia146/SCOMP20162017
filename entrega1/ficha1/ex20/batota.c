#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(){
	int num;
	srand(time(NULL));
	num = rand()%5+1; 
	return num;
}
