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
float* transpose(float *in_matrix, int size1, int size2) {
	float out_matrix[size2][size1];
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			out_matrix[j][i] = *(matrix + sizeof(float)*i*size2 + sizeof(float)*j);
		}
	}
	return &out_matrix;
}

/* make Y an all zero matrix
 * size1 and size2 are the size of Y
 */
void zeros(float *Y, int size1, int size2){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			*(Y + (i*size1*sizeof(float) + (j*sizeof(float)*size2))) = 0;
		}
	}
}

/* make Y an all one matrix
 * size1 and size2 are the size of Y
 */
void ones(float *Y, int size1, int size2){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			*(Y + (i*size1*sizeof(float) + (j*sizeof(float)*size2))) = 1;
		}
	}
}

/* check if a square matrix is symmetric
 * size: the size of the matrix
 * returns 1 if true, 0 if false
 */
int isSymmetric(float *in_matrix, int size){
	for(int i=0; i < size; i++){
		for(int j=0; j < size; j++){
			diff = *(in_matrix + sizeof(float)*i*size + sizeof(float)*j) - *(in_matrix + sizeof(float)*j*size + sizeof(float)*i);
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
int isSymmetric(double *in_matrix, int size, double eps) {
	for(int i=0; i < size; i++){
		for(int j=0; j < size; j++){
			diff = *(in_matrix + sizeof(float)*i*size + sizeof(float)*j) - *(in_matrix + sizeof(float)*j*size + sizeof(float)*i);
			if(diff > eps || diff < -eps){
				return 0;
			}
		}
	}
	return 1;
}

