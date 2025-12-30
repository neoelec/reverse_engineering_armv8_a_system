#include <stdio.h>

void func(int x)
{
    if (x > 0x100) {
        puts("x > 0x100");
    } else {
        puts("x is else");
    }
}

int main(void)
{
    func(0x0);
    func(0x100);

    return 0;
}
