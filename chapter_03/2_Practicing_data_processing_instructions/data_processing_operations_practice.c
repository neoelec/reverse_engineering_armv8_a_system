#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define TASK_RUNNING 0x0000
#define TASK_INTERRUPTIBLE 0x0001
#define TASK_UNINTERRUPTIBLE 0x0002
#define __TASK_STOPPED 0x0004

#define print_state(state, flag) \
    if (state & flag)            \
    puts(#flag)

void check_curr_state(unsigned int state)
{
    print_state(state, TASK_RUNNING);
    print_state(state, TASK_INTERRUPTIBLE);
    print_state(state, TASK_UNINTERRUPTIBLE);
    print_state(state, __TASK_STOPPED);
}

void compare_operation(void)
{
    unsigned int state = TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE;
    unsigned int count = 1;

    if (state & TASK_UNINTERRUPTIBLE) {
        count++;
        state &= ~TASK_UNINTERRUPTIBLE;
    } else {
        count--;
        state |= __TASK_STOPPED;
    }

    check_curr_state(state);
}

int main(void)
{
    compare_operation();

    return 0;
}
