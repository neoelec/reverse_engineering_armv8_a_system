#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void logical_operation(void)
{
    size_t x = 0x23, y = 0x123, z = 0x103;
    size_t a = 0xf, b = 0xf0;
    size_t result1, result2, result3;

    result1 = x & y;
    result2 = x | z;
    result3 = a ^ b;

    printf("result1: 0x%zx, result2: 0x%zx, result3: 0x%zx \n", result1,
           result2, result3);
}

int main(void)
{
    logical_operation();

    return 0;
}
