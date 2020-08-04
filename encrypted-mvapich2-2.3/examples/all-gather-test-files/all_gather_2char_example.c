#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
//#include <assert.h>



int main(int argc, char** argv) {

  int status =0;
  status=MPI_Init(NULL, NULL);

  int world_rank;
  status=MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  char local_char [20] = {'x'};
  char local_array[24] = {'x','x','x','x'};
  status=MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  
  if (world_rank == 0)
    local_char[0] = 'a';
  else if (world_rank == 1)
    local_char[0] = 'B';
  

  //printf("rank %d will send %x %c\n",world_rank, local_char[0], local_char[0]);fflush(stdout);

  
 //MPI_Allgather(local_char, 1, MPI_CHAR, local_array, 1, MPI_CHAR, MPI_COMM_WORLD); 

 // printf("rank %d received %c %c\n",world_rank, local_array[0], local_array[1]);
  //fflush(stdout);
  init_crypto();
  printf(">Try encrypted part............\n");//fflush(stdout);
  local_array[0]='x';
  local_array[1]='x';
  local_array[2]='x';
  if (world_rank == 0)
    local_char[0] = 'c';
  else if (world_rank == 1)
    local_char[0] = 'D';
  

  printf("#Rank %d will send %c\n",world_rank, local_char[0]);//fflush(stdout);
  int var=MPI_SEC_Allgather(local_char, 1, MPI_CHAR, local_array, 1, MPI_CHAR, MPI_COMM_WORLD); 
  printf("Rank %d received   local_array[0]=%c  local_array[1]=%c\n",world_rank, local_array[0], local_array[1]);
  printf("done calling status=%d\n",var);
  //fflush(stdout);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}
