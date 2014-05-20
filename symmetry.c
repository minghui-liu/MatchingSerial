boolean symmetry(double *G, int size){

	for(int i=0; i < size; i++){
		for(int j=0; j < size; j++){
			diff = *(G1 + sizeof(float)*i*size + sizeof(float)*j) - *(G1 + sizeof(float)*j*size + sizeof(float)*i);
			if(diff != 0){
				return false;
			}
		}
	}
	return true;
}
