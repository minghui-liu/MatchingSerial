#include <stdio.h>

/* Test code segment from nearestDSmax_RE.c */

float sumY(float* Y, int m, int n);

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
/*
 * Code segment from nearestDSmax_RE.c that
 * corresponds to matlab line " sum(Y(:))"
 *
 */
float sumY(float* Y, int m, int n){
	//sum(Y(:))
	float Ysum = 0;
	for(int i=0; i < m; i++){
		for(int j=0; j < n; j++){

			Ysum += *(Y + i*n + j);

		}
	}
	return Ysum;
}

void main(){
	float A[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	printMatrix(A,3,3);
	float Ysum;
	Ysum = sumY(A, 3, 3);
	printf("%.2f\n", Ysum);
}
