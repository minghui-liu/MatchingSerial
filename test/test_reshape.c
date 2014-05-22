#include <stdio.h>

/* reshapes a matrix into another dimension
 * the number of elements must remain the same
 */
void reshape(float *in, int insize1, int insize2, float *out, int outsize1, int outsize2) {
	if (insize1*insize2 == outsize1*outsize2) {
		int c = 0;
		for (int i=0; i<insize2; i++) {
			for (int j=0; j<insize1; j++) {
				*(out+(c%outsize1)*outsize2+(c/outsize1)) = *(in+j*insize2+i);
				c++;
			}
		}
	} else	
		printf("Error: cannot reshape. the number of elements must agree");
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
	float A[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	printMatrix(A,3,4);
	float B[4][3];
	reshape(A,3,4,B,4,3);
	printMatrix(B,4,3);
	float C[2][6];
	reshape(A,3,4,C,2,6);
	printMatrix(C,2,6);
}
