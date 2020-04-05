#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  
  char token='L';
  char tokenn='R';
  MPI_Send(&token, 1, MPI_BYTE, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
  
