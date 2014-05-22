/* a test program for zeros() and ones() */

#include <stdio.h>

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

void main() {
	float A[4][5];
	zeros(A,4,5);
	// print A
	for (int i=0; i<4; i++){
		for(int j=0; j<5; j++) {
			printf("%.2f ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	ones(A,4,5);
	// print A
	for (int i=0; i<4; i++){
		for(int j=0; j<5; j++) {
			printf("%.2f ", A[i][j]);
		}
		printf("\n");
	}

}
