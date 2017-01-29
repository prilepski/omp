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

double pi_threaded_atomic() {
  double start_time = omp_get_wtime();
  static long num_steps = 100000;

  double pi = 0, num_threads = 0.0;

  double step = 1.0 / (double) num_steps;
  
  omp_set_num_threads(NUM_THREADS);

  #pragma omp parallel
  {
    int thread_id = omp_get_thread_num();
    int total_threads = omp_get_num_threads();

    double x, sum = 0;
    for (double i = thread_id; i < num_steps; i += total_threads){
      x = (i + 0.5) * step;
      sum += 4.0 / (1.0 + x * x);
    }

  #pragma omp critical
    pi += sum * step;
  }


  std::cout << "Threaded Atomic PI: " << pi << std::endl;
  std::cout << "Threaded Atomic PI Time: " << omp_get_wtime() - start_time << std::endl;  
}

// CAlculating PI in parallel with schedule
double pi_for() {
  double start_time = omp_get_wtime();
  static long num_steps = 100000;
  double step;

  double x, pi, sum = 0.0;

  step = 1.0 / (double) num_steps;

  #pragma omp parallel for schedule(auto) reduction(+:sum)
    for (long i = 0; i < num_steps; i++){
      x = (i + 0.5) * step;
      sum += 4.0 / (1.0 + x * x);
    }

  pi = step * sum;

  std::cout << "Parallel For PI: " << pi << std::endl;
  std::cout << "Parallel For Time: " << omp_get_wtime() - start_time << std::endl;  
}


int main(int argc, char **argv) {

  pi_sequencial();
  pi_threaded();
  pi_threaded_atomic();
  pi_for();
/*
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    
    std::cout << "Hello " << ID << std::endl;
    std::cout << "World " << ID << std::endl;
  }*/
    return 0;
}
