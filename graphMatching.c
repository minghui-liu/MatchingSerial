#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.c"
#include "hypergraphMatching.c"

void graphMatching(float* G1, int size1, float* G2, int size2, float sigma, int numberOfMatches, float *X, float *Z, float *Y){

/*	Algorithm due to R. Zass and A. Shashua.,
 	'Probabilistic Graph and Hypergraph Matching.',
 	Computer Vision and Pattern Recognition (CVPR) Anchorage, Alaska, June 2008.

 	G1  				An size1 by size1 symmetric matrix, with the weight of the first graph edges.
 	G2  				An size2 by size2 symmetric matrix, with the weight of the second graph edges.
 	sigma 	 			Kernel parameter for edge-to-edge correlations.
 	numberOfMatches  	number of matches required. 

 	X [Output]  	an n1 by n2 matrix with the hard matching results.
             		The i,j entry is one iff the i-th feature of the first object
             		match the j-th feature of the second object. Zero otherwise.
 
	Z [Output]  	an n1 by n2 matrix with the soft matching results.
             		The i,j entry is the probablity that the i-th feature of the
             		first object match the j-th feature of the second object.
 
	Y [Output]  	Debug information.
*/


	//Check to make sure the matrices are symmetric	
	if(isSymmetric(G1,size1) == 0) {
		printf("G1 is not symmetric \n");
	}
	
	if(isSymmetric(G2,size2) == 0) {
		printf("G2 is not symmetric \n");
	}

	// tranpose G2
	float G2t[size2][size2];
	transpose(G2, G2t, size2, size2);
	
	// make Y an all zero matrix
	zeros(Y, size1, size2);
	float d[size1][size2], d1[size1][size2], d2[size1][size2], G1_i[size1], G2t_j[size2];

	for(int i=0; i < size1; i++) {
		for(int j=0; j < size2; j++) {
			//d = repmat(G1(:,i), 1, n2) - repmat(G2t(j, :), n1, 1);

			//...G1(:,i)...
			getCol(G1,size1,size1,G1_i,i);
			// ...G2t(j,:)...
			getRow(G2t,size2,size2,G2t_j,j);	
			//...repmat(G1(:,i), 1, n2)...
			repmat(G1_i, d1, size1, 1, 1, size2);
			//...repmat(G2t(j, :), n1, 1);
			repmat(G2t_j, d2, 1, size2, size1, 1);

			// d = ... - ...
			matSub(d1, d2, d, size1, size2);

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
					*(Y+u*size2+v) += d[u][v];
				}
			}
			
		}
	}

	/* do hypergraphMatching over Y */
	hypergraphMatching(Y, size1, size2, numberOfMatches, X, Z);

}
