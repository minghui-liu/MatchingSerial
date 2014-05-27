/*
 * file: rotate.c
 *
 * Testing the probablistic graph matching algorithm 
 * by rotating a set of artificial points
 *
 * Kevin Liu & Reid Delaney
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void main(){
	
}

//function takes in a set of points, rotates them and then returns the new set
void rotate(int size; coordinates G1[size][2]; coordinates G2[size][2]; float centerX; float centerY){

	float theta = randomFloat();
	G2[i][0] = cos(theta)*(G1[i][0] - centerX) - sin(theta)*(G1[i][1] - centerY) + centerX;
	G2[i][1] = sin(theta)*(G1[i][0] - centerX) + cos(theta)*(G1[i][1] - centerY) + centerY;

}

//function returns a random float value in the interval [0,360]
float randomFloat(){

	//generate random float between 0 and 1
	float r = (float)rand()/(float)RAND_MAX;

	//scale to the 0 to 360 range
	r *= 360;
	
	return r;
}
