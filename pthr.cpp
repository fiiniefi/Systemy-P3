#include "pthr.h"
#include <ucontext.h>
#include <stdexcept>


bool schedule()
{
    if (contexts.size() == 0)
        return false;
    ucontext_t *prev;
    if (swapcontext(prev, contexts.front()))
        return false;
    contexts.pop();
    contexts.push(prev);
    return true;
}

void create(void (*ptr)(), int argc, int argv[])
{
    ucontext_t *nthr = new ucontext_t();
    makecontext(nthr, ptr, argc, argv);
    contexts.push(nthr);
}
