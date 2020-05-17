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
  
  double M[4][4] = {
	{9, 0, -27, 18},
	{0, 9, -9, -27},
	{-27, -9, 99, -27},
	{18, -27, -27, 121}
};
  
  if(world_rank == 0){
    for (int i = 0; i <= 3; i++){
		  for (int j = 0; j <= 3; j++){
			  cout << M[i][j] << " ";
		  }
		  cout << endl;
	  }     
  }
  else if (world_rank == world_size - 1){
   MPI_Send(&token, 1, MPI_BYTE, 0, 0, MPI_COMM_WORLD); 
   MPI_Send(&tokenn, 2, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD); 
   MPI_Recv(&token, 1, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   printf("Process %d received token %c from process %d\n", world_rank, token, world_rank - 1);
   MPI_Recv(&tokenn, 2, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   printf("Process %d received token %c from process %d\n", world_rank, tokenn, 0);  
  }  
  else {
   MPI_Send(&token, 1, MPI_BYTE, world_rank + 1, 0, MPI_COMM_WORLD); 
   MPI_Send(&tokenn, 2, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD);  
   MPI_Recv(&token, 1, MPI_BYTE, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   printf("Process %d received token %c from process %d\n", world_rank, token, world_rank - 1);
   MPI_Recv(&tokenn, 2, MPI_BYTE, world_rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   printf("Process %d received token %c from process %d\n", world_rank, tokenn, world_rank + 1);     
  }  
  MPI_Finalize();
}  
