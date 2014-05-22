/* test program for transpose function */

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
	return &out_matrix;
}

void main() {
	float A[3][2] = {{1,4},{2,5},{3,6}};
	float B[2][3];
	transpose(A,B,3,2);
	// print A
	for (int i=0; i<3; i++){
		for(int j=0; j<2; j++) {
			printf("%.2f ", B[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	// print B
	for (int i=0; i<2; i++){
		for(int j=0; j<3; j++) {
			printf("%.2f ", B[i][j]);
		}
		printf("\n");
	}
}
