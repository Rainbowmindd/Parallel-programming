#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <unistd.h>

#include <string.h>

#include "mpi.h"

//komunikaty: rank i hostname

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;

  //inicjalizacja MPI
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); //ranga procesu (jego ID)
  MPI_Comm_size( MPI_COMM_WORLD, &size );// liczba procesow
  
  const int string_size=256;
  char host_name[string_size];

  memset(host_name,0,sizeof(host_name)); //zeruje cala tablice hostname

  gethostname(host_name,sizeof(host_name));

//komunikacja miedzy procesami 
  if(size>1){
    
    if( rank != 0 ){ 
      //wysylanie swojej nazwy do procesu 0
      dest=0; 
      tag=0; 
      
      MPI_Send( &rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
      MPI_Send(host_name,string_size,MPI_CHAR,0,0,MPI_COMM_WORLD);
      printf("Rank %d: Send host_name: %s to rank 0.\n",rank,host_name);
      
    } else {

      //odbieranie wiadomosoci przez proces 0 
      
      for( i=1; i<size; i++ ) { 
        char name_sent[string_size];
        
        memset(name_sent,0,sizeof(name_sent));
        
	      MPI_Recv( &ranksent, 1, MPI_INT,i, 
		    MPI_ANY_TAG, MPI_COMM_WORLD, &status );
        MPI_Recv(name_sent,string_size,MPI_CHAR,i,MPI_ANY_TAG,MPI_COMM_WORLD,&status);

       name_sent[string_size - 1] = '\0';


	    printf("Dane od procesu o randze (status.MPI_SOURCE ->) %d: %d, %s  (i=%d)\n", 
	       status.MPI_SOURCE, ranksent, name_sent,i );
      }
      
    }

  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  //zakonczenie programu
  MPI_Finalize(); 
  
  return(0);

}

