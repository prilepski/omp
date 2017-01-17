#include <iostream>
#include <omp.h>

#define NUM_THREADS 4 // MAx number of threads

// CAlculating PI squencially
double pi_sequencial() {
  double start_time = omp_get_wtime();
  static long num_steps = 100000;
  double step;

  double x, pi, sum = 0.0;

  step = 1.0 / (double) num_steps;

  for (double i = 0; i < num_steps; i++){
    x = (i + 0.5) * step;
    sum += 4.0 / (1.0 + x * x);
  }

  pi = step * sum;

  std::cout << "Sequencial PI: " << pi << std::endl;
  std::cout << "Sequencial PI Time: " << omp_get_wtime() - start_time << std::endl;  
}

double pi_threaded() {
  double start_time = omp_get_wtime();
  static long num_steps = 100000;

  double step;

  double x, pi = 0, num_threads = 0.0;
  double sum[NUM_THREADS];

  step = 1.0 / (double) num_steps;
  
  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int total_threads = omp_get_num_threads();
    if (!thread_id)
      num_threads = total_threads;

    double x;
    sum[thread_id] = 0.0;
    for (double i = thread_id; i < num_steps; i += total_threads){
      x = (i + 0.5) * step;
      sum[thread_id] += 4.0 / (1.0 + x * x);
    }
  }

  for (int i = 0; i < num_threads; i++) 
    pi += sum[i];

  pi *= step;

  std::cout << "Threaded PI: " << pi << std::endl;
  std::cout << "Threaded PI Time: " << omp_get_wtime() - start_time << std::endl;  
}

int main(int argc, char **argv) {

  pi_sequencial();
  pi_threaded();
/*
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    
    std::cout << "Hello " << ID << std::endl;
    std::cout << "World " << ID << std::endl;
  }*/
    return 0;
}
