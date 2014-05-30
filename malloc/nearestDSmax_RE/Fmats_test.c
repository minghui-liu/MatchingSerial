#include <stdio.h>

/* testing code segment from nearestDSmax_RE.c */

void Fmats(float* Y, float* F1, float* F2, float* F3, float totalSum, float Ysum, int m, int n){
	for(int i=0; i < m; i++){
		for(int j=0; j < n; j++){

			*(F1 + i*n + j) = totalSum * (*(Y + i*n + j) / Ysum);
			*(F2 + i*n + j) = *(F3 + i*n + j) = *(F1 + i*n + j);

		}
	}
}

/* prints a matrix 
 * matrix: pointer to the matrix to be printed
 * size1 size2: size of matrix
 */
void printMatrix(float *matrix, int size1, int size2) {
	for (int i=0; i<size1; i++){
		for(int j=0; j<size2; j++) {
			printf("%.1f ", *(matrix + i*size2 + j));
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	float Y[2][3] = {{2, 3, 6}, {1, 0, 9}};
	float F1[2][3], F2[2][3], F3[2][3];
	float totalSum = 32 ;
	float Ysum = 21 ;
	Fmats(Y, F1, F2, F3, totalSum, Ysum, 2, 3);
	printMatrix(F1, 2, 3);
	printMatrix(F2, 2, 3);
	printMatrix(F3, 2, 3);
}
