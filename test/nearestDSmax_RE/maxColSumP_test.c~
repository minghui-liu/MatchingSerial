#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Test to see if the function maxColSumP from nearestDSmax_RE.c works correctly */

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

/***********************************************************************************************************/
/***********************************************************************************************************/

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
		}
	}
} // end of function

/***********************************************************************************************************/
/***********************************************************************************************************/

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

/**********************************************************************************************************/
/**********************************************************************************************************/

void getCol(float *in_matrix, int size1, int size2, float *output, int colnum) {
	for(int i=0; i<size1; i++) {
		*(output+i) = *(in_matrix + i*size2 + (colnum-1));
	}
}

/***********************************************************************************************************/
/***********************************************************************************************************/
//function X = maxColSumP (Y, H, maxColSum, precision)
void maxColSumP(float* Y, int Ydim1, int Ydim2, float* H, float* maxColSum, float precision, float* X){

//X = unconstrainedP (Y, H);
	unconstrainedP(Y, H, X, Ydim1, Ydim2, precision);

//Xsum = sum(X);
	float Xsum = 0;
	for(int i=0; i < Ydim1; i++){
		for(int j=0; j < Ydim2; j++){
			Xsum += *(X + i*Ydim2 + j);
		} 
	}
//float yCol[Ydim2], hCol[Ydim2], Xcol[Ydim2];
//for i = find(Xsum > maxColSum)
	float Ydim = Ydim1*Ydim2;	
	for(int i=0; i < Ydim1; i++){
		if(Xsum > *(maxColSum + i)){
//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);
/*			getCol(Y, Ydim1, Ydim2, yCol, i);
			getCol(H, Ydim1, Ydim2, hCol, i);
			getCol(X, Ydim1, Ydim2, Xcol, i); */
			exactTotalSum(Y, H, *(maxColSum + i), precision, X, Ydim1);
/*			for(int j=0; j < Ydim1; j++){
				*(X + j*Ydim1 + i) = *(Xcol + j);
			}*/
		}
	}
} // end of function

/***********************************************************************************************************/
/***********************************************************************************************************/
void main() {
	
	float A[4][4] = {{4, 2, 5, 91}, {4, 3, 4, 6}, {4, 9, 0, 2}, {4, 5, 2, 1}};
	float B[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	float X[4][4];
	float maxColSum[4] = {4, 5, 9, 25};
	float eps = 0.01;
	maxColSumP(A, 4, 4, B, maxColSum, eps, X);
	printMatrix(A, 4, 4);
	printMatrix(B, 4, 4);
	printMatrix(X, 4, 4);
}
