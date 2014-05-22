/* a test program for matSub() */
#include <stdio.h>

/* Perform matrix subtraction and return the difference between two matrices 
 * in_matrix1 in_matrix2: input matrices
 * diff: output matrix
 * dim1 dim2: the dimension of the matrices 
 */
void matSub(float *in_matrix1, float *in_matrix2, float* diff, int dim1, int dim2){
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			*(diff + i * dim2 + j) = *(in_matrix1 + i * dim2 + j) - *(in_matrix2 + i * dim2 + j);
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
			printf("%.2f ", *(matrix + i*size2 + j));
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	float A[2][3] = {{1,2,3},{4,5,6},{7,8,9}};
	printMatrix(A,2,3);
	float B[2][3] = {{1,1,1},{1,1,1},{1,1,1}};
	printMatrix(B,2,3);
	float diff[2][3];
	matSub(A,B,diff,2,3);
	printMatrix(diff,2,3);
}
