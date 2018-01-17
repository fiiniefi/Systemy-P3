#include <ucontext.h>
#include <vector>

std::vector<ucontext_t *> contexts;

ucontext_t *schedule();
