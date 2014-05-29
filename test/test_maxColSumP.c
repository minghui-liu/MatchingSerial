#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.c"

void unconstrainedP(float* Y, float* H, float* X, int size1, int size2, float eps){
	//function X = unconstrainedP (Y, H)
	for(int i=0; i<size1; i++) {
		for(int j=0; j<size2; j++) {
			//X = Y ./ H;
			*(X + i*size2 + j) = *(Y + i*size2 + j) / *(H + i*size2 + j);

			//X(find(X < eps)) = eps;
			if(*(X + i*size2 + j) < eps) {
				*(X + i*size2 + j) = eps;
			}

		} // end of for j
	} // end of for i
} // end of function

//function x = exactTotalSum (y, h, totalSum, precision)
void exactTotalSum(float* y, float* h, float totalSum, float precision, float* X, int length) {

	// y and h are vectors, totalSum and precision are scalars
	//X is the return vector and length is the length of y, h, and X
	float totalSumMinus = totalSum - precision;
	float curAlpha;

	//get the minimum of vector h
	float min = *(h);
	for (int i=1; i < length; i++)
		min = (min < *(h+i))? min : *(h+i);

 	curAlpha = -min + precision;

	//stepAlpha = max(10, abs(curAlpha/10));
	float stepAlpha, newAlpha, newSum;
	if(10 > abs(curAlpha/10))
		stepAlpha = 10;
	else
		stepAlpha = abs(curAlpha/10);

	for(int j=0; j < 50; j++) {
		newAlpha = curAlpha + stepAlpha;
		newSum = 0;

		//x = y ./ (h + newAlpha);
		for(int k=0; k < length; k++) {
			*(X + k) = *(y + k) / (*(h + k) + newAlpha);
			//newSum = sum(x);
			newSum += *(X + k);
		}

		if(newSum > totalSum) {
			curAlpha = newAlpha;
		} else {
			if (newSum < totalSumMinus)
				stepAlpha = stepAlpha / 2;
			else return;
		}
	
	} //end of for j

} //end of exactTotalSum() 

//function X = maxColSumP (Y, H, maxColSum, precision)
void maxColSumP(float* Y, int Ydim1, int Ydim2, float* H, float* maxColSum, float precision, float* X) {
	//X = unconstrainedP (Y, H);
	unconstrainedP(Y, H, X, Ydim1, Ydim2, precision);

	//Xsum = sum(X);
	float Xsum;
	for(int i=0; i < Ydim1; i++){
		for(int j=0; j < Ydim2; j++) {
			Xsum += *(X + i*Ydim2 + j);
		} 
	}

	//for i = find(Xsum > maxColSum)
	for(int i=0; i< dim2; i++){
		if(Xsum > *(maxColSum + i)) {
			//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);
			exactTotalSum(Y, H, i, *(maxColSum + i), precision, X, n);
		}
	}
}

void main() {
	float Y[4][4];
	ones(Y,4,4);
	printMatrix(Y,4,4);
	float H[4][4];
	ones(H,4,4);
	matTimesScaler(H,3,H,4,4);
	printMatrix(H,4,4);
	float maxColSum[4];
	zeros(maxColSum,1,4);
	printMatrix(maxColSum,1,4);

	float X[4][4];
	maxColSumP(Y,4,4,H,maxColSum,0.01,X);
	printMatrix(X,4,4);

}
