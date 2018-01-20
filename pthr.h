#include <ucontext.h>
#include <queue>

std::queue<ucontext_t *> contexts;

bool schedule();
void create(void (*ptr)(), int argc, int argv[]); //"The value of argc must match the number of integers passed to ptr"
void join(ucontext_t *threadid);

class Semaphore
{
protected:
    int signal;
public:
    virtual void wake_up() = 0;
    virtual void wait() = 0;
    Semaphore(int val) : signal(val) {}
};

class Binsem : public Semaphore
{
public:
    Binsem() : Semaphore(1) {}
    void wake_up()
    {
        signal = 1;
    }
    void wait()
    {
        while (signal == 0);
        signal = 0;
    }
};

class Countsem : public Semaphore
{
private:
    int maxthr;
public:
    Countsem(int maxthr) : Semaphore(maxthr), maxthr(maxthr) {}
    void wake_up()
    {
        if (signal < maxthr)
            signal++;
    }
    void wait()
    {
        while (signal == 0);
        signal--;
    }
};
