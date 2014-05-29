/* a test program for indexOfElement() */

#include <stdio.h>

/* find an element in an array and return its index 
 * note: this function only returns the index of the 
 * first match element
 */
int indexOfElement(float *in, int size, float element) {
	for (int i=0; i<size; i++) {
		if (*(in + i) == element)
			return i;
	}
	return -1;
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
	float A[6] = {1,2,3,4,5,6};
	printMatrix(A,1,6);
	int idx = indexOfElement(A,6,4);
	printf("%d\n",idx);
}
