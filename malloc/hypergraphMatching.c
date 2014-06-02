/* File: hypergraphMatching.c
 *
 * Optimal soft hyergraph matching.
 *
 * Algorithm due to R. Zass and A. Shashua.,
 * 'Probabilistic Graph and Hypergraph Matching.',
 * Computer Vision and Pattern Recognition (CVPR) Anchorage, Alaska, June 2008.
 *
 * Y - Marginalization of the hyperedge-to-hyperedge correspondences matrix.
 * numberOfMatches - number of matches required.
 *
 * X [Output] - an n1 by n2 matrix with the hard matching results.
 *             The i,j entry is one iff the i-th feature of the first object
 *             match the j-th feature of the second object. Zero otherwise.
 * Z [Output] - an n1 by n2 matrix with the soft matching results.
 *             The i,j entry is the probablity that the i-th feature of the
 *             first object match the j-th feature of the second object.
 *
 *  See also:
 *  - graphMatching() as an example on how to use this for graphs with a
 *  specific similarity function.
 */
 
#include <math.h>
#include "utils.c"
#include "nearestDSmax_RE.c"

void soft2hard(int size1, int size2, float* soft, int numberOfMatches, float* hard) {

	float* softTemp = (float *)malloc(size1*size2*sizeof(float));

	for (int i=0; i<size1; i++) {
		for (int j=0; j<size2; j++) {
			*(softTemp + i*size2 + j) =  *(soft + i*size2 + j);
		}
	}

	zeros(size1, size2, hard);
	float* maxSoft = (float *)malloc(size1 * sizeof(float));
	float* softR = (float *)malloc(size2 * sizeof(float));

	for (int i=0; i<numberOfMatches; i++) {

//		printf("i is now %d\n", i);
//		printMatrix(size1, size2, softTemp);

		maxOfMatrix(size1, size2, softTemp, maxSoft, 2);

//		printf("MaxSoft is\n");
//		printMatrix(size1, 1, maxSoft);

		// dummy is the max element in maxSoft, r is its position in maxSoft
		float dummy = *(maxSoft);
		for (int i=0; i<size1; i++) {
			dummy = (dummy > *(maxSoft + i))? dummy : *(maxSoft + i);
		}
		int r = indexOfElement(size1, maxSoft, dummy);

//		printf("Dummy is %f and r is %d\n", dummy, r);
		
		// val is the max of soft(r,:), c is the index of val in soft(r,:)

//		printf("maxSoft 2 is\n");
//		printMatrix(size1, 1, maxSoft);
	
		getRow(size1,size2,softTemp,softR,r);

//		printf("softR\n");
//		printMatrix(size1, 1, softR);
		float val = *(softR);
		for (int i=0; i<size2; i++) {
			val = (val > *(softR + i))? val : *(softR + i);
		}
		int c = indexOfElement(size2, softR,val);
//		printf("val is now %.2f\n", val);
		if (val < 0){
//			printf("I'm returning now\n");
			return;
		}
		*(hard+r*size2+c) = 1;
		//hard[r][c] = 1;
		// soft(r,:) = -inf;
		for (int j=0; j<size2; j++) {
			*(softTemp+r*size2+j) = -INFINITY;
			//softTemp[r][j] = -INFINITY;			
		}
		// soft(:,c) = -inf;
		for (int k=0; k<size1; k++) {
			*(softTemp+k*size2+c) = -INFINITY;
			//softTemp[k][c] = -INFINITY;
		}
		
	}

	free(softTemp);
	free(maxSoft);
	free(softR);

}

void hypergraphMatching(int size1, int size2, float* Y, int numberOfMatches, float* X, float* Z) {
	// do i need to use maxRowSum[size1][1] here? Seems doesnt make a difference
	float* maxRowSum = (float *)malloc(size1 * sizeof(float));
	ones(size1, 1, maxRowSum);
	float* maxColSum = (float *)malloc(size2 * sizeof(float));
	ones(1, size2, maxColSum);
	
	nearestDSmax_RE(size1,size2,Y,maxRowSum,maxColSum,numberOfMatches,0.01,1000,Z);
	soft2hard(size1, size2, Z, numberOfMatches, X);

	free(maxRowSum);
	free(maxColSum);
}


