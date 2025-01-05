#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv){
    int rank,size;
    int liczba=0; //przekazywana wartosc w sztafecie
    int source,dest; //zrodlo i cel komunikatu

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    //Sprawdzenie liczby procesow
    if(size<2){
        printf("Przynajmniej 2 procesy do realizacji sztafety");
        MPI_Finalize();
        return 0;
    }

    if(rank==0){
        //proces o randze 0 inicjalizuje sztafete
        liczba=1; //wartosc startowa
        dest=rank+1 ;//wysylamy do procesu 1
        printf("Proces %d wyslal liczbe %d do procesu %d\n",rank,liczba,dest);
        MPI_Send(&liczba,1,MPI_INT,dest,0,MPI_COMM_WORLD);
    } else{
        source=rank-1;
        MPI_Recv(&liczba,1,MPI_INT,source,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Proces %d odebral liczbe %d od procesu %d\n",rank,liczba,source);

        liczba+=1;

        if(rank<size-1){
            dest=rank+1;
            printf("Proces %d wyslal liczbe %d do procesu %d\n",rank,liczba,dest);
            MPI_Send(&liczba,1,MPI_INT,dest,0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();

    return 0;

}