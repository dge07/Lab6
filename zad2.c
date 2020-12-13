#include <stdio.h>
	#include <string.h>
	#include <math.h>
	#include "mpi.h"
	
	int a = 1;
	int b = 4;
	
	float funkcja(float x) 
	{ 
	
	    return x*x; 
	} 
	
	float calka(int nr, int max) 
	{ 
	    float a_2,b_2;
	
	    float odleglosc;
	
	    odleglosc = (b - a) / max;
	
	    b_2 = max - nr - odleglosc;
	
	    a_2 = b_2 - odleglosc;
	
	    float h = (b_2-a_2); 
	  
	    float s = funkcja(a_2)+funkcja(b_2); 
	    
	    s += 2*funkcja(a_2+h); 
	  
	    return((0.5)*s); 
	    
	} 
	
	
	
	int main(int argc, char **argv)
	{
	    int liczba_procesu,numer_procesu;
	    int tag=20;double suma;
	
	    suma=0;
	    MPI_Status status;
	    MPI_Init(&argc, &argv);
	    MPI_Comm_rank(MPI_COMM_WORLD, &numer_procesu);
	    MPI_Comm_size(MPI_COMM_WORLD, &liczba_procesu);
	    if (numer_procesu == liczba_procesu-1)
	    {
	        suma = calka(numer_procesu, liczba_procesu);
	        printf("\nPID: %d\n",numer_procesu); 
	        printf("Suma: %lf\n",suma);
	        //wysylamy zmienne do ostatniego procesu       
	        MPI_Send(&suma, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
	        }
	//warunek gdy proces ma numer wiekszy niz 0 i mniejszy niz ostatni proces
	if (numer_procesu>0 && numer_procesu<liczba_procesu-1){ 
	
	    MPI_Recv(&suma, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
	
	    suma += calka(numer_procesu, liczba_procesu);
	
	    printf("\nPID: %d\n",numer_procesu);
	    printf("Suma: %lf\n",suma);
	    //przesylamy tutaj zmienne do poprzedniego procesu
	    MPI_Send(&suma, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
	    }
	    if(numer_procesu == 0)
	    {
	        
	
	        MPI_Recv(&suma, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
	        suma = calka(numer_procesu, liczba_procesu);
	        printf("\nPID: %d\n",numer_procesu); 
	        printf("|SUMA|:  %lf\n",suma);
	    }
	        MPI_Finalize();
	return 0;
	}
