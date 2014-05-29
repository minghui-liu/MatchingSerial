/* a test program for matTimesScaler() and matPlusScaler() */
#include <stdio.h>

/* Perform matrix and scaler addtion and return the sum 
 * in_matrix1: input matrix
 * scaler: input scaler
 * product: output matrix
 * dim1 dim2: the dimension of the matrix 
 */
void matTimesScaler(float *in_matrix, float scaler, float* product, int dim1, int dim2) {
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			*(product + i * dim2 + j) = *(in_matrix + i * dim2 + j) * scaler;
		}
	}
}

/* Perform matrix and scaler multiplication and return the product 
 * in_matrix1: input matrix
 * scaler: input scaler
 * sum: output matrix
 * dim1 dim2: the dimension of the matrix 
 */
void matPlusScaler(float *in_matrix, float scaler, float* sum, int dim1, int dim2) {
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			*(sum + i * dim2 + j) = *(in_matrix + i * dim2 + j) + scaler;
		}
	}
}

/* Perform element wise matrix division
 * in_matrix1 in_matrix2: input matrices
 * out: output matrix
 * dim1 dim2: the dimension of the matrices 
 */
void matDiv(float *in_matrix1, float *in_matrix2, float* out, int dim1, int dim2){
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			*(out + i * dim2 + j) = *(in_matrix1 + i * dim2 + j) / *(in_matrix2 + i * dim2 + j);
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
	float Bp2[2][3];
	matPlusScaler(B,2,Bp2,2,3);
	printMatrix(Bp2,2,3);
	float At2[2][3];
	matTimesScaler(A,2,At2,2,3);
	printMatrix(At2,2,3);
	float At2DA[2][3];
	matDiv(At2,A,At2DA,2,3);
	printMatrix(At2DA,2,3);
}
