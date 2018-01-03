#include "pthr.h"
#include <ucontext.h>
#include <stdexcept>


ucontext_t *schedule(ucontext_t *ncon)
{
    ucontext_t *prev = new ucontext_t();
    if (swapcontext(prev, ncon))
        throw std::invalid_argument("schedule(ucontext_t*): The argument does not have enough stack left to complete the operation");
    return prev;
}
