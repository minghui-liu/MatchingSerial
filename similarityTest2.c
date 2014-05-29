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
void rotate(int size, float G1[size][2], float G2[size][2], float centerX, float centerY){

	float theta = randomfloatAngle();
	for(int i=0; i < size; i++){
		G2[i][0] = ((float)cos((double)theta))*(G1[i][0] - centerX) - ((float)sin((double)theta))*(G1[i][1] - centerY) + centerX;
		G2[i][1] = ((float)sin((double)theta))*(G1[i][0] - centerX) + ((float)cos((double)theta))*(G1[i][1] - centerY) + centerY;
	}
} //end of function

void translate(int size, float G1[size][2], float G2[size][2], float centerX, float centerY){

	float distortionX;
	float distortionY;
	distortionX = randomfloat();
	distortionY = randomfloat();
	for(int i=0; i < size; i++){
		G2[i][0] = distortionX + G1[i][0];
		G2[i][1] = distortionY + G1[i][1];
	}

} //end of function

void graphDistortion(int size, float G1[size][2], float G2[size][2], float centerX, float centerY){

	rotate(size, G1, G2, centerX, centerY);
	translate(size, G2, G2, centerX, centerY);

} //end of function

void printMatrix( int size1, int size2, float matrix[size1][size2]) {
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
void neighborDistances(int size, float G1[size][2], float neighbors[size][size], float adjacency[size][size]){

	float distance = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(i == j)
				neighbors[i][j] = -INFINITY;
			else if (adjacency[i][j] == 1){
				distance = sqrt((G1[i][0] - G1[j][0])*(G1[i][0] - G1[j][0]) + (G1[i][1] - G1[j][1])*(G1[i][1] - G1[j][1]));
				neighbors[i][j] = distance;
			}
			else
				neighbors[i][j] = -INFINITY;
		}
	}

}

//similarity function
void similarity(int size, int size2, int edges, float neighbors1[size][size], float neighbors2[size][size], float similarity[size2][size2]){

	float simScore = 0;
	int j = 0;
	int i = 0;

	for(int k = 1; k < size; k++){
		for(int l = 0; l < k; l++){
			for(int m = 1; m < size; m++){
				for(int n = 0; n < m; n++){
					if(neighbors1[k][l] == -INFINITY || neighbors2[m][n] == -INFINITY)
						similarity[i][j] = 0;
					else
						similarity[i][j] = exp(-(fabs(neighbors1[k][l] - neighbors2[m][n])));
					j = (j+1) % size2;
				}
			}
			i = (i+1);
		}
	}

}

/* make Y an all zero matrix
 * size1 and size2 are the size of Y
 */
void zeros(int size1, int size2, float Y[size1][size2]){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			//*(Y + (i*size2 + j) ) = 0;
			Y[i][j] = 0;
		}
	}
}

void makeAdjacency(int size, float adjacent[size][size], int edges){

	float temp;
	float p = 1 / (((((float)size * (float)size)/2) - ((float)size/2)) / (float)edges);
	printf("probability = %f\n", p);
	int edgeCount = 0;
//the adjacency matrix will be symmetric therefore its only neccessary to 
//loop through half of the elements

//we assume there are no loops in this graph
	while(edgeCount != edges){

		for(int i = 1; i < size; i++){
			for(int j = 0; j < i; j++){

				temp = fabs(randomfloat());
				printf("temp is %f\n", temp);

				if(temp < p){
					if(adjacent[i][j] != 1){

						adjacent[i][j] = 1;
						adjacent[j][i] = 1;
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

	srand(time(0));

//create random set of points
	int size = 5;
	float G1[size][2];
	for(int i=0; i < size; i++){
		G1[i][0] = randomfloat();
		G1[i][1] = randomfloat();
	}
	printMatrix(size, 2, G1);

//create adjacency matrix to determine where edges exist
	float adjacent[size][size];
	zeros(size, size, adjacent);
	int edges = 6;
	makeAdjacency(size, adjacent, edges);

	printf("Adjacency Matrix\n");
	printMatrix(size, size, adjacent);


//copy original set of points for distortion
	float G2[size][2];
	for(int i=0; i < size; i++){
		G2[i][0] = G1[i][0];
		G2[i][1] = G1[i][1];
	}

//distort the graph for testing purposes
	graphDistortion(size, G1, G2, 0, 0);
	printMatrix(size, 2, G2);

//calculate the distances to each neighbor
	float neighborDist1[size][size], neighborDist2[size][size];
	neighborDistances(size, G1, neighborDist1, adjacent);
	neighborDistances(size, G2, neighborDist2, adjacent);
	
	printf("neighbor Distances 1\n");
	printMatrix(size, size, neighborDist1);

	printf("neighbor distances 2\n");
	printMatrix(size, size, neighborDist2);

	int size2;
	size2 = (size*size)/2 - (size/2);


	float simMatrix[size2][size2];
	zeros(size2, size2, simMatrix);

//check to see if the graphs are the same
	similarity(size, size2, edges, neighborDist1, neighborDist2, simMatrix);
	printf("Similarity Scores\n");
	printMatrix(size2, size2, simMatrix);



}
