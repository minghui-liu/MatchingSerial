#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.c"

#define EPS 1e-5
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


//function x = exactTotalSum (y, h, totalSum, precision)
void exactTotalSum(int length, float y[length][1], float h[length][1], float totalSum, float precision, float X[length]) {

	// y and h are vectors, totalSum and precision are scalars
	//X is the return vector and length is the length of y, h, and X
	float totalSumMinus = totalSum - precision;
	float curAlpha;

	//get the minimum of vector h
	float min = h[0][0];
	for (int i=1; i < length; i++)
		min = (min < h[i][0])? min : h[i][0];

 	curAlpha = -min + EPS;

	//stepAlpha = max(10, abs(curAlpha/10));
	float stepAlpha, newAlpha, newSum;
	if(10 > fabs(curAlpha/10))
		stepAlpha = 10;
	else
		stepAlpha = fabs(curAlpha/10);

	for(int j=0; j < 50; j++) {
		newAlpha = curAlpha + stepAlpha;
		newSum = 0;

		//x = y ./ (h + newAlpha);
		for(int k=0; k < length; k++) {
			X[k] = y[k][0] / (h[k][0] + newAlpha);
			//newSum = sum(x);
			newSum += X[k];
		}

		if(newSum > totalSum) {
			curAlpha = newAlpha;
		} else {
			if (newSum < totalSumMinus)
				stepAlpha = stepAlpha / 2;
			else return;
		}
	
	} //end of for j

} //end of function



void unconstrainedP(int size1, int size2, float Y[size1][size2], float H[size1][size2], float X[size1][size2], float eps){
	//function X = unconstrainedP (Y, H)
	for(int i=0; i<size1; i++) {
		for(int j=0; j<size2; j++) {
			//X = Y ./ H;
			X[i][j] = Y[i][j] / H[i][j];

			//X(find(X < eps)) = eps;
			if(X[i][j] < eps) {
				X[i][j] = eps;
			}

		} // end of for j
	} // end of for i
} // end of function



//function X = maxColSumP (Y, H, maxColSum, precision)
void maxColSumP(int dim1, int dim2, float Y[dim1][dim2], float H[dim1][dim2], float maxColSum[dim1][1], float precision, float X[dim1][dim2]) {
	//X = unconstrainedP (Y, H);
	unconstrainedP(dim1, dim2, Y, H, X, precision);
	
	//Xsum = sum(X);
	float Xsum[dim1][1];
	for(int i=0; i < dim1; i++){
		for(int j=0; j < dim2; j++){
			Xsum[i][0] += X[j][i];
		} 
	}


	float yCol[dim2][1], hCol[dim2][1], Xcol[dim2];
	float dim = dim1*dim2;	


//for i = find(Xsum > maxColSum)
	for(int i=0; i < dim1; i++){
		if(Xsum[i][0] > maxColSum[i][0]){

//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);
			getCol(dim1, dim2, Y, yCol, i);
			getCol(dim1, dim2, H, hCol, i);

			exactTotalSum(dim1, yCol, hCol, maxColSum[i][0], precision, Xcol);
			
			for(int j=0; j < dim1; j++){
				X[j][i] = Xcol[j];
			}
		}
	}
} // end of function


