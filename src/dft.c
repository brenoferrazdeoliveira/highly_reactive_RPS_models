//criado em      :2018/05/02
//ult. atualizção:2018/05/02
//a utor         :breno <breno@dfi.uem.br>
//notas          :faz a transformada de fourier discreta
//compilação     :gcc dft.c -lm
//execução       :./a.out nome_do_arquivo_de_dados.dat n_de_linhas

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

int main(int argc, char **argv){
	if(argc != 3){
		printf("%s nome_do_arquivo_de_dados.dat n_de_linhas\n", argv[0]);
		exit(1);
	}
	
	int t, f, n;
	double         *g_t_1, *g_t_2, *g_t_3, *g_t_0;
	double complex *g_f_1, *g_f_2, *g_f_3, *g_f_0;
	FILE *arquivo;

	arquivo= fopen(argv[1], "r"); 
	n = atoi(argv[2]);
	g_t_1= (double         *) calloc(n,   sizeof(double        ));
	g_f_1= (double complex *) calloc(n/2, sizeof(double complex));
	g_t_2= (double         *) calloc(n,   sizeof(double        ));
	g_f_2= (double complex *) calloc(n/2, sizeof(double complex));
	g_t_3= (double         *) calloc(n,   sizeof(double        ));
	g_f_3= (double complex *) calloc(n/2, sizeof(double complex));
	g_t_0= (double         *) calloc(n,   sizeof(double        ));
	g_f_0= (double complex *) calloc(n/2, sizeof(double complex));
//	for(t= 0; t< n; t++){
//		if(fscanf(arquivo, "%lf %lf %lf %lf", &g_t_1[t], &g_t_2[t], &g_t_3[t], &g_t_0[t]) != 4){
//			printf("não foi possível ler o arquivo\n");
//			exit(1);
//		}
//	}
	for(t= 0; t< n; t++){
		if(fscanf(arquivo, "%lf %lf %lf %lf", &g_t_1[t], &g_t_2[t], &g_t_3[t], &g_t_0[t]) != 4){
			printf("não foi possível ler o arquivo\n");
			exit(1);
		}
	}
	fclose(arquivo);

	for(f= 0; f< n/2; f++){
		for(t= 0; t< n; t++){
			g_f_1[f]+= g_t_1[t]*cexp(-2.0*M_PI*I*f*t/n);
			g_f_2[f]+= g_t_2[t]*cexp(-2.0*M_PI*I*f*t/n);
			g_f_3[f]+= g_t_3[t]*cexp(-2.0*M_PI*I*f*t/n);
			g_f_0[f]+= g_t_0[t]*cexp(-2.0*M_PI*I*f*t/n);
		}
		g_f_1[f]*= 2.0/n;
		g_f_2[f]*= 2.0/n;
		g_f_3[f]*= 2.0/n;
		g_f_0[f]*= 2.0/n;
	}
	g_f_1[0]*= 0.5;
	g_f_2[0]*= 0.5;
	g_f_3[0]*= 0.5;
	g_f_0[0]*= 0.5;

	arquivo= fopen("dft.dat", "w");
	for(f= 0; f< n/2; f++){
		fprintf(arquivo, "%e %e %e %e\n", cabs(g_f_1[f]*g_f_1[f]), cabs(g_f_2[f]*g_f_2[f]), cabs(g_f_3[f]*g_f_3[f]), cabs(g_f_0[f]*g_f_0[f]));
	}
	fclose(arquivo);

	free(g_t_1); free(g_t_2); free(g_t_3); free(g_t_0);
	free(g_f_1); free(g_f_2); free(g_f_3); free(g_f_0);
	return 0;
}
