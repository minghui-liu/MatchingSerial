/* a test program for maxOfArray() and maxOfMatrix() */
#include <stdio.h>
/* find the maximum element in an array */
float maxOfArray(float *array, int size) {
	float m = array[0];
	for (int i=1; i<size; i++) {
		m = (m > array[i])? m : array[i];
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
				m = (m > *(matrix+j*size2+i))? m : *(matrix+j*size2+i);
			}
		*(out + i) = m;
		}
	} else if (dim = 2) {
		for(int i=0; i<size1; i++) {
			float m = *(matrix + i*size2);
			for (int j=0; j<size2; j++) {
				m = (m > *(matrix+i*size2+j))? m : *(matrix+i*size2+j);
			}
		*(out + i) = m;
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
			printf("%.1f ", *(matrix + i*size2 + j));
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	float a[6] = {1,2,3,4,5,6};
	float m = maxOfArray(a,6);
	printMatrix(a,1,6);
	printf("%.1f\n\n",m);
	
	float A[2][3] = {{1,2,3},{4,5,6},{7,8,9}};
	printMatrix(A,2,3);
	float maxOfA1[3];
	float maxOfA2[2];
	maxOfMatrix(A,2,3,maxOfA1,1);
	maxOfMatrix(A,2,3,maxOfA2,2);
	printMatrix(maxOfA1,1,3);
	printMatrix(maxOfA2,1,2);
}
