/* a test program for isSymmetric() function */

#include <stdio.h>

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

void main() {
	float A[3][3] = {{2,1,1},{1,2,1},{1,1,2}};
	// print A
	for (int i=0; i<3; i++){
		for(int j=0; j<3; j++) {
			printf("%.1f ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	int result = isSymmetric(A, 3);
	printf("%d\n\n", result);		
	
	float B[4][4] = {{4,3,2,1},{3,4,3,2},{2,3,4,3},{1,2,3,4}};
	// print B
	for (int i=0; i<4; i++){
		for(int j=0; j<4; j++) {
			printf("%.1f ", B[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	result = isSymmetric_eps(B, 4, 1e-10);
	printf("%d\n\n", result);
	
	float C[4][4] = {{0,3,2,1},{3,4,3,2},{0,3,4,3},{0,2,3,4}};
	// print C
	for (int i=0; i<4; i++){
		for(int j=0; j<4; j++) {
			printf("%.1f ", C[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	result = isSymmetric_eps(C, 4, 1e-8);
	printf("%d\n\n", result);


}
