#include "../rps.h"

void op(int NI, int *phi){
	int i, j;
	char name[100];
	sprintf(name, "dat/phi-%d.dat", NI);
	FILE *file= fopen(name,  "w");

	for(j= 0; j< Ny; j++){
		for(i= 0; i< Nx; i++){
			fprintf(file, "%d ", phi[j*Nx+i]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}
