//
//  main.cpp
//  OpenMP
//
//  Created by Benjamin Häfele on 13.08.13.
//  Copyright (c) 2013 Benjamin Häfele. All rights reserved.
//

#include <iostream>
#include <omp.h>

int serialFib(int n) {
  if (n < 2) return n;
  int x = serialFib(n - 1);
  int y = serialFib(n - 2);
  return x+y;
};

int fib(int n) {
  if (n < 2) return n;
  if (n <= 30) return serialFib(n);
  
  int x, y;
#pragma omp task shared(x)
  {
    x = fib(n-1);
  }
#pragma omp task shared(y)
  {
    y = fib(n-2);
  }
#pragma omp taskwait
  {
    return x+y;
  }
};


int main(int argc, const char * argv[]) {
  
  double t1, duration;
  
  omp_set_num_threads(4);

  std::cout << "Start calculation:\n";
  t1 = omp_get_wtime();
  int sol = fib(40);
  std::cout << "The solution is: " << sol << "\n";
  duration = (omp_get_wtime() - t1);
  std::cout << "The calculation time is: " << duration << "\n";
  
  return 0;
}

