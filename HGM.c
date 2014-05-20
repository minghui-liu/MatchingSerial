#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

	
	return 0;
}


void graphMatching(float* G1, int size1, float* G2, int size2, float sigma, int numberOfMatches){

/*	Algorithm due to R. Zass and A. Shashua.,
 	'Probabilistic Graph and Hypergraph Matching.',
 	Computer Vision and Pattern Recognition (CVPR) Anchorage, Alaska, June 2008.

 	G1  				An n1 by n1 symmetric matrix, with the weight of the first graph edges.
 	G2  				An n2 by n2 symmetric matrix, with the weight of the second graph edges.
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
// size1 and size2 are the dimensions of G1 and G2

//Check to make sure the matrices are symmetric	
	float diff;
	for(int i=0; i < size1; i++){
		for(int j=0; j < size1; j++){
			diff = (G1 + sizeof(float)*i*size1 + sizeof(float)*j) - (G1 + sizeof(float)*j*size1 + sizeof(float)*i);
			if(diff > 1e-6){
				System.out.print("G1 is not symmetric\n");
				return;
			}
		}
	}

	for(int i=0; i < size2; i++){
		for(int j=0; j < size2; j++){
			diff = (G2 + sizeof(float)*i*size2 + sizeof(float)*j) - (G2 + sizeof(float)*j*size2 + sizeof(float)*i);
			if(diff > 1e-6){
				System.out.print("G2 is not symmetric\n");
				return;
			}
		}
	}

	float G2t[size2][size2];
	for(int i=0; i<size2; i++){
		for(int j=0; j<size2; j++){
			G2t[i][j] = *(G2 + sizeof(float)*j*size2 + sizeof(float)*i);
		}
	}

	float Y[size1][size2];
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			Y[i][j] = 0;
		}
	}


}
