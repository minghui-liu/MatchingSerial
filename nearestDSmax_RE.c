#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "utils.c"

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

void nearestDSmax_RE(float* Y, int m, int n, float* maxRowSum, float* maxColSum, float totalSum, float precision, float maxLoops, float* F){
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
		float YdivF3eps[m][n]; 
		matDiv(Y, F3eps, YdivF3eps, m, n)
		matSub(lambda1, YdivF3eps, H1, m, n);
		
		// F1 = maxColSumP (Y', -H1', maxRowSum', precision)';
		float negH1[m][n]; 
		matTimesScaler(H1, -1, negH1, m, n);
		float Yt[n][m]
		transpose(Y, Yt, m, n);
		float maxRowSumT[1][m];
		transpose(maxRowSum, maxRowSumT, m, 1);
		maxColSumP(Yt, n, m, negH1, maxRowSumT, precision, F1);

		// lambda1 = lambda1 - (Y ./ (F3+eps)) + (Y ./ (F1+eps));
		float F1eps[m][n];
		matPlusScaler(F1, eps, F3eps, m, n);
		float YdivF1eps[m][n]; 
		matDiv(Y, F1eps, YdivF1eps, m, n);
		matSub(lambda1, YdivF3eps, lambda1, m, n);
		matAdd(lambda1, YdivF1eps, lambda1, m, n);

// Max col sum 
		// H2 = lambda2 - (Y ./ (F1+eps));
		float F1eps[m][n];
		matPlusScaler(F1, eps, F1eps, m, n);
		float YdivF1eps[m][n]; 
		matDiv(Y, F1eps, YdivF1eps, m, n)
		matSub(lambda2, YdivF1eps, H2, m, n);
		
		// F2 = maxColSumP (Y, -H2, maxColSum, precision);
		float negH2[m][n];
		matTimesScaler(H2, -1, negH2, m, n);
		maxColSumP(Y, n, m, negH2, maxColSum, precision, F2);

		// lambda2 = lambda2 - (Y ./ (F1+eps)) + (Y ./ (F2+eps));
		float F2eps[m][n];
		matPlusScaler(F2, eps, F2eps, m, n);
		float YdivF2eps[m][n]; 
		matDiv(Y, F2eps, YdivF2eps, m, n);
		matSub(lambda2, YdivF1eps, lambda2, m, n);
		matAdd(lambda2, YdivF2eps, lambda2, m, n);

// Total sum
		// H3 = lambda3 - (Y ./ (F2 + eps));
		matSub(lambda3, YdivF1eps, H3, m, n);

		// F3 = reshape( exactTotalSum (Y(:), -H3(:), totalSum, precision), size(Y));
		float X[m*n];
		exactTotalSum(Y, negH3, totalSum, precision, X, m*n);
		reshape(X, Y, F3);

		//lambda3 = lambda3 - (Y ./ (F2+eps)) + (Y ./ (F3+eps));
		matSub(lambda3, YdivF2eps, lambda3, m, n);
		matAdd(lambda3, YdivF3eps, lambda3, m, n);


//if (max(abs(F1(:) - F2(:))) < precision && max(abs(F1(:) - F3(:))) < precision)
		float Fdiff1[m*n], Fdiff2[m*n];
		for(int i=0; i < m; i++){
			for(int j=0; j < n; j++){
				Fdiff1[i*n + j] = abs(F1[i][j] - F2[i][j]);
				Fdiff2[i*n + j] = abs(F1[i][j] - F3[i][j]);
			}
		}
		fdMax1 = maxOfArray(Fdiff1, m*n);
		fdMax2 = maxOfArray(Fdiff2, m*n);
		if( fdMax1 < precision && fdMax2 < precision ){
			break;
		}

	} // end of t for loop

		// F = (F1 + F2 + F3) / 3;
		matAdd(F1, F2, F, m, n);
		matAdd(F, F3, F, m, n);
		ones(Fdiv, m, n);
		matTimesScaler(Fdiv, 3, Fdiv, m, n);
		matDiv(F, Fdiv, F, m, n);
		 
} //end of function


//function X = maxColSumP (Y, H, maxColSum, precision)
void maxColSumP(float* Y, int Ydim1, int Ydim2, float* H, float* maxColSum, float precision, float* X){


	//X = unconstrainedP (Y, H);
	unconstrainedP(Y, H, X, Ydim1, Ydim2, precision);

	//Xsum = sum(X);
	for(int i=0; i < Ydim1; i++){
		for(int j=0; j < Ydim2; j++){

			Xsum += *(X + i*Ydim2 + j);

		} 
	}


//for i = find(Xsum > maxColSum)
	for(int i=0; i<n; i++){
		if(Xsum > *(maxColSum + i)){

//X(:,i) = exactTotalSum (Y(:,i), H(:,i), maxColSum(i), precision);			
			exactTotalSum(Y, H, i, *(maxColSum + i), precision, X, n);

		}
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
} // end of function



//function x = exactTotalSum (y, h, totalSum, precision)
void exactTotalSum(float* y, float* h, float totalSum, float precision, float* X, int length) {
// y and h are vectors, totalSum and precision are scalars
//X is the return vector and length is the length of y, h, and X

	float totalSumMinus = totalSum - precision;
	
	float curAlpha;

//get the minimum of vector h
	float min = *(h);
	for (int i=1; i < length; i++) {
		min = (min < *(h+i))? min : *(h+i);
	}

 	curAlpha = -min + precision;

//stepAlpha = max(10, abs(curAlpha/10));
	float stepAlpha, newAlpha, newSum;
	if(10 > abs(curAlpha/10)){
		stepAlpha = 10;
	} else{
		stepAlpha = abs(curAlpha/10);
	}

	for(int j=0; j < 50; j++){

		newAlpha = curAlpha + stepAlpha;

		newSum = 0;

//x = y ./ (h + newAlpha);
		for(int k=0; k < length; k++){
			*(X + k) = *(y + k) / (*(h + k) + newAlpha);
//newSum = sum(x);
			newSum += *(X + k);
		}

		if(newSum > totalSum){
			curAlpha = newAlpha;
		}else{
			if (newSum < totalSumMinus){
				stepAlpha = stepAlpha / 2;
			}else{
				return;
			}
		}
	}

} //end of function

