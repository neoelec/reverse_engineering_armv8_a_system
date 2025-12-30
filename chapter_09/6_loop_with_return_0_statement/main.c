#include <stdio.h>

int loop_func(int c)
{
    int a = 0;

    for (int i = 0; i < 100; i++) {
        if (i == c) {
            return 0;
        }

        printf("loop_func count: %d\n", a);
        a++;
    }

    return c + a;
}

void bound_condition(int a)
{
    int retval;

    retval = loop_func(a);

    if (retval == 1) {
        return;
    }

    puts("do something others");
}

int main(int argc, char *argv[])
{
    bound_condition(10);

    return 0;
}
