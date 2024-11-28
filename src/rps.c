#include "../rps.h"

void ic(const gsl_rng *, int *);     /* initial conditions      */
void op(int , int *);                /* data output             */

int main(int argc, char **argv){
	if(argc != 2){
		printf("type: %s seed\n", argv[0]);
		exit(1);
	}
	int g, i, j, t, ac, ps, tp, gd, nb;
	int *phi, *dst;
	double at, n_m, n_p, n_r;
//	PROBABILITY_OF_PREDATION
	char name[100];
	FILE *file;

	phi= (int *) calloc(Nx*Ny, sizeof(int));
	dst= (int *) calloc((NS+1), sizeof(int));

	gsl_rng_default_seed= atoi(argv[1]);
	gsl_rng *w= gsl_rng_alloc(gsl_rng_taus);

	ic(w, phi);
	for(i= 0; i < Nx*Ny; i++){
		dst[phi[i]]++;
	}

	n_m= n_p= n_r= 0.0;
	for(t= 1; t <= NG; t++){
		gd= 0;
		while(gd < Nx*Ny){
			do{
				i= gsl_rng_uniform(w)*Nx;
				j= gsl_rng_uniform(w)*Ny;
				ac= j*Nx+i;
			}while(phi[ac] == 0);
			nb= gsl_rng_uniform(w)*4;
			switch(nb){
				case 0:
					ps= j*Nx+((i+1)%Nx);
				break;
				case 1:
					ps= j*Nx+((i-1+Nx)%Nx);
				break;
				case 2:
					ps= ((j+1)%Ny)*Nx+i;
				break;
				default:
					ps= ((j-1+Ny)%Ny)*Nx+i;
			}
			at= gsl_rng_uniform(w);
			if(at < pm){
				tp= phi[ps];
				phi[ps]= phi[ac];
				phi[ac]= tp;
				gd++; n_m++;
			}else{
				if(at < (pm + pp)){
					switch(phi[ac]){
						case 1:
							g= 0;
							if(phi[j*Nx+((i+1)%Nx)] == 2){
								 phi[j*Nx+((i+1)%Nx)]= 0;
								g++;
							}
							if(phi[j*Nx+((i-1+Nx)%Nx)] == 2){
								 phi[j*Nx+((i-1+Nx)%Nx)]= 0;
								g++;
							}
							if(phi[((j+1)%Ny)*Nx+i] == 2){
								 phi[((j+1)%Ny)*Nx+i]= 0;
								g++;
							}
							if(phi[((j-1+Ny)%Ny)*Nx+i] == 2){
								 phi[((j-1+Ny)%Ny)*Nx+i]= 0;
								g++;
							}
							if(g > 0){
								gd++; n_p++;
							}
						break;
						case 2:
							g= 0;
							if(phi[j*Nx+((i+1)%Nx)] == 3){
								 phi[j*Nx+((i+1)%Nx)]= 0;
								g++;
							}
							if(phi[j*Nx+((i-1+Nx)%Nx)] == 3){
								 phi[j*Nx+((i-1+Nx)%Nx)]= 0;
								g++;
							}
							if(phi[((j+1)%Ny)*Nx+i] == 3){
								 phi[((j+1)%Ny)*Nx+i]= 0;
								g++;
							}
							if(phi[((j-1+Ny)%Ny)*Nx+i] == 3){
								 phi[((j-1+Ny)%Ny)*Nx+i]= 0;
								g++;
							}
							if(g > 0){
								gd++; n_p++;
							}
						break;
						case 3:
							g= 0;
							if(phi[j*Nx+((i+1)%Nx)] == 1){
								 phi[j*Nx+((i+1)%Nx)]= 0;
								g++;
							}
							if(phi[j*Nx+((i-1+Nx)%Nx)] == 1){
								 phi[j*Nx+((i-1+Nx)%Nx)]= 0;
								g++;
							}
							if(phi[((j+1)%Ny)*Nx+i] == 1){
								 phi[((j+1)%Ny)*Nx+i]= 0;
								g++;
							}
							if(phi[((j-1+Ny)%Ny)*Nx+i] == 1){
								 phi[((j-1+Ny)%Ny)*Nx+i]= 0;
								g++;
							}
							if(g > 0){
								gd++; n_p++;
							}
						break;
					}
				}else{
					if(phi[ps] == 0){
						phi[ps]= phi[ac];
						gd++; n_r++;
					}
				}
			}
		}
		if(t > 1000){
			for(i= 0; i < (NS+1); i++){
				dst[i]= 0;
			}
			for(i= 0; i < Nx*Ny; i++){
				dst[phi[i]]++;
			}
			sprintf(name, "dat/dst-%d.dat", atoi(argv[1]));
			file= fopen(name, "a");
			for(i= 1; i < (NS+1); i++){
				fprintf(file, "%e ", (double)dst[i]/(Nx*Ny));
			}
			fprintf(file, "%e\n", (double)dst[0]/(Nx*Ny));
			fclose(file);
		}
	}
	op(atoi(argv[1]), phi);
	file= fopen("dat/mpr.dat", "a");
	fprintf(file, "%e %e %e", n_m/(n_m+n_p+n_r), n_p/(n_m+n_p+n_r), n_r/(n_m+n_p+n_r));
	fclose(file);

	gsl_rng_free(w);
	free(phi);
	free(dst);
	return 0;
}
