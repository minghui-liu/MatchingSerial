#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.c"
#include "hypergraphMatching.c"

void graphMatching(int size1, float G1[size1][size1], int size2, float G2[size2][size2], float sigma, int numberOfMatches, float X[size1][size2], float Z[size1][size2], float Y[size1][size2]){

/*	Algorithm due to R. Zass and A. Shashua.,
 	'Probabilistic Graph and Hypergraph Matching.',
 	Computer Vision and Pattern Recognition (CVPR) Anchorage, Alaska, June 2008.

 	G1  				An size1 by size1 symmetric matrix, with the weight of the first graph edges.
 	G2  				An size2 by size2 symmetric matrix, with the weight of the second graph edges.
 	sigma 	 			Kernel parameter for edge-to-edge correlations.
 	numberOfMatches  	number of matches required. 

 	X [Output]  	a size1 by size2 matrix with the hard matching results.
             		The i,j entry is one iff the i-th feature of the first object
             		match the j-th feature of the second object. Zero otherwise.
 
	Z [Output]  	a size1 by size2 matrix with the soft matching results.
             		The i,j entry is the probablity that the i-th feature of the
             		first object match the j-th feature of the second object.
 
	Y [Output]  	Debug information.
*/


	//Check to make sure the matrices are symmetric	
	if(isSymmetric(size1, G1) == 0) {
		printf("G1 is not symmetric \n");
	}
	
	if(isSymmetric(size2, G2) == 0) {
		printf("G2 is not symmetric \n");
	}

	// tranpose G2
	float G2t[size2][size2];
	transpose(size2, size2, G2, G2t);
	
	// make Y an all zero matrix
	zeros(size1, size2, Y);
	float d[size1][size2], d1[size1][size2], d2[size1][size2], G1_i[size1][1], G2t_j[1][size2];

	for(int i=0; i < size1; i++) {
		for(int j=0; j < size2; j++) {
			//d = repmat(G1(:,i), 1, n2) - repmat(G2t(j, :), n1, 1);

			//...G1(:,i)...
			getCol(size1, size1, G1, G1_i, i);
			// ...G2t(j,:)...
			getRow(size2, size2, G2t, G2t_j, j);	
			//...repmat(G1(:,i), 1, n2)...
			repmat(size1, 1, G1_i, 1, size2, d1);
			//...repmat(G2t(j, :), n1, 1);
			repmat(1, size2, G2t_j, size1, 1, d2);

			// d = ... - ...
			matSub(size1, size2, d1, d2, d);

			//Y = Y + exp((-d.*d) ./ sigma);

			//exp((-d.*d) ./ sigma)
			for(int k=0; k < size1; k++) {
				for(int l=0; l < size2; l++) {
					d[k][l] = exp((-d[k][l] * d[k][l]) / sigma);
				}
			}

			// Y = Y + ...
			for(int u=0; u < size1; u++) {
				for(int v=0; v < size2; v++) {
					Y[u][v] += d[u][v];
				}
			}
			
		}
	}

	/* do hypergraphMatching over Y */
	hypergraphMatching(size1, size2, Y, numberOfMatches, X, Z);

}
