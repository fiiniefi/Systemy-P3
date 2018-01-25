#include <iostream>
#include <unistd.h>
#include "pthr.h"

void hello(int thread_number)
{
    std::cout << "Thread number: " << thread_number << std::endl;
    std::cout.flush();
}


/*void threads_test()
{
    const int length = 101;
    ucontext_t *threads[length];
    for (int i = 0; i < length; i++)
        threads[i] = create(&hello, 0, {});
    for (int i = 0; i < length; i++)
        schedule();
    for (int i = 0; i < length; i++)
        join(threads[i]);
    std::cout << "Main thread." << std::endl;
    std::cout.flush();
}*/
