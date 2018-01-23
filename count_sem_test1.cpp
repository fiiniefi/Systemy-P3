#include "tests.h"
#include "pthr.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>

namespace cst
{
    void *routine(void *threadid);
    std::pair<int, bool> sum[thr_allowed];
    Countsem sem(thr_allowed);
}

void *cst::routine(void *threadid)
{
    cst::sem.wait();
    for (int i = 0; i < cst::thr_allowed; i++)
        if (cst::sum[i].second == true)
        {
            cst::sum[i].second = false;
            cst::sum[i].first += (int)threadid;
            usleep(1);
            cst::sum[i].second = true;
            cst::sem.wake_up();
            pthread_exit(NULL);
        }
    cst::sem.wake_up();
    std::cout << "Countsem error" << std::endl;
    pthread_exit(NULL);
}

void count_sem_test1(int tnumb)
{
    std::fill_n(cst::sum, cst::thr_allowed, std::make_pair(0, true));
    pthread_t threads[tnumb];
    for (int i = 0; i < tnumb ; i++)
        pthread_create(&threads[i], NULL, cst::routine, (void *)(i+1));
    for (int i = 0 ; i < tnumb ; i++)
        pthread_join(threads[i], NULL);
    int sum = 0;
    for (int i = 0 ; i < cst::thr_allowed ; i++)
    {
        std::cout << "Field number " << i << " is equal to: " << cst::sum[i].first << std::endl;
        sum += cst::sum[i].first;
    }
    std::cout << "Sum of natural integers from 0 to " << tnumb << " is equal to " << sum << std::endl;
}

