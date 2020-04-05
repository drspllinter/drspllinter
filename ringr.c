// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Example using MPI_Send and MPI_Recv to pass a message around in a ring.
//
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

  
  if (world_rank==0) {
    char tokenn='R';
    MPI_Send(&tokenn, 2, MPI_BYTE, world_size - 1, 0, MPI_COMM_WORLD); 
  }
  if (world_rank != world_size-1) {
    MPI_Recv(&tokenn, 2, MPI_BYTE, world_rank + 1, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received token %c from process %d\n", world_rank, tokenn,
           world_rank + 1);    
  } else{
    MPI_Recv(&tokenn, 2, MPI_BYTE, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    printf("Process %d received token %c from process %d\n", world_rank, tokenn,
           0);     
  }
  if (world_rank !=0){
    MPI_Send(&tokenn, 2, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD);
  }  

  MPI_Finalize();
}
