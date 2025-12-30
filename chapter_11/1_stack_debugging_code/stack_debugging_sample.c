#include <stdio.h>

#define GET_SP_REGISTER_DEBUG() debug_sp_register()

static size_t *sp_value;
static size_t *lr_value;

static inline void debug_sp_register(void)
{
    __asm__ volatile("mov %0,sp\n"
                     "mov %1,lr"
                     : "=r"(sp_value), "=r"(lr_value));

    printf("sp: %p, fp: %p\n", sp_value, lr_value);

    printf("[%p]: 0x%zx\n", sp_value, *sp_value);
    printf("[%p]: 0x%zx\n", sp_value + 1, *(sp_value + 1));
    printf("[%p]: 0x%zx\n", sp_value + 2, *(sp_value + 2));
}

void suspicious_stack_corruption(void)
{
}

int add_func(int x, int y)
{
    int result = x + y;

    GET_SP_REGISTER_DEBUG();
    suspicious_stack_corruption();
    printf("x: %d, y: %d\n", x, y);

    return result;
}

int main(void)
{
    add_func(1, 2);

    return 0;
}
