#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "pthr.h"
//#include <thread>

int hunters_numb, cooks_numb, meat_numb, meal_numb;
Binsem meat;
Binsem meal;
void *hunter_routine(void *);
void *cook_routine(void *);
void consume(int &);


//int cooks_job, hunters_job; //debug

void *hunter_routine(void *)
{
//hunters_job++; //debug
    srand(time(NULL));
    int throw_hunter = std::rand() % 6;
    int throw_prey = std::rand() % 6;
    meat.wait();
    if (throw_hunter > throw_prey)
    {
        meat_numb++;
    }
    meal.wait();
    consume(hunters_numb);
    meal.wake_up();
    meat.wake_up();
    usleep(100);
    pthread_exit(NULL);
}


void *cook_routine(void *)
{
//cooks_job++; //debug
    meat.wait();
    if (meat_numb > 0)
    {
        meat_numb--;
        meal.wait();
        meal_numb += (std::rand() % 6);
    }
    consume(cooks_numb);
    meal.wake_up();
    meat.wake_up();
    usleep(100);
    pthread_exit(NULL);
}

void consume(int &villagers_numb)
{
    if (meal_numb > 0)
        meal_numb--;
    else if (villagers_numb > 0)
        villagers_numb--;
}


void bin_sem_test2(int hts, int cks, int mt, int ml, int days)
{
    hunters_numb = hts, cooks_numb = cks, meat_numb = mt, meal_numb = ml;

    pthread_t hunters[hunters_numb];
    pthread_t cooks[cooks_numb];

    for (int i = 1 ; i <= days ; i++)
    {
        for (int j = 0 ; j < cooks_numb ; j++)
        {
            int flag = pthread_create(&cooks[j], NULL, cook_routine, NULL);
            if (flag)
                std::cout<< "Error: Cook thread cannot be created" << std::endl;
        }

        for (int j = 0 ; j < hunters_numb ; j++)
        {
            int flag = pthread_create(&hunters[j], NULL, hunter_routine, NULL);
            if (flag)
                std::cout << "Error: Hunter thread cannot be created" << std::endl;
        }

        for (int j = 0 ; j < cooks_numb ; j++)
        {
            pthread_join(cooks[j], NULL);
        }

        for (int j = 0 ; j < hunters_numb ; j++)
        {
            pthread_join(hunters[j], NULL);
        }
        std::cout << "Number of hunters after " << i << " day(s): " << hunters_numb << std::endl;
        std::cout << "Number of cooks after " << i << " day(s): " << cooks_numb << std::endl;
        std::cout << "Number of meat after " << i << " day(s): " << meat_numb << std::endl;
        std::cout << "Number of meal after " << i << " day(s): " << meal_numb << std::endl;
//std::cout<<"Cooks job: "<<cooks_job<<std::endl; //debug
//std::cout<<"Hunters job: "<<hunters_job<<std::endl; //debug
    }
}
