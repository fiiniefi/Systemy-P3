#include "pthr.h"
#include <ucontext.h>
#include <stdexcept>

std::queue<ucontext_t *> contexts;

bool schedule()
{
    if (contexts.empty())
        return false;
    ucontext_t *prev;
    if (swapcontext(prev, contexts.front()))
        return false;
    contexts.pop();
    contexts.push(prev);
    return true;
}

ucontext_t *create(void (*ptr)(), int argc, int argv[])
{
    ucontext_t *nthr = new ucontext_t();
    nthr->uc_stack.ss_size = argc;
    makecontext(nthr, ptr, argc, argv);
    contexts.push(nthr);
    return nthr;
}

void join(ucontext_t *threadid)
{
    ucontext_t *now = new ucontext_t();
    getcontext(now);
    while (threadid == now);
    schedule();
}
