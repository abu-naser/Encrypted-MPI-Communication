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
  char local_char[5] = {'x','x','x','x','x'};
  char local_array[4] = {'x','x','x','x'};
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  
  /*if (world_rank == 0)
    local_char = 'a';
  else if (world_rank == 1)
    local_char = 'B';
   MPI_Alltoall(&local_char, 1, MPI_CHAR, local_array, 1, MPI_CHAR, MPI_COMM_WORLD); 
   printf("Rank %d received local_array[0]=%c  local_array[1]=%c\n",world_rank, local_array[0], local_array[1]);
  fflush(stdout);
  MPI_Barrier(MPI_COMM_WORLD);*/
  
   init_crypto();
  printf("Try encrypted part............");fflush(stdout);
  local_array[0]='x';
  local_array[1]='x';
  local_array[2]='x';
  if (world_rank == 0){
    local_char[0] = 'c';
    local_char[1] = 'd';
  }
  else if (world_rank == 1){
    local_char[0] = 'E';
    local_char[1] = 'F';
  }
  

  printf("Rank %d will send %c %c\n",world_rank, local_char[0], local_char[1]);fflush(stdout);
  MPI_Alltoall(local_char, 1, MPI_CHAR, local_array, 1, MPI_CHAR, MPI_COMM_WORLD); 
  printf("Rank %d received local_array[0]=%c  local_array[1]=%c\n",world_rank, local_array[0], local_array[1]);
  fflush(stdout);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}
