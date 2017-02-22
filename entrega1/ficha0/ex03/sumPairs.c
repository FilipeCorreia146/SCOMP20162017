#include <stdio.h>

int sumPairs( int * ptr, int n){

	if( n == 0){

	return 0;

	}
	else
 
		if( *ptr % 2 == 0){

		return *ptr + sumPairs( ptr+1, n-1);

		}
		else

		return sumPairs( ptr+1, n-1);

}






