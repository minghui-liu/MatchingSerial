#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 2.2204e-16

/* Test to see if the function maxColSumP from nearestDSmax_RE.c works correctly */

/* prints a matrix 
 * matrix: pointer to the matrix to be printed
 * size1 size2: size of matrix
 */
void printMatrix( int size1, int size2, float matrix[size1][size2]) {
	for (int i=0; i<size1; i++){
		for(int j=0; j<size2; j++) {
			//printf("%.2f ", *(matrix + i*size2 + j));
			printf("%.2f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/***********************************************************************************************************/
/***********************************************************************************************************/

void unconstrainedP(int size1, int size2, float Y[size1][size2], float H[size1][size2], float X[size1][size2], float eps){
	//function X = unconstrainedP (Y, H)
	for(int i=0; i<size1; i++) {
		for(int j=0; j<size2; j++) {
			//X = Y ./ H;
			X[i][j] = Y[i][j] / H[i][j];

			//X(find(X < eps)) = eps;
			if(X[i][j] < eps) {
				X[i][j] = eps;
			}

		} // end of for j
	} // end of for i
} // end of function

/***********************************************************************************************************/
/***********************************************************************************************************/

//function x = exactTotalSum (y, h, totalSum, precision)
void exactTotalSum(int length, float y[length], float h[length], float totalSum, float precision, float X[length]) {

	// y and h are vectors, totalSum and precision are scalars
	// X is the return vector and length is the length of y, h, and X
	float totalSumMinus = totalSum - precision;
	float curAlpha;

	//get the minimum of vector h
	float min = h[0];
	for (int i=1; i < length; i++)
		min = (min < h[i])? min : h[i];

 	curAlpha = -min + precision;

	//stepAlpha = max(10, abs(curAlpha/10));
	float stepAlpha, newAlpha, newSum;
	if(10 > fabs(curAlpha/10))
		stepAlpha = 10;
	else
		stepAlpha = fabs(curAlpha/10);


	for(int j=0; j < 50; j++) {
		newAlpha = curAlpha + stepAlpha;
		newSum = 0;

		//x = y ./ (h + newAlpha);
		for(int k=0; k < length; k++) {
			X[k] = y[k] / (h[k] + newAlpha);
			//newSum = sum(x);
			newSum += X[k];
		}

		if(newSum > totalSum) {
			curAlpha = newAlpha;
		} else {
			if (newSum < totalSumMinus)
				stepAlpha = stepAlpha / 2;
			else return;
		}
	
	} //end of for j

} //end of function

/**********************************************************************************************************/
/**********************************************************************************************************/

void getCol(int size1, int size2, float in_matrix[size1][size2], float output[size1], int colnum) {
	for(int i=0; i<size1; i++) {
		//*(output+i) = *(in_matrix + i*size2 + (colnum-1));
		output[i] = in_matrix[i][colnum];
	}
}

/***********************************************************************************************************/
/***********************************************************************************************************/
//function X = maxColSumP (Y, H, maxColSum, precision)
void maxColSumP(int dim1, int dim2, float* Y, float* H, float* maxColSum, float precision, float* X) {
	//X = unconstrainedP (Y, H);
	unconstrainedP(dim1, dim2, Y, H, X, EPS);
	
	//Xsum = sum(X);
	float* Xsum = (float *) malloc(dim2 * sizeof(float));
	for(int i=0; i < dim2; i++){
		for(int j=0; j < dim1; j++){
			*(Xsum + i) += *(X + j*dim2 + i);
		} 
	}
	
	float* yCol = (float *)malloc(dim1 * sizeof(float));
	float* hCol = (float *)malloc(dim1 * sizeof(float));
	float* Xcol = (float *)malloc(dim1 * sizeof(float));
	//float dim = dim1*dim2;	


	//for i = find(Xsum > maxColSum)
	for(int i=0; i < dim2; i++) {
		if(*(Xsum + i) > *(maxColSum + i)) {

			//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);
			getCol(dim1, dim2, Y, yCol, i);
			getCol(dim1, dim2, H, hCol, i);

			exactTotalSum(dim1, yCol, hCol, *(maxColSum + i), precision, Xcol);
			
			for(int j=0; j < dim1; j++){
				*(X + j*dim1 + i) = *(Xcol + j);
			}

		}
	}
	free(yCol);
	free(hCol);
	free(Xcol);
	free(Xsum);

} // end of function

/***********************************************************************************************************/
/***********************************************************************************************************/
void main() {
	
	float A[4][4] = {{4, 2, 5, 91}, {4, 3, 4, 6}, {4, 9, 0, 2}, {4, 5, 2, 1}};
	float B[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	float X[4][4];
	float maxColSum[4][1] = {4, 5, 9, 25};
	float eps = 0.01;

	printf("Test Array\n");
	printMatrix(4, 4, A);

	printf("H\n");
	printMatrix(4, 4, B);

	printf("MaxColSum\n");
	printMatrix(4, 1, maxColSum);

	maxColSumP(4, 4, A, B, maxColSum, eps, X);

	printf("X \n");
	printMatrix(4, 4, X);
}
