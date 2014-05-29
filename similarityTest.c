/*
 * file: similarityTest.c
 *
 * Testing the probablistic graph matching algorithm 
 * by rotating a set of artificial points and then calculating
 * the similarity score for the edges
 *
 * Kevin Liu & Reid Delaney
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265

/*
double randomdouble();
double randomdoubleAngle();
void pointDistort(int size; double G1[][]; double G2[][]; double centerX; double centerY);
void rotate(int size; double G1[][]; double G2[][]; double centerX; double centerY); 
*/

//function returns a random double value in the interval [0, 2PI]
double randomdoubleAngle(){

	//generate random double between 0 and 1
	double r = (double)rand()/(double)RAND_MAX;

	//scale to the 0 to 2PI range
	r *= (2*PI);
	
	return r;
} //end of function

//function returns a random double value in the interval [0,1]
double randomdouble(){

	//generate random double between 0 and 1
	double r = (double)rand()/(double)RAND_MAX;

	if(rand()%2 == 0)
		return r;
	else
		return -r;
} //end of function

//function takes in a set of points, rotates them and then returns the new set
void rotate(int size, double G1[size][2], double G2[size][2], double centerX, double centerY){

	double theta = randomdoubleAngle();
	for(int i=0; i < size; i++){
		G2[i][0] = cos(theta)*(G1[i][0] - centerX) - sin(theta)*(G1[i][1] - centerY) + centerX;
		G2[i][1] = sin(theta)*(G1[i][0] - centerX) + cos(theta)*(G1[i][1] - centerY) + centerY;
	}
} //end of function

void pointDistort(int size, double G1[size][2], double G2[size][2], double centerX, double centerY){

	double distortionX;
	double distortionY;
	for(int i=0; i < size; i++){
		distortionX = randomdouble();
		distortionY = randomdouble();
		G2[i][0] = distortionX + G1[i][0];
		G2[i][1] = distortionY + G1[i][1];
	}

} //end of function

void graphDistortion(int size, double G1[size][2], double G2[size][2], double centerX, double centerY){

	rotate(size, G1, G2, centerX, centerY);
	//pointDistort(size, G2, G2, centerX, centerY);

} //end of function

void printMatrix( int size1, int size2, double matrix[size1][size2]) {
	for (int i=0; i<size1; i++){
		for(int j=0; j<size2; j++) {
			//printf("%.2f ", *(matrix + i*size2 + j));
			printf("%6.2f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
} //end of function

//create a matrix of distances between nodes
void neighborDistances(int size, double G1[size][2], double neighbors[size][size]){

	double distance = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i == j)
				neighbors[i][j] = 0;
			else {
				distance = sqrt((G1[i][0] - G1[j][0])*(G1[i][0] - G1[j][0]) + (G1[i][1] - G1[j][1])*(G1[i][1] - G1[j][1]));
				neighbors[i][j] = distance;
			}
		}
	}

}

//similarity function
void similarity(int size, int edges, double neighbors1[size][size], double neighbors2[size][size], double similarity[edges][edges]){

	double simScore = 0;
	int j = 0;
	int i = 0;

	for(int k = 1; k < size; k++){
		for(int l = 0; l < k; l++){
			for(int m = 1; m < size; m++){
				for(int n = 0; n < m; n++){
						similarity[i][j] = exp(-(fabs(neighbors1[k][l] - neighbors2[m][n])));
						j = (j+1) % edges;
				}
			}
			i = (i+1);
		}
	}

}

/* make Y an all zero matrix
 * size1 and size2 are the size of Y
 */
void zeros(int size1, int size2, double Y[size1][size2]){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			//*(Y + (i*size2 + j) ) = 0;
			Y[i][j] = 0;
		}
	}
}

void main(){
	int size = 5;
	double G1[size][2];
	for(int i=0; i < size; i++){
		G1[i][0] = randomdouble();
		G1[i][1] = randomdouble();
	}
	printMatrix(size, 2, G1);
	double G2[size][2];
	for(int i=0; i < size; i++){
		G2[i][0] = G1[i][0];
		G2[i][1] = G1[i][1];
	}
	graphDistortion(size, G1, G2, 0, 0);
	printMatrix(size, 2, G2);
	double neighborDist1[size][size], neighborDist2[size][size];
	neighborDistances(size, G1, neighborDist1);
	neighborDistances(size, G2, neighborDist2);
	
	printf("neighbor Distances 1\n");
	printMatrix(size, size, neighborDist1);

	printf("neighbor distances 2\n");
	printMatrix(size, size, neighborDist2);

	int size2;
	if(size % 2 == 0)
		size2 = (size*size)/2 - (size/2);
	else
		size2 = (size*size)/2 - (size/2);

	double simMatrix[size2][size2];
	zeros(size2, size2, simMatrix);

	similarity(size, size2, neighborDist1, neighborDist2, simMatrix);
	printf("Similarity Scores\n");
	printMatrix(size2, size2, simMatrix);

}
