#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
        int rank;
        int buf[100];
        const int root=0;
        int i;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
       
        for(i=0;i<20;i++)
            buf[i]=rank;

        printf("[%d]: Before Bcast, %d %d %d %d %d %d %d %d %d %d\n", rank, 
                buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9]);
        
       
        MPI_Barrier(MPI_COMM_WORLD);

        if(rank == root) {
           for(i=0;i<5;i++)
            buf[i]= -11;

            for(i=5;i<10;i++)
                buf[i]= 21;
        }

        

        init_boringssl_128_siv();  
        /* everyone calls bcast, data is taken from root and ends up in everyone's buf */
        MPI_SEC_Bcast(buf, 10, MPI_INT, root, MPI_COMM_WORLD);

         printf("[%d]: After Bcast, %d %d %d %d %d %d %d %d %d %d\n", rank, 
                buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9]);

        MPI_Finalize();
        return 0;
}