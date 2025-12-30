#include <stdio.h>

void func(int x)
{
    if (x > 0x100) {
        puts("x > 0x100");
    } else if (x < 0x300) {
        puts("x > 0x100 and x < 0x300");
    } else {
        puts("x is else");
    }
}

int main(void)
{
    func(0x20);

    return 0;
}
