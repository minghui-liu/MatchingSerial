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

void hypergraphMatching(float *Y, int size1, int size2, int numberOfMatches, float *X, float*Z) {
	float maxRowSum[size1];
	ones(maxRowSum, size1, 1);
	float maxColSum[size2];
	ones(maxColSum, 1, size2);
	
	nearestDSmax_RE(Y, maxRowSum, maxColumSum, numberOfMatches, Z);
	soft2hard(Z, numberOfMatches, X);
}

void soft2hard(float *soft, int size1, size2, float *hard, int numberOfMatches, float *hard) {
	zeros(hard, size1, size2);
	for (int i=0; i<numberOfMatches; i++) {
		float maxSoft[size1][1];
		maxOfMatrix(soft, size1, size2, &maxSoft, 2)
		// dummy is the max element in maxSoft, r is its position in maxSoft
		float dummy = maxOfArray(maxSoft,size2);
		int r = indexOfElement(maxSoft, size1, dummy);

		// val is the max of soft(r,:), c is the index of val in soft(r,:)
		float softR[size2];
		getRow(soft,size1,size2,softR,r);
		float	val = maxOfArray(softR,size2);
		int c = indexOfElement(softR, size2, val);
		
		if (val < 0)
			return;
		hard[r][c] = 1;
		// soft(r,:) = -inf;
		for (int j=0; j<size2; j++) {
			*(soft+r*size2+j) = -INFINITY;				
		}
		// soft(:,c)
		for (in k=0; k<size1; k++) {
			*(soft+k*size2+k) = -INFINITY;
		}
	}
}

