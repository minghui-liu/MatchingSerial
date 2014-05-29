/* test column vector printing */

#include <stdio.h>

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
	float col[4] = {1,2,3,4};
	printMatrix(col,4,1);
	float col2[4][1] = {{1},{2},{3},{4}};
	printMatrix(col2,4,1);
}

