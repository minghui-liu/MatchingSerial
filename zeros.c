void zeros(double *Y, int size1, int size2){
	for(int i=0; i<size1; i++){
		for(int j=0; j<size2; j++){
			*(Y + (i*size1*sizeof(int) + (j*sizeof(int)*size2))) = 0;
		}
	}
}
