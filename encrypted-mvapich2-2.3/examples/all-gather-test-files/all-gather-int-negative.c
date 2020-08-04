#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>



int main(int argc, char** argv) {


  MPI_Init(NULL, NULL);
    int i;
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  int local_int[300];
  int local_array[1000];
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  

  printf("Try encrypted part............\n");fflush(stdout);
   init_boringssl_128_siv();
  
    

  if(world_rank == 0){
      for(i=0;i<10;i++)
         local_int[i]=-9;
  }

  if(world_rank == 1){
      for(i=0;i<10;i++)
         local_int[i]=8;
  }

  if(world_rank == 2){
      for(i=0;i<10;i++)
         local_int[i]=-5;
  }
  if(world_rank == 3){
      for(i=0;i<10;i++)
         local_int[i]=-2;
  //local_int[9]='\0';
  }
  MPI_SEC_Allgather(local_int, 4, MPI_INT, local_array, 4, MPI_INT, MPI_COMM_WORLD);
  printf("Rank %d received %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
  world_rank, local_array[0], local_array[1], local_array[2], local_array[3], local_array[4], local_array[5], local_array[6], local_array[7],
  local_array[8], local_array[9], local_array[10], local_array[11], local_array[12], local_array[13], local_array[14], local_array[15]); fflush(stdout);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
