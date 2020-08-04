#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#define MAX 1000
/*
This program tests MPI_Alltoallv by having processor i send different
amounts of data to each processor.
The first test sends i items to processor i from all processors.
*/
int main( int argc, char **argv )
{
    MPI_Comm comm;
    int *sbuf, *rbuf;
    int rank, size;
    int *sendcounts, *recvcounts, *rdispls, *sdispls;
    int i, j, *p, err;

    MPI_Init( &argc, &argv );
    err = 0;
    comm = MPI_COMM_WORLD;
    /* Create the buffer */
    MPI_Comm_size( comm, &size );
    MPI_Comm_rank( comm, &rank );
    sbuf = (int *)malloc( MAX * size * sizeof(int) );
    rbuf = (int *)malloc( MAX * size * sizeof(int) );
    if (!sbuf || !rbuf) {
        fprintf( stderr, "Could not allocated buffers!\n" );
        MPI_Abort( comm, 1 );
    }
    /* Load up the buffers */
    /*
    for (i=0; i<size*size; i++) {
        sbuf[i] = i + 100*rank;
        rbuf[i] = -i;
    }
    */
    for (i=0; i<MAX; i++) {
        sbuf[i] = 10*rank+1;
        rbuf[i] = 0;
    }

    /* Create and load the arguments to alltoallv */
    sendcounts = (int *)malloc( MAX * sizeof(int) );
    recvcounts = (int *)malloc( MAX * sizeof(int) );
    rdispls = (int *)malloc( MAX * sizeof(int) );
    sdispls = (int *)malloc( MAX * sizeof(int) );
    if (!sendcounts || !recvcounts || !rdispls || !sdispls) {
        fprintf( stderr, "Could not allocate arg items!\n" );fflush(stderr);
        MPI_Abort( comm, 1 );
    }
    /*
    for (i=0; i<size; i++) {
        sendcounts[i] = i;
        recvcounts[i] = rank;
        rdispls[i] = i * rank;
        sdispls[i] = (i * (i+1))/2;
    }
    */
    if(rank==0){
        sendcounts[0] = 1;
        sendcounts[1] = 2;
        sendcounts[2] = 3;
        sendcounts[3] = 4;

        sdispls[0] = 0;
        sdispls[1] = 1;
        sdispls[2] = 3;
        sdispls[3] = 6;

        recvcounts[0] = 1;
        recvcounts[1] = 1;
        recvcounts[2] = 1;
        recvcounts[3] = 1;

        rdispls[0] = 0;
        rdispls[1] = 1;
        rdispls[2] = 2;
        rdispls[3] = 3;

    }
    else if(rank==1){   
        sendcounts[0] = 1;
        sendcounts[1] = 2;
        sendcounts[2] = 3;
        sendcounts[3] = 4;

        sdispls[0] = 0;
        sdispls[1] = 1;
        sdispls[2] = 3;
        sdispls[3] = 6;

        recvcounts[0] = 2;
        recvcounts[1] = 2;
        recvcounts[2] = 2;
        recvcounts[3] = 2;

        rdispls[0] = 2;
        rdispls[1] = 0;
        rdispls[2] = 6;
        rdispls[3] = 4;
    }
    else if(rank==2){   
        sendcounts[0] = 1;
        sendcounts[1] = 2;
        sendcounts[2] = 3;
        sendcounts[3] = 4;

        sdispls[0] = 0;
        sdispls[1] = 1;
        sdispls[2] = 3;
        sdispls[3] = 6;

        recvcounts[0] = 3;
        recvcounts[1] = 3;
        recvcounts[2] = 3;
        recvcounts[3] = 3;

        rdispls[0] = 0;
        rdispls[1] = 3;
        rdispls[2] = 6;
        rdispls[3] = 9;
    }
    else if(rank==3){   
        sendcounts[0] = 1;
        sendcounts[1] = 2;
        sendcounts[2] = 3;
        sendcounts[3] = 4;

        sdispls[0] = 0;
        sdispls[1] = 1;
        sdispls[2] = 3;
        sdispls[3] = 6;

        recvcounts[0] = 4;
        recvcounts[1] = 4;
        recvcounts[2] = 4;
        recvcounts[3] = 4;

        rdispls[0] = 0;
        rdispls[1] = 4;
        rdispls[2] = 8;
        rdispls[3] = 12;
    }
    init_crypto();
    MPI_SEC_Alltoallv( sbuf, sendcounts, sdispls, MPI_INT, rbuf, recvcounts, rdispls, MPI_INT, comm );

    //MPI_Alltoallv( sbuf, sendcounts, sdispls, MPI_INT, rbuf, recvcounts, rdispls, MPI_INT, comm );
    /* Check rbuf */
    int total_recv =0;
    for(i=0; i<size; i++)
        total_recv+=recvcounts[i];
    if(rank==0)
        printf("rank =%d: %d %d %d %d\n",rank,rbuf[0],rbuf[1],rbuf[2],rbuf[3]); fflush(stdout);  
    if(rank==1)
        printf("rank =%d: %d %d %d %d %d %d %d %d\n",rank,rbuf[0],rbuf[1],rbuf[2],rbuf[3],
        rbuf[4],rbuf[5],rbuf[6],rbuf[7]); fflush(stdout); 
    if(rank==2)
     printf("rank =%d: %d %d %d %d %d %d %d %d %d %d %d %d\n",rank,rbuf[0],rbuf[1],rbuf[2],rbuf[3],
     rbuf[4],rbuf[5],rbuf[6],rbuf[7],rbuf[8],rbuf[9],rbuf[10],rbuf[11]); fflush(stdout);  
     if(rank==3)
     printf("rank =%d: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",rank,rbuf[0],rbuf[1],rbuf[2],rbuf[3],
      rbuf[4],rbuf[5],rbuf[6],rbuf[7],rbuf[8],rbuf[9],rbuf[10],rbuf[11],rbuf[12],rbuf[13],rbuf[14],rbuf[15]); fflush(stdout); 
   /* printf("rank =%d: ",rank); fflush(stdout);      
    for(i=0; i<total_recv; i++){
      printf("%d ", rbuf[i]); fflush(stdout);
    }
    printf("\n");fflush(stdout);
    */
    /*
    for (i=0; i<size; i++) {
        p = rbuf + rdispls[i];
        for (j=0; j<rank; j++) {
            if (p[j] != i * 100 + (rank*(rank+1))/2 + j) {
                fprintf( stderr, "[%d] got %d expected %d for %dth\n",
                                    rank, p[j],(i*(i+1))/2 + j, j );
                fflush(stderr);
                err++;
            }
            else{
                 fprintf( stdout, "[%d] got %d expected %d for %dth\n",
                                    rank, p[j],(i*(i+1))/2 + j, j );
                fflush(stdout);
            }
        }
    }
    */
    free( sdispls );
    free( rdispls );
    free( recvcounts );
    free( sendcounts );
    free( rbuf );
    free( sbuf );
    MPI_Finalize();
    return 0;
}