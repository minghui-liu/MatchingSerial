void transpose(double *trans, int size1, int size2){

	double trans2[size1][size2];

	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			trans[j][i] = *(trans + sizeof(double)*i*size1 + sizeof(double)*j);
		}
	}
}
