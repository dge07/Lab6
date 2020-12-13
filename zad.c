    #include "mpi.h"
	#include <stdio.h>
	#include <math.h>
	

	
	
	double leibniz( double );
	double leibniz( double a )
	{
	    return (4.0 / (1.0 + a*a));
	}
	
	int main( int argc, char *argv[])
	{
	    int done = 0, n, myid, numer_procesu, i;
	    double wartosc_PI = 3.141592653589793238462643;
        double mypi, pi, h, sum, x;
	
	    MPI_Init(&argc,&argv);
	    MPI_Comm_size(MPI_COMM_WORLD,&numer_procesu);
	    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	
	    n = 0;
	    while (!done)
	    {
		    if (n==0) n=1024*numer_procesu; else n=0;
	
		    
	        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	        if (n == 0) done = 1;
	        else
	        {
	            sum = 0.0;
	        	for(i = myid ; i < n; i += numer_procesu) 
				{ 
	                sum += pow((-1),i)*(4.0 / (2*i+1)); 
	            } 
	            mypi = sum;
	
	            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	            if (myid == 0)
		    	{
	                printf("Wartosc liczby PI= %.16f, Blad obliczen= %.16f\n",pi, fabs(pi - wartosc_PI));
					
		    	}
	        }
	    }
	    MPI_Finalize();
	    return 0;
	}
