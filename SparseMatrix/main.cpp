//
//  main.cpp
//  SparseMatrix
//
//  Created by Benjamin Häfele on 14.08.13.
//  Copyright (c) 2013 Benjamin Häfele. All rights reserved.
//

#include <iostream>
#include <openmp.h>

void spmv(double* value, int* index, int* ptr, double* x, double* y, int n, int nnz) {
  for (int i = 0; i < n; i++) {
    y[i] = 0;
#pragma omp for private(i, j)
    for (int j = ptr[i]; j < ptr[i+1]; j++) {
      y[i] += value[j] * x[index[j]];
    }
  }
};


int main(int argc, const char * argv[])
{
  
  int ptr[6] = {0,2,4,7,11,13};
  int index[13] = {0,3,1,2,1,2,3,0,2,3,4,3,4};
  double value[13] = {1,2,1,3,2,1,4,1,3,1,5,5,1};
  int n = 5;
  int nnz = 13;
  double x[5] = {2,2,2,2,2};
  double y[5];
  
  spmv(value, index, ptr, x, y, n, nnz);
  
  for(int i = 0; i < n; i++) std::cout << y[i] << std::endl;
  
  return 0;
}

