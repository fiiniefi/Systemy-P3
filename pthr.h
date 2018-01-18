#include <ucontext.h>
#include <queue>

std::queue<ucontext_t *> contexts;

bool schedule();
void create(void (*ptr)(), int argc, int argv[]); //"The value of argc must match the number of integers passed to ptr"
void join(ucontext_t *threadid);
