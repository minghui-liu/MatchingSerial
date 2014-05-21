#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* 
function [X,Z] = hypergraphMatching (Y, numberOfMatches)

Optimal soft hyergraph matching.

Algorithm due to R. Zass and A. Shashua.,
'Probabilistic Graph and Hypergraph Matching.',
Computer Vision and Pattern Recognition (CVPR) Anchorage, Alaska, June 2008.

Y - Marginalization of the hyperedge-to-hyperedge correspondences matrix.
numberOfMatches - number of matches required.

X [Output] - an n1 by n2 matrix with the hard matching results.
             The i,j entry is one iff the i-th feature of the first object
             match the j-th feature of the second object. Zero otherwise.
Z [Output] - an n1 by n2 matrix with the soft matching results.
             The i,j entry is the probablity that the i-th feature of the
             first object match the j-th feature of the second object.

See also:
- graphMatching() as an example on how to use this for graphs with a
  specific similarity function.

Author: Ron Zass, zass@cs.huji.ac.il, www.cs.huji.ac.il/~zass
*/

void main(){
	return 0;
}

void hypergraphMatching(float* Y, int numberOfMatches, int size1, int size2){
//size1 = n1, size2 = n2

	float maxRowSum[size1][1];
	ones(maxRowSum, size1, 1);
	float maxColumnSum[1][size2];
	ones(maxColumnSum, 1, size2);
	float Z[size1][size2];
	
}