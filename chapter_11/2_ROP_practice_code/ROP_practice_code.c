#include <signal.h>
#include <stdio.h>

void call_empty(void) __attribute__((noreturn));
void call_empty(void)
{
    printf("call_empty() called!\n");
}

void sig_handler(int signum)
{
    printf("Signal handler called!\n");
    call_empty();
}

void secret_execution(void)
{
    printf("secret_execution called!\n");
}

int main(void)
{
    signal(SIGUSR1, sig_handler);
    printf("About to raise the signal.\n");
    raise(SIGUSR1); /* Triggers the handler */

    printf("Complete: Signal handler executed.\n");

    return 0;
}
