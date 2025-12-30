#include <stdio.h>

void func(int x)
{
    if (x == 0x100) {
        puts("x == 0x100");
    }
}

int main(void)
{
    func(0x100);

    return 0;
}
