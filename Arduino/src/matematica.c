#include <time.h>
#include <stdlib.h>
#include "matrix.h"
#include "matematica.h"


int fatorial(int x){
    if ( x == 1 || x == 0){
        return 1;
    } else {
        return x*fatorial(x-1);        
    }
}

matrix* linspace(double x1, double x2, int n){

	/* Variáveis auxiliares */
	matrix *e = new_matrix(n, 1);
	double dE = (x2 - x1)/(n-1);

	/* Recorrência */
	int cont = 0;
	for (double i = x1 ; cont < n ; i+=dE){
		set(i, e, cont, 0);
		cont++; 
	}
	return e;
}