void nearestDSmax_RE(int m, int n, float Y[m][n], float maxRowSum[m][1], float maxColSum[n][1], float totalSum, float precision, float maxLoops, float F[m][n]){
//m and n are the dimensions of Y

/*
 *   lambda1 = zeros(size(Y));
 *   lambda2 = lambda1;
 *   lambda3 = lambda1;
 */
	float lambda1[m][n];
	float lambda2[m][n];
	float lambda3[m][n];
	zeros(m, n, lambda1);
	zeros(m, n, lambda2);
	zeros(m, n, lambda3);

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

			Ysum += Y[i][j];

		}
	}

	for(int i=0; i < m; i++){
		for(int j=0; j < n; j++){

			F1[i][j] = totalSum * (Y[i][j] / Ysum);
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
		matPlusScaler(m, n, F3, EPS, F3eps);
		float YdivF3eps[m][n]; 
		matDiv(m, n, Y, F3eps, YdivF3eps);
		matSub( m, n, lambda1, YdivF3eps, H1);
		
		// F1 = maxColSumP (Y', -H1', maxRowSum', precision)';
		float negH1[m][n]; 
		matTimesScaler(m, n, H1, -1, negH1);
		float Yt[n][m];
		transpose(m, n, Y, Yt);
		float maxRowSumT[m][1];
		transpose( m, 1, maxRowSum, maxRowSumT);
		maxColSumP(n, m, Yt, negH1, maxRowSumT, precision, F1);

		// lambda1 = lambda1 - (Y ./ (F3+eps)) + (Y ./ (F1+eps));
		float F1eps[m][n];
		matPlusScaler( m, n, F1, EPS, F3eps);
		float YdivF1eps[m][n]; 
		matDiv(m, n, Y, F1eps, YdivF1eps);
		matSub(m, n, lambda1, YdivF3eps, lambda1);
		matAdd(m, n, lambda1, YdivF1eps, lambda1);

// Max col sum 
		// H2 = lambda2 - (Y ./ (F1+eps));
		matPlusScaler( m, n, F1, EPS, F1eps);
		matDiv(m, n, Y, F1eps, YdivF1eps);
		matSub(m, n, lambda2, YdivF1eps, H2);
		
		// F2 = maxColSumP (Y, -H2, maxColSum, precision);
		float negH2[m][n];
		matTimesScaler( m, n, H2, -1, negH2);
		maxColSumP(n, m, Y, negH2, maxColSum, precision, F2);

		// lambda2 = lambda2 - (Y ./ (F1+eps)) + (Y ./ (F2+eps));
		float F2eps[m][n];
		matPlusScaler( m, n, F2, EPS, F2eps);
		float YdivF2eps[m][n]; 
		matDiv(m, n, Y, F2eps, YdivF2eps);
		matSub(m, n, lambda2, YdivF1eps, lambda2);
		matAdd(m, n, lambda2, YdivF2eps, lambda2);

// Total sum
		// H3 = lambda3 - (Y ./ (F2 + eps));
		matSub(m, n, lambda3, YdivF1eps, H3);

		// F3 = reshape( exactTotalSum (Y(:), -H3(:), totalSum, precision), size(Y));
		float X[m*n];


		float negH3[m*n][1];
		float Yv[m*n][1];


		for(int i=0; i<n; i++){ 
			for(int j=0; j < m; j++){
				Yv[n*i + j][0] = Y[j][i];
				negH3[n*i + j][0] = -H3[j][i];
			}
		}

		exactTotalSum(m*n, Yv, negH3, totalSum, precision, X);

		float Xp[m*n][1];
		for(int i=0; i<n; i++){
			for(int j=0; j < m; j++){
				Xp[n*i +j][0] = X[n*i + j];
			}
		}

		reshape(m*n, 1, Xp, m, n, F3);

		//lambda3 = lambda3 - (Y ./ (F2+eps)) + (Y ./ (F3+eps));
		matSub(m, n, lambda3, YdivF2eps, lambda3);
		matAdd(m, n, lambda3, YdivF3eps, lambda3);


//if (max(abs(F1(:) - F2(:))) < precision && max(abs(F1(:) - F3(:))) < precision)
		float Fdiff1[m*n][1], Fdiff2[m*n][1];
		for(int i=0; i < m; i++){
			for(int j=0; j < n; j++){
				Fdiff1[i*n + j][0] = abs(F1[i][j] - F2[i][j]);
				Fdiff2[i*n + j][0] = abs(F1[i][j] - F3[i][j]);
			}
		}
		float fdMax1 = maxOfArray(m*n, Fdiff1);
		float fdMax2 = maxOfArray(m*n, Fdiff2);
		if(fdMax1 < precision && fdMax2 < precision){
			break;
		}

	} // end of t for loop

		// F = (F1 + F2 + F3) / 3;
		matAdd(m, n, F1, F2, F);
		matAdd(m, n, F, F3, F);
		float Fdiv[m][n];
		ones(m, n, Fdiv);
		matTimesScaler(m, n, Fdiv, 3, Fdiv);
		matDiv(m, n, F, Fdiv, F);
		 
} //end of function

