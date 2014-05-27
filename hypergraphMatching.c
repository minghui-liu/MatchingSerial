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

void soft2hard(int size1, int size2, float soft[size1][size2], int numberOfMatches, float hard[size1][size2]) {
	zeros(size1, size2, hard);
	for (int i=0; i<numberOfMatches; i++) {
		float maxSoft[size1][1];
		maxOfMatrix(size1, size2, soft, maxSoft, 2);
		// dummy is the max element in maxSoft, r is its position in maxSoft
		float dummy = maxOfArray(size2, maxSoft);
		int r = indexOfElement(size1, maxSoft, dummy);

		// val is the max of soft(r,:), c is the index of val in soft(r,:)
		float softR[size2];
		getRow(size1,size2,soft,softR,r);
		float val = maxOfArray(size2, softR);
		int c = indexOfElement(size2, softR,val);
		
		if (val < 0)
			return;
		//*(hard+r*size2+c) = 1;
		hard[r][c] = 1;
		// soft(r,:) = -inf;
		for (int j=0; j<size2; j++) {
			//*(soft+r*size2+j) = -INFINITY;
			soft[r][j] = -INFINITY;			
		}
		// soft(:,c) = -inf;
		for (int k=0; k<size1; k++) {
			//*(soft+c*size2+k) = -INFINITY;
			soft[c][k] = -INFINITY;
		}
	}
}

void hypergraphMatching(int size1, int size2, float Y[size1][size2], int numberOfMatches, float X[size1][size2], float Z[size1][size2]) {
	// do i need to use maxRowSum[size1][1] here? Seems doesnt make a difference
	float maxRowSum[size1][1];
	ones(size1, 1, maxRowSum);
	float maxColSum[size2];
	ones(1, size2, maxColSum);
	
	nearestDSmax_RE(size1,size2,Y,maxRowSum,maxColSum,numberOfMatches,0.01,1000,Z);
	soft2hard(size1, size2, Z, numberOfMatches, X);
}


