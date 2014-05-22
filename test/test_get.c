#include <stdio.h>

/* gets one row from a matrix 
 * in_matrix: input matrix
 * size: the length of one row
 * output: an array containing the row
 * rownum: row number
 */
void getRow(float *in_matrix, int size1,int size2, float *output, int rownum) {
	for(int i=0; i<size2; i++) {
		*(output+i) = *(in_matrix + (rownum-1)*size2 + i);
	}
}

/* gets one column from a matrix 
 * in_matrix: input matrix
 * size: the length of one column
 * output: an array containing the column
 * colnum: column number
 */
void getCol(float *in_matrix, int size1, int size2, float *output, int colnum) {
	for(int i=0; i<size1; i++) {
		*(output+i) = *(in_matrix + i*size2 + (colnum-1));
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
	float A[2][3] = {{1,2,3},{4,5,6}};
	printMatrix(A,2,3);
	float row[3], col[2];
	getRow(A,2,3,row,2);
	printMatrix(row,1,3);
	getCol(A,2,3,col,3);
	printMatrix(col,1,2);
}
