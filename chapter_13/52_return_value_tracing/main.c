#include <stdio.h>

int add_func(int x, int y)
{
    int result = x + y;

    printf("x:%d, y:%d, ret:%d\n", x, y, result);

    return result;
}

int main(void)
{
    add_func(2, 3);

    return 0;
}
