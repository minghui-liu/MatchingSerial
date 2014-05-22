#include <stdio.h>

/* test the function exactTotalSum from nearestDSmax_RE.c */

//function x = exactTotalSum (y, h, totalSum, precision)

void exactTotalSum(float* y, float* h, float totalSum, float precision, float* X, int length) {

// y and h are vectors, totalSum and precision are scalars
// X is the return vector and length is the length of y and h

	float totalSumMinus = totalSum - precision;
	
	float curAlpha;

//get the minimum of vector h
	float min = *(h);
	for (int i=1; i < length; i++) {
		min = (min < *(h+i))? min : *(h+i);
	}

 	curAlpha = -min + precision;

//stepAlpha = max(10, abs(curAlpha/10));
	float stepAlpha, newAlpha, newSum;
	if(10 > abs(curAlpha/10)){
		stepAlpha = 10;
	} else{
		stepAlpha = abs(curAlpha/10);
	}

	for(int j=0; j < 50; j++){

		newAlpha = curAlpha + stepAlpha;
		newSum = 0;
//x = y ./ (h + newAlpha);
		for(int k=0; k < length; k++){
			*(X + k) = *(y + k) / (*(h + k) + newAlpha);
//newSum = sum(x);
			newSum += *(X + k);
		}

		if(newSum > totalSum){
			curAlpha = newAlpha;
		}else{
			if (newSum < totalSumMinus){
				stepAlpha = stepAlpha / 2;
			}else{
				return;
			}
		}
	}

} //end of function

/* prints a matrix 
 * matrix: pointer to the matrix to be printed
 * size1 size2: size of matrix
 */
void printMatrix(float *matrix, int size1, int size2) {
	for (int i=0; i<size1; i++){
		for(int j=0; j<size2; j++) {
			printf("%.2f ", *(matrix + i*size2 + j));
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	
	float y[3][3] = {{4, 5, 2}, {3, 9, 10}, {4, 5, 0.5}};
	float h[3][3] = {{5, 6, 9}, {10, 12, 13}, {1, 1, 1}};
	float totalSum = 48;
	float precision = 0.01;
	int length = 9;
	float X[9];
	exactTotalSum(y, h, totalSum, precision, X, length);
	printMatrix(X, 9, 1);

}
