#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.c"

int main(void) {
	return 0;
}


void graphMatching(float* G1, int size1, float* G2, int size2, float sigma, int numberOfMatches){

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

	int check;

	check = isSymmetric(G1, size1);
	if(check == 0){
		System.out.print("G1 is not symmetric \n");
	}
	
	check = isSymmetric(G2, size2);
	if(check == 0){
		System.out.print("G2 is not symmetric \n");
	}
	

	// tranpose G2
	float *G2t = transpose(G2, size2, size2);
	
	// creat Y and make it an all zero matrix
	float Y[size1][size2];
	zeros(Y, size1, size2);
	double* d, d1, d2, G1rep, G2trep;

	for(int i=0; i < size1; i++){
		for(int j=0; j < size2; j++){

//d = repmat(G1(:,i), 1, n2) - repmat(G2t(j, :), n1, 1);

			//...G1(:,i)...
			for(int k=0; k < size1; k++){
				G1rep[k] = G1[k][i];
			}
			// ...G2t(j,:)...
			for(int k=0; k < size2; k++){
				G2trep[k] = G2t[j][k];
			}
	
			//...repmat(G1(:,i), 1, n2)...
			repmat(G1rep, d1, size1, 1, 1, size2);

			//...repmat(G2t(j, :), n1, 1);
			repmat(G2trep, d2, 1, size2, size1, 1);

			// d = ... - ...
			matSub(d, d1, d2);

//Y = Y + exp((-d.*d) ./ sigma);

			//exp((-d.*d) ./ sigma)
			for(int i=0; i < dimD; i++){
				for(int j=0; j<dimD2; j++){
					d[i][j] = exp((-d[i][j] * d[i][j]) / sigma);
				}
			}

			// Y = Y + ...
			for(int i=0; i < size1; i++){
				for(int j=0; j<size2; j++){
					Y[i][j] += d[i][j];
				}
			}
			
		}
	}
}
