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
#include "graphMatching.c"
#include "utils.c"

#define PI 3.14159265
#define TEST_SIZE 500

//function returns a random float value in the interval [-1,1]
float randomfloat(){

	//generate random float between 0 and 1
	float r = (float)rand()/(float)RAND_MAX;

	if(rand()%2 == 0)
		return r;
	else
		return -r;
} //end of function

//function returns a random float value in the interval [0, 2PI]
float randomfloatAngle(){

	//generate random float between 0 and 1
	float r = fabs(randomfloat());

	//scale to the 0 to 2PI range
	r *= (2*PI);
	
	return r;
} //end of function

//function takes in a set of points, rotates them and then returns the new set
void rotate(int size, float* G1, float* G2, float centerX, float centerY){

	float theta = randomfloatAngle();
	for(int i=0; i < size; i++){
		*(G2 + i*2) = ((float)cos((double)theta))*(*(G1 + i*2) - centerX) - ((float)sin((double)theta))*(*(G1 + i*2 + 1) - centerY) + centerX;
		*(G2 + i*2 + 1) = ((float)sin((double)theta))*(*(G1 + i*2) - centerX) + ((float)cos((double)theta))*(*(G1 + i*2 + 1) - centerY) + centerY;
	}
} //end of function

void translate(int size, float* G1, float *G2, float centerX, float centerY){

	float distortionX;
	float distortionY;
	distortionX = randomfloat();
	distortionY = randomfloat();
	for(int i=0; i < size; i++){
		*(G2 + i*2) = distortionX + *(G1 + i*2);
		*(G2 + i*2 + 1) = distortionY + *(G1 + i*2 + 1);
	}

} //end of function

void graphDistortion(int size, float* G1, float* G2, float centerX, float centerY){

	rotate(size, G1, G2, centerX, centerY);
	translate(size, G2, G2, centerX, centerY);

} //end of function

//create a matrix of distances between nodes
void neighborDistances(int size, float* G1, float* neighbors, float *adjacency){

	float distance = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i == j)
				//neighbors[i][j] = -INFINITY;
				*(neighbors + i*size + j) = 0;
			else if (*(adjacency + i*size + j) == 1){
				distance = sqrt((*(G1 + i*2) - *(G1 + j*2))*(*(G1 + i*2) - *(G1 + j*2)) + 
						(*(G1 + i*2 + 1) - *(G1 + j*2 + 1))*(*(G1 + i*2 + 1) - *(G1 + j*2 + 1)));
				*(neighbors + i*size + j) = distance;
			}
			else
				//neighbors[i][j] = -INFINITY;
				*(neighbors + i*size + j) = 0;
		}
	}

}

//similarity function
void similarity(int size, int size2, int edges, float *neighbors1, float *neighbors2, float* similarity){

	float simScore = 0;
	int j = 0;
	int i = 0;

	for(int k = 1; k < size; k++){
		for(int l = 0; l < k; l++){
			for(int m = 1; m < size; m++){
				for(int n = 0; n < m; n++){
					if(*(neighbors1 + k*size + l) == 0 || *(neighbors2 + m*size + n) == 0)
						*(similarity + i*size2 + j) = 0;
					else
						*(similarity + i*size2 + j) = exp(-(fabs(*(neighbors1 + k*size + l) - *(neighbors2 + m*size + n))));
					j = (j+1) % size2;
				}
			}
			i = (i+1);
		}
	}

}


void makeAdjacency(int size, float* adjacent, int edges){

	float temp;
	float p = (float)edges / ((((float)size * (float)size)/2) - ((float)size/2));

//	printf("probability = %f\n", p);
	int edgeCount = 0;

//the adjacency matrix will be symmetric therefore its only neccessary to 
//loop through half of the elements

//we assume there are no loops in this graph
	while(edgeCount != edges){

		for(int i = 1; i < size; i++){
			for(int j = 0; j < i; j++){

				temp = fabs(randomfloat());

				if(temp < p){
					if(*(adjacent + i*size + j) != 1){

						*(adjacent + i*size + j) = 1;
						*(adjacent + j*size + i) = 1;
						edgeCount++;
						if(edgeCount == edges)
							return;

					} //adjacent...
				} //temp<p

			} // j
		} // i

	} //while loop

} //end of function

void main(){

	clock_t start = clock(), diff;

	srand(time(0));

//create random set of points
	int size = TEST_SIZE;
	float* G1 = (float *)malloc(size*2*sizeof(float));
	for(int i=0; i < size; i++){
		*(G1 + i*2) = randomfloat();
		*(G1 + i*2 + 1) = randomfloat();
	}
//	printMatrix(size, 2, G1);

//create adjacency matrix to determine where edges exist
	float* adjacent = (float *)malloc(size*size*sizeof(float));
	zeros(size, size, adjacent);
	int edges = size + (size/2);
	makeAdjacency(size, adjacent, edges);

//	printf("Adjacency Matrix\n");
//	printMatrix(size, size, adjacent);


//copy original set of points for distortion
	float* G2 = (float *)malloc(size*2*sizeof(float));
	for(int i=0; i < size; i++){
		*(G2 + i*2) = *(G1 + i*2);
		*(G2 + i*2 + 1) = *(G1 + i*2 + 1);
	}

//distort the graph for testing purposes
	graphDistortion(size, G1, G2, 0, 0);
//	printMatrix(size, 2, G2);

//calculate the distances to each neighbor
	float *neighborDist1 = (float *) malloc(size*size*sizeof(float)); 
	float *neighborDist2 = (float *) malloc(size*size*sizeof(float));
	neighborDistances(size, G1, neighborDist1, adjacent);
	neighborDistances(size, G2, neighborDist2, adjacent);
//	printf("neighbor Distances 1\n");
//	printMatrix(size, size, neighborDist1);

//	printf("neighbor distances 2\n");
//	printMatrix(size, size, neighborDist2);

	int size2;
	size2 = (size*size)/2 - (size/2);

	//printf("size2 is : %d\n", size2);
//	float *simMatrix = malloc(size2*size2 * sizeof(float));
//	int **simPtrs = malloc(size2 * sizeof(int));
//	printf("created simMatrix\n");
//	zeros(size2, size2, simMatrix);

//check to see if the graphs are the same
//	similarity(size, size2, edges, neighborDist1, neighborDist2, simMatrix);
	//printf("Similarity Scores\n");
	//printMatrix(size2, size2, simMatrix);

//free up memory that was dynamically allocated
//	free(simMatrix);
	free(G1);
	free(G2);
	free(adjacent);
		
	float *X = (float *)malloc(size*size*sizeof(float));
	float *Z = (float *)malloc(size*size*sizeof(float));
	float *Y = (float *)malloc(size*size*sizeof(float));
	zeros(size, size, X);
	zeros(size, size, Z);
	zeros(size, size, Y);

	printf("Got to graph matching\n");
	graphMatching(size,neighborDist1,size,neighborDist2, 0.01,size,X,Z,Y);

	printf("Finished\n");

	free(neighborDist1);
	free(neighborDist2);
	  
/*	printf("X(hard):\n");
	printMatrix(size, size, X);
	printf("Z(soft):\n");
	printMatrix(size, size, Z);
	printf("Y(debug):\n");
	printMatrix(size, size, Y);
*/
	free(X);
	free(Z);
	free(Y);

	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

}
