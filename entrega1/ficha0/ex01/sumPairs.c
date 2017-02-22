#include <stdio.h>

 int sumPairs(int * ptr, int n){
	 
	 int i, sum = 0;
	 
	 for( i = 0; i<n; i++){

		if( *(ptr+i) %2 == 0){
		 
		 	sum = sum + *(ptr+i);
		 
		}
	}
	
	return sum;

}
