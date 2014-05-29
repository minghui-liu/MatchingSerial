/*
* file: RandomTest.c
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
#define TEST_SIZE 5


//function returns a random float value in the interval [0, 2PI]
float randomfloatAngle(){
  //generate random float between 0 and 1
  float r = (float)rand()/(float)RAND_MAX;
  //scale to the 0 to 2PI range
  r *= (2*PI);
  return r;
} //end of function

//function returns a random float value in the interval [0,1]
float randomfloat(){
  //generate random float between 0 and 1
  float r = (float)rand()/(float)RAND_MAX;
  
  if(rand()%2 == 0)
    return r;
  else
    return -r;
} //end of function

//function takes in a set of points, rotates them and then returns the new set
void rotate(int size, float V1[size][2], float V2[size][2], float centerX, float centerY){
  float theta = randomfloatAngle();
  for(int i=0; i < size; i++){
    V2[i][0] = cos(theta)*(V1[i][0] - centerX) - sin(theta)*(V1[i][1] - centerY) + centerX;
    V2[i][1] = sin(theta)*(V1[i][0] - centerX) + cos(theta)*(V1[i][1] - centerY) + centerY;
  }
} //end of function

void pointDistort(int size, float V1[size][2], float V2[size][2], float centerX, float centerY){
  float distortionX;
  float distortionY;
  for(int i=0; i < size; i++){
    distortionX = randomfloat()/10;
    distortionY = randomfloat()/10;
    V2[i][0] = distortionX + V1[i][0];
    V2[i][1] = distortionY + V1[i][1];
  }
} //end of function

void graphDistortion(int size, float V1[size][2], float V2[size][2], float centerX, float centerY) {
  rotate(size, V1, V2, centerX, centerY);
  pointDistort(size, V2, V2, centerX, centerY);
} //end of function


//create a matrix of distances between nodes
void neighborDistances(int size, float V1[size][2], float neighbors[size][size]){

  float distance = 0;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      if(i == j)
        neighbors[i][j] = 0;
      else {
        distance = sqrt((V1[i][0] - V1[j][0])*(V1[i][0] - V1[j][0]) + (V1[i][1] - V1[j][1])*(V1[i][1] - V1[j][1]));
        neighbors[i][j] = distance;
      }
    }
  }

}

//similarity function
void similarity(int size, int edges, float neighbors1[size][size], float neighbors2[size][size], float similarity[edges][edges]){
  float simScore = 0;
  int j = 0;
  int i = 0;
  
  for(int k = 1; k < size; k++) {
    for(int l = 0; l < k; l++) {
      for(int m = 1; m < size; m++) {
        for(int n = 0; n < m; n++) {
          similarity[i][j] = exp(-(fabs(neighbors1[k][l] - neighbors2[m][n])));
          j = (j+1) % edges;
        }
      }
      i = (i+1);
    }
  }

} // end oof function

void main(){
  int size = TEST_SIZE;
  float V1[size][2], V2[size][2];
  for(int i=0; i < size; i++){
    V2[i][0] = V1[i][0] = V1[i][0] = randomfloat();
    V2[i][1] = V1[i][1] = V1[i][1] = randomfloat();
  }
  printMatrix(size, 2, V1);

  graphDistortion(size, V1, V2, 0, 0);
  printMatrix(size, 2, V2);
  float neighborDist1[size][size], neighborDist2[size][size];
  neighborDistances(size, V1, neighborDist1);
  neighborDistances(size, V2, neighborDist2);
  
  printf("neighbor Distances 1\n");
  printMatrix(size, size, neighborDist1);
  
  printf("neighbor distances 2\n");
  printMatrix(size, size, neighborDist2);
  
  int size2;
  size2 = (size*size)/2 - (size/2);
  
  
  float simMatrix[size2][size2];
  zeros(size2, size2, simMatrix);
  
  similarity(size, size2, neighborDist1, neighborDist2, simMatrix);
  printf("Similarity Scores\n");
  printMatrix(size2, size2, simMatrix);
  
  float X[size][size];
  float Z[size][size];
  float Y[size][size];
  graphMatching(size,neighborDist1,size,neighborDist2,1,size,X,Z,Y);
  
  printf("X(hard):\n");
  printMatrix(size, size, X);
  printf("Z(soft):\n");
  printMatrix(size, size, Z);
  printf("Y(debug):\n");
  printMatrix(size, size, Y);
 
}
