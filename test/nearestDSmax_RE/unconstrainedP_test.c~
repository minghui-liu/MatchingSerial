#include <stdio.h>

/* Test to see if the function unconstrainedP from nearestDSmax_RE.c works correctly */

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

void main() {
	
	float A[4][4] = {{1,2,3, 4},{4,0,6, 7},{0,8,9, 1}, {12, 3, 0, 4}};
	float B[4][4] = {{1,2,3, 4},{4,5,6, 7},{7,8,9, 1000}, {6, 4, 2, 9}};
	float X[4][4];
	float eps = 0.01;
	unconstrainedP(4, 4, A, B, X, eps);
	printMatrix(4, 4, A);
	printMatrix(4, 4, B);
	printMatrix(4, 4, X);
}
