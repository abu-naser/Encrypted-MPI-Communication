#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>



int main(int argc, char** argv) {


  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  float local_int[300];
  float local_array[1000];
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  

  printf("Try encrypted part............\n");fflush(stdout);
   init_boringssl_128_siv();
  
    int i;

  if(world_rank == 0){
       for(i=0;i<4;i++)
         local_int[i]=-9.0;
      for(i=4;i<8;i++)
         local_int[i]=-8.0;
      for(i=8;i<12;i++)
         local_int[i]=-7.0;
      for(i=12;i<16;i++)
         local_int[i]=-6.345;  
  }

  if(world_rank == 1){
       for(i=0;i<4;i++)
         local_int[i]=-10.0;
      for(i=4;i<8;i++)
         local_int[i]=-11.0;
      for(i=8;i<12;i++)
         local_int[i]=-12.98;
      for(i=12;i<16;i++)
         local_int[i]=-13.90;  
  }

  if(world_rank == 2){
       for(i=0;i<4;i++)
         local_int[i]=-9.02;
      for(i=4;i<8;i++)
         local_int[i]=-8.98;
      for(i=8;i<12;i++)
         local_int[i]=-7.09;
      for(i=12;i<16;i++)
         local_int[i]=-6.23;  
  }
  if(world_rank == 3){
      for(i=0;i<4;i++)
         local_int[i]=40.0;
      for(i=4;i<8;i++)
         local_int[i]=50.0;
      for(i=8;i<12;i++)
         local_int[i]=51.0;
      for(i=12;i<16;i++)
         local_int[i]=52.0;  
  //local_int[9]='\0';
  }
  MPI_SEC_Alltoall(local_int, 4, MPI_FLOAT, local_array, 4, MPI_FLOAT, MPI_COMM_WORLD);
  printf("Rank %d received %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
  world_rank, local_array[0], local_array[1], local_array[2], local_array[3], local_array[4], local_array[5], local_array[6], local_array[7],
  local_array[8], local_array[9], local_array[10], local_array[11], local_array[12], local_array[13], local_array[14], local_array[15]); fflush(stdout);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
