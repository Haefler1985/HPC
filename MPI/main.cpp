//
//  main.cpp
//  MPI
//
//  Created by Benjamin Häfele on 14.08.13.
//  Copyright (c) 2013 Benjamin Häfele. All rights reserved.
//

#define LEN 20

#include <iostream>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  
  int *local = (int*) malloc(sizeof(int)*LEN);
  int *result = (int*) malloc(sizeof(int)*LEN);
  int *tmpbuf = (int*) malloc(sizeof(int)*LEN);
  
  int i, rank, size, step, left, right;
  
  MPI_Status status, send_status;
  MPI_Request request;
  
  MPI_Init(&argc, &argv);
  
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if (rank==0) {
    for(i = 0; i < LEN; i++) result[i] = 1;
    for(i = 0; i < LEN; i++) std::cout << *(result+i) << " ";
    std::cout << std::endl;
  }
  
  right = (rank + 1) % size;
  left = (rank - 1 + size) % size;
  
  if(rank == 0) std::cout << std::endl << "Startup..." << std::endl;
  
  MPI_Barrier(MPI_COMM_WORLD);
  
  for (step = 0; step < size ; step++) {
    // Send our partial result to the next rank
    MPI_Isend(result, LEN, MPI_INT, right, 0, MPI_COMM_WORLD, &request);
    // Receive the result from the left rank
    MPI_Recv(tmpbuf, LEN, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
    /* Wait for the send to complete */
    MPI_Wait(&request, &send_status);
    /* Swap buffers */
    int *tmp = result;
    result = tmpbuf;
    tmpbuf = tmp;
    // Combine the local values with the partial result
    for (i = 0; i < LEN; i++) result[i] *= local[i];
    
    if (rank == 0) {
      std::cout << step << " ";
      for(i = 0; i < LEN; i++) std::cout << result[i] << " ";
      std::cout << std::endl;
    }
    
  }
  
  MPI_Finalize();
  return 0;
}
