#include <stdio.h>

/* gets one row from a matrix 
 * in_matrix: input matrix
 * size: the length of one row
 * output: an array containing the row
 * rownum: row number
 */
void getRow(int size1, int size2, float in_matrix[size1][size2], float output[1][size2], int rownum) {
	for(int i=0; i<size2; i++) {
		//*(output+i) = *(in_matrix + (rownum-1)*size2 + i);
		output[0][i] = in_matrix[rownum][i];
	}
}

/* gets one column from a matrix 
 * in_matrix: input matrix
 * size: the length of one column
 * output: an array containing the column
 * colnum: column number
 */
void getCol(int size1, int size2, float in_matrix[size1][size2], float output[size1][1], int colnum) {
	for(int i=0; i<size1; i++) {
		//*(output+i) = *(in_matrix + i*size2 + (colnum-1));
		output[i][0] = in_matrix[i][colnum];
	}
}

/* prints a matrix 
 * matrix: pointer to the matrix to be printed
 * size1 size2: size of matrix
 */
void printMatrix( int size1, int size2, float matrix[size1][size2]) {
	for (int i=0; i<size1; i++){
		for(int j=0; j<size2; j++) {
			//printf("%.2f ", *(matrix + i*size2 + j));
			printf("%.2f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void main() {
	float A[2][3] = {{1,2,3},{4,5,6}};
	printMatrix(2,3,A);
	float row[1][3], col[2][1];
	getRow(2,3,A,row,1);
	printMatrix(1,3, row);
	getCol(2,3,A,col,2);
	printMatrix(1,2, col);
}
