#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#define Nx 500     /* grid size                      */
#define Ny 500     /* grid size                      */
#define NG 6000    /* number of generations          */
#define NS 3       /* number of types of species     */
/* pm + pr + pp = 1.0                                */
#define pm 0.5                    /* probability of motion          */
#define pr 0.5*(1.0-pm)           /* probability of reproduction    */
#define pp 0.5*(1.0-pm)           /* probability of predation       */

#define PROBABILITY_OF_PREDATION \
const int p[NS*NS]= {\
	0, 1, 0, \
	0, 0, 1, \
	1, 0, 0, \
};
