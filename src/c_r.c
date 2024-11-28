#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <gsl/gsl_statistics.h>

int main(int argc, char **argv){
	int i, j, l, Nx, Ny;
	int *nor;
	double *phi, *c_r, *s_k;
	FILE *file;
	char name[100];

	if(argc != 4){
		printf("%s datafile.dat Nx Ny\n", argv[0]);
		exit(1);
	}

	Nx= atoi(argv[2]);
	Ny= atoi(argv[3]);

	nor= (int    *) calloc(2*Nx,  sizeof(int   ));
	phi= (double *) calloc(Nx*Ny, sizeof(double));
	c_r= (double *) calloc(2*Nx,  sizeof(double));
	s_k= (double *) calloc(2*Nx,  sizeof(double));

	fftw_complex *inp= (fftw_complex *) fftw_malloc(sizeof(fftw_complex)*(Nx*Ny));
	fftw_complex *out= (fftw_complex *) fftw_malloc(sizeof(fftw_complex)*(Nx*Ny));

	sprintf(name, "%s", argv[1]);
	if(!(file= fopen(name, "r"))){
		printf("cannot open file %s\n", argv[1]);
		exit(0);
	}
	for(j= 0; j< Ny; j++){
		for(i= 0; i< Nx; i++){
			if((fscanf(file, "%lf", &phi[j*Nx+i]) != 1)){
				printf("cannot read file %s\n", argv[1]);
				exit(0);
			}
		}
	}
	fclose(file);
			
	double mu= gsl_stats_mean(phi, 1, Nx*Ny);
	double sd= gsl_stats_sd(phi, 1, Nx*Ny);
	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			phi[i*Ny+j]-= mu;	
			inp[i*Ny+j]= phi[i*Ny+j] + 0.0*I;
		}
	}

	fftw_plan FTF= fftw_plan_dft_2d(Nx, Ny, inp, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(FTF);

	double SUM= 0.0;
	for(i= 0; i< (Nx*Ny); i++){
		out[i]= out[i]*conj(out[i]);
		SUM+= out[i];
	}

	fftw_plan FTB= fftw_plan_dft_2d(Nx, Ny, out, inp, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(FTB);

	for(i= 0; i< Nx; i++){
		for(j= 0; j< Ny; j++){
			l= i+j;
			c_r[l]+= creal(inp[i*Ny+j])/(Nx*Ny*sd*sd*Nx*Ny);
			s_k[l]+= creal(out[i*Ny+j])/SUM;
			nor[l]++;
		}
	}

	for(l= 1; l< (2*Nx); l++){
		c_r[l]/= nor[l];
		s_k[l]/= nor[l];
	}
	
	sprintf(name, "c_r.dat");
	if(!(file= fopen(name, "w"))){
		printf("cannot open file c_r.dat\n");
		exit(0);
	}
	for(l= 0; l< (2*Nx-1); l++){
		fprintf(file, "%e\n", c_r[l]);
	}
	fclose(file);

	sprintf(name, "s_k.dat");
	if(!(file= fopen(name, "w"))){
		printf("cannot open file s_k.dat\n");
		exit(0);
	}
	for(l= 0; l< (2*Nx-1); l++){
		fprintf(file, "%e\n", s_k[l]);
	}
	fclose(file);

	free(phi);
	free(c_r);
	free(s_k);
	free(nor);
	fftw_destroy_plan(FTF);
	fftw_destroy_plan(FTB);
	fftw_free(inp);
	fftw_free(out);
	fftw_cleanup();
	return 0;
}
