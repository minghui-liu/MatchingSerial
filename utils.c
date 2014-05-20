/* File: utils.c
 * 
 * Utility functions for serial hypergraph matching
 *
 * Reid Delaney & Kevin Liu
 */

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
