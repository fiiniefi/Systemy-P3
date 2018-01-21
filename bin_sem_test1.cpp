#include "tests.h"
#include "pthr.h"
#include <iostream>
#include <pthread.h>

void *routine(void *threadid);
int sum;
Binsem sem;

void *routine(void *threadid)
{
    sem.wait();
    sum += (int)threadid;
    sem.wake_up();
    pthread_exit(NULL);
}

void bin_sem_test1(int tnumb)
{
    pthread_t threads[tnumb];
    for (int i = 0; i < tnumb ; i++)
        pthread_create(&threads[i], NULL, routine, (void *)i);
    for (int i = 0 ; i < tnumb ; i++)
        pthread_join(threads[i], NULL);
    std::cout << "Sum of natural integers from 0 to " << tnumb << " is equal to " << sum << std::endl;
}
