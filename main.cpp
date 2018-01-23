#include <iostream>
#include "tests.h"


int main()
{
    std::cout << "*****BINARY SEMAPHORE: TEST 1 - SUM 1+2+...+10 FROM DIFFERENT THREADS*****" << std::endl;
    bin_sem_test1(10);
    std::cout << "\n\n\n\n\n" << std::endl;
    std::cout << "*****BINARY SEMAPHORE: TEST 2 - SETTLERS SIMULATION*****" << std::endl;
    bin_sem_test2(10, 5, 100, 1000, 50);
    std::cout << "\n\n\n\n\n";
    extern const int thr_allowed;
    std::cout << "*****COUNTING SEMAPHORE TEST - SUM 1+2+...+100 FROM DIFFERENT THREADS ON "
              << cst::thr_allowed << " FIELDS*****" << std::endl;
    count_sem_test1(100);
    std::cout << "\n\n\n\n\n";
}
