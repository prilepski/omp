#include <iostream>
#include <omp.h>

int main(int argc, char **argv) {
    
  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    
    std::cout << "Hello " << ID << std::endl;
    std::cout << "World " << ID << std::endl;
  }
    return 0;
}
