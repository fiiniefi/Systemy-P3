#include <ucontext.h>
#include <queue>
#include <functional>

std::queue<ucontext_t *> contexts;

bool schedule();
bool create(std::function<void(...)> ptr);
