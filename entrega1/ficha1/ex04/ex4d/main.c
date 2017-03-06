#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void){

	pid_t pid;
	int f;
	
	pid = fork();
	for(f=0; f<2; f++){
		if(pid>0){
			printf("Eu sou o pai \n");
			pid = fork();
		}
		else{
			sleep(1);
		}
		
	}
	return 0;	
}
