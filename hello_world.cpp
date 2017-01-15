#include <iostream>
#include <omp.h>

int main(int argc, char **argv) {
    
  #pragma omp parallel
  {
    int ID = 1;
    
    std::cout << "Hello " << ID << std::endl;
    std::cout << "World " << ID << std::endl;
  }
    return 0;
}
