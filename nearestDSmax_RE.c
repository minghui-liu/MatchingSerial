#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
function F = nearestDSmax_RE (Y, maxRowSum, maxColSum, totalSum, precision, maxLoops)

Find the nearest matrix with non-negative entries and row / column sum at
most rowSum / colSum, to A in relative entropy.

Algorithm due to R. Zass and A. Shashua.,
'Probabilistic Graph and Hypergraph Matching.',
Computer Vision and Pattern Recognition (CVPR) Anchorage, Alaska, June 2008.

Y - an m by n non-negative matrix.
maxRowSum - a non-negative column vector of length m with the maximal allowed rows sum.
maxColSum - a non-negative row vector of length n with the maximal allowed columns sum.
totalSum - a non-negative scalar, the desired sum of all elements.
precision [Optional, default=0.01] - break when the each row/column sum is at most precision away from the desired sum.
maxLoops [Optional, defalut=1000] - Max number of iterations to perform.

F [Output] - The nearest generalized doubly stochastic F to Ker in relative entropy.

Author: Ron Zass, zass@cs.huji.ac.il, www.cs.huji.ac.il/~zass 
*/

void nearestDSmax_RE(float* Y, int m, int n, float* maxRowSum, float* maxColSum, float totalSum, float precision, float maxLoops){
//m and n are the dimensions of Y

/*
 *   lambda1 = zeros(size(Y));
 *   lambda2 = lambda1;
 *   lambda3 = lambda1;
 */
	float lambda1[m][n];
	float lambda2[m][n];
	float lambda3[m][n];
	zeros(lambda1, m, n);
	zeros(lambda2, m, n);
	zeros(lambda3, m, n);

/*    
 *	F1 = totalSum * (Y ./ sum(Y(:)));
 *  F2 = F1;
 *  F3 = F1;
 */
	float F1[m][n];
	float F2[m][n];
	float F3[m][n];

	//sum(Y(:))
	float Ysum = 0;
	for(int i=0; i < m; i++){
		for(int j=0; j < n; j++){
			Ysum += *(Y + i*n + j);
		}
	}

	for(int i=0; i < m; i++){
		for(int j=0; j < n; j++){
			F1[i][j] = totalSum * (*(Y + i*n + j) / Ysum);
			F2[i][j] = F3[i][j] = F1[i][j];
		}
	}

	float H1[m][n];
	float H2[m][n];
	float H3[m][n];

	//for t = 1 : maxLoops
	for(int t=0; t < maxLoops; t++) {
 		// Max row sum 
		// H1 = lambda1 - (Y ./ (F3+eps));
		float F3eps[m][n];
		matPlusScaler(F3, eps, F3eps, m, n);
		float Ydiv[m][n]; 
		matDiv(Y, F3eps, Ydiv, m, n)
		matSub(lambda1, Ydiv, H1, m, n);
		
		// (Y ./ (F3 + eps))

		// F1 = maxColSumP (Y', -H1', maxRowSum', precision)';
		
		// lambda1 = lambda1 - (Y ./ (F3+eps)) + (Y ./ (F1+eps));
		
 		transpose(maxColSumP())
	}
}

void maxColSumP(float* Y, int Ydim1, int Ydim2, float* H, float maxColSum, float precision, float* X){
	//function X = maxColSumP (Y, H, maxColSum, precision)

	//X = unconstrainedP (Y, H);
	unconstrainedP(Y, H, X, Ydim1, Ydim2, precision);

	//Xsum = sum(X);
	for(int i=0; i < Ydim1; i++){
		for(int j=0; j < Ydim2; j++){
			Xsum += *(X + i*Ydim2 + j);
		}
	}

	//for i = find(Xsum > maxColSum)
	//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);
}

void unconstrainedP(float* Y, float* H, float* X, int size1, int size2, float eps){
	//function X = unconstrainedP (Y, H)
	for(int i=0; i<size1; i++) {
		for(int j=0; j<size2; j++) {
			//X = Y ./ H;
			*(X + i*size2 + j) = *(Y + i*size2 + j) / *(H + i*size2 + j);

			//X(find(X < eps)) = eps;
			if(*(X + i*size2 + j) < eps) {
				*(X + i*size2 + j) = eps;
			}
		}
	}
}

void exactTotalSum(float* y, float* h, float totalSum, float precision){
//function x = exactTotalSum (y, h, totalSum, precision)
// y and h are vectors, totalSum and precision are scalars


}
