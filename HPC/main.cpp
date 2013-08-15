//
//  main.cpp
//  HPC
//
//  Created by Benjamin Häfele on 11.08.13.
//  Copyright (c) 2013 Benjamin Häfele. All rights reserved.
//

#include <iostream>
#include <random>

#include "functions.hpp"

int main(int argc, const char * argv[])
{
  
  int i,j;
  int n = 10;
  
  std::random_device rd;
  
  double **Ap = new double *[n];
  for (i = 0; i < n; ++i)
  {
    Ap[i] = new double[n];
  }
  for (i = 0; i < n; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      Ap[i][j] = rd()/(rd.max()/10);
    }
  }
  
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      std::cout << Ap[i][j] << " ";
    }
    std::cout << "\n";
  }
  
  i = luDecomp(Ap, n);
  
  std::cout << "\n";
  std::cout << "Anzahl Multiplikationen: " << i;
  std::cout << "\n\n";
  
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      std::cout << Ap[i][j] << " ";
    }
    std::cout << "\n";
  }
  
 
  return 0;
  
}

