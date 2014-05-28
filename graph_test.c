#include <stdio.h>
#include <math.h>
#include "graphMatching.c"
#include "utils.c"

void main() {
	float G1[3][3] = {{0,4,3},{4,0,5},{3,5,0}};
	float G2[3][3] = {{0,3.8,2.9},{3.8,0,5.1},{2.9,5.1,0}};
	printf("G1:\n");
	printMatrix(3, 3, G1);
	printf("G2:\n");
	printMatrix(3, 3, G2);

	float X[3][3];
	float Z[3][3];
	float Y[3][3];

	graphMatching(3, G1, 3, G2, 1, 3, X, Z, Y);

	printf("X(hard):\n");
	printMatrix(3, 3, X);
	printf("Z(soft):\n");
	printMatrix(3, 3, Z);
	printf("Y(debug):\n");
	printMatrix(3, 3, Y);
}
