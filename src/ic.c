#include "../rps.h"

void ic(const gsl_rng *w, int *phi){
	int i;

//	for(i= 0; i< Nx*Ny; i++){
//		phi[i]= gsl_rng_uniform(w)*(NS+1);
//	}

	FILE *file;
		if(!(file= fopen("dat/phi-0.dat", "r"))){
			printf("cannot open file dat/phi-0.dat\n");
			exit(1);
		}
	for(i= 0; i< Nx*Ny; i++){
		if((fscanf(file, "%d", &phi[i]) != 1)){
			printf("cannot read file phi-0.dat\n");
			exit(1);
		}
	}

}
