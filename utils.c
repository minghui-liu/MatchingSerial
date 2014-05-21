/* File: utils.c
 * 
 * Utility functions for serial hypergraph matching
 *
 * Reid Delaney & Kevin Liu
 */

#include <stdio.h>
#include <math.h>

/* transpose a size1*size2 matrix
 * returns a pointer to the new matrix
 */
void transpose(float *in_matrix, float *out_matrix, int size1, int size2) {
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			*(out_matrix + j*size1 + i) = *(in_matrix + i*size2 + j);
		}
	}
}

/* make Y an all zero matrix
 * size1 and size2 are the size of Y
 */
void zeros(float *Y, int size1, int size2){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			*(Y + (i*size2 + j) ) = 0;
		}
	}
}

/* make Y an all one matrix
 * size1 and size2 are the size of Y
 */
void ones(float *Y, int size1, int size2){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			*(Y + (i*size2 + j) ) = 1;
		}
	}
}

/* check if a square matrix is symmetric
 * size: the size of the matrix
 * returns 1 if true, 0 if false
 */
int isSymmetric(float *in_matrix, int size){
	double diff;
	for(int i=0; i < size; i++){
		for(int j=0; j < size; j++){
			diff = *(in_matrix + i*size + j) - *(in_matrix + j*size + i);
			if(diff != 0){
				return 0;
			}
		}
	}
	return 1;
}

/* check if a square matrix is symmetric with an epsilon eps
 * size: the size of the square matrix
 * eps: the epsilon value
 * returns 1 if true 0 if false
 */
int isSymmetric_eps(float *in_matrix, int size, double eps) {
	double diff;
	for(int i=0; i < size; i++){
		for(int j=0; j < size; j++){
			diff = *(in_matrix + i*size + j) - *(in_matrix + j*size + i);
			if(diff > eps || diff < -eps){
				return 0;
			}
		}
	}
	return 1;
}

/* creates a m*n tiling of a matrix */
void repmat(float *in_matrix, float *out_matrix, int size1, int size2, int m, int n) {
	for(int i=0; i<size1*m; i++) {
		for(int j=0; j<size2*n; j++) {
			*(out_matrix + i*size2*n + j) = *(in_matrix + (i%size1)*size2 + (j%size2));
		}
	}
}

/* find the maximum */

/* Perform array subtraction and return the new array */
void matSub(float* diff, float* op1, float* op2, int dim1, int dim2){
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			*(diff + i * dim1 + j) = *(op1 + i * dim1 + j) - *(op2 + i * dim1 + j);
		}
	}
}
/* find the maximum element in an array */
float maxOfArray(float *array, int size) {
	float m = array[0];
	for (int i=1; i<size; i++) {
		m = max(m, array[i]);
	}
	return m;
}

/* find the maximum elements in a matrix
 * dim: the dimension wrt which you want to find the maximums
 * 
 * Example:
 * Consider the following matrix A:
 * 	1 2 3
 * 	4 5 6
 * 	7 8 9
 * maxOfMatrix(A,1) will return [7 8 9]
 * maxOfMatrix(A,2) will return [3 6 9]                            
 */
void maxOfMatrix(float *matrix, int size1, int size2, float *out, int dim) {
	if (dim == 1) {
		for(int i=0; i<size2; i++) {
			float m = *(matrix + i);
			for (int j=0; j<size1; j++) {
				m = max(m, *(matrix+j*size2+i));
			}
			*(out + i) = m;
		}

	}
}
