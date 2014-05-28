#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
void maxColSumP(int dim1, int dim2, float Y[dim1][dim2], float H[dim1][dim2], float maxColSum[dim1][1], float precision, float X[dim1][dim2]) {
	//X = unconstrainedP (Y, H);
	unconstrainedP(dim1, dim2, Y, H, X, precision);
	
	//Xsum = sum(X);
	float Xsum[dim1][1];
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			Xsum[i][0] += X[j][i];
		} 
	}

	float yCol[dim2], hCol[dim2], Xcol[dim2];
	float dim = dim1*dim2;	

//for i = find(Xsum > maxColSum)
	for(int i=0; i < dim1; i++){
		if(Xsum[i][0] > maxColSum[i][0]){

//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);
			getCol(dim1, dim2, Y, yCol, i);
			getCol(dim1, dim2, H, hCol, i);

			exactTotalSum(dim1, yCol, hCol, maxColSum[i][0], precision, Xcol);
			
			for(int j=0; j < dim1; j++){
				X[j][i] = Xcol[j];
			}
		}
	}
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
