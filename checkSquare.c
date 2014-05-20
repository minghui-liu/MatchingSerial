#include <math.h> 
#include <stdio.h>

boolean checkSquare(double *G){
	int count = 0;
	int temp;
	while(1){
		temp = *(G + count*sizeof(double));
		if(temp > 10000 || temp <10000){
			return false;
		}
	count++;
	}
	count++;
	int size = sqrt(count);
	if(size*size != count)
		return false;
	return true;
}
