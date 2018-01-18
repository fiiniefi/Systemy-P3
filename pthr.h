#include <ucontext.h>
#include <queue>

std::queue<ucontext_t *> contexts;

bool schedule();
void create(ucontext_t *ptr);
