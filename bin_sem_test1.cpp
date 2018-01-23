#include "tests.h"
#include "pthr.h"
#include <iostream>
#include <pthread.h>

namespace bst
{
    void *routine(void *threadid);
    int sum;
    Binsem sem;
}

void *bst::routine(void *threadid)
{
    bst::sem.wait();
    bst::sum += (int)threadid;
    bst::sem.wake_up();
    pthread_exit(NULL);
}

void bin_sem_test1(int tnumb)
{
    pthread_t threads[tnumb];
    for (int i = 0; i < tnumb ; i++)
        pthread_create(&threads[i], NULL, bst::routine, (void *)(i+1));
    for (int i = 0 ; i < tnumb ; i++)
        pthread_join(threads[i], NULL);
    std::cout << "Sum of natural integers from 0 to " << tnumb << " is equal to " << bst::sum << std::endl;
}
