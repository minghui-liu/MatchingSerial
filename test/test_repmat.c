#include <stdio.h>

/* creates a m*n tiling of a matrix */
void repmat(int size1, int size2, float in_matrix[size1][size2], int m, int n, float out_matrix[size1*m][size2*n]) {
	for(int i=0; i<size1*m; i++) {
		for(int j=0; j<size2*n; j++) {
			//*(out_matrix + i*size2*n + j) = *(in_matrix + (i%size1)*size2 + (j%size2));
			out_matrix[i][j] = in_matrix[i%size1][j%size2];
		}
	}
}

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

int main() {
	float a[3][2] = {{1.0,4.0},{2.0,5.0},{3.0,6.0}};
	printMatrix(3,2,a);
	float out_matrix[9][6];
	repmat(3,2,a,3,3,out_matrix);
	printMatrix(9,6,out_matrix);
	
}

