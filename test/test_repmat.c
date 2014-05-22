#include <stdio.h>

/* creates a m*n tiling of a matrix */
void repmat(float *in_matrix, int size1, int size2, int m, int n, float *out_matrix) {
	for(int i=0; i<size1*m; i++) {
		for(int j=0; j<size2*n; j++) {
			*(out_matrix + i*size2*n + j) = *(in_matrix + (i%size1)*size2 + (j%size2));
		}
	}
}

int main() {
	float a[3][2] = {{1.0,4.0},{2.0,5.0},{3.0,6.0}};
	float *p = a;
	for (int i=0; i<3; i++){
		for(int j=0; j<2; j++) {
			printf("%.2f ", *(p + i*2 + j));
		}
		printf("\n");
	}
	
	printf("\n\n");
	float out_matrix[9][6];
	repmat(a,3,2,3,3,out_matrix);
	
	for (int i=0; i<9; i++){
		for(int j=0; j<6; j++) {
			printf("%.2f ", out_matrix[i][j] );
		}
		printf("\n");
	}

}

