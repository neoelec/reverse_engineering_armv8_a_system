## Chapter 9: Understanding Basic Static Analysis

### The if with return statement

```
    ┌──────────────────────────────────────────────────────┐
    │  0x828                                               │
    │ ; int loop_func(int c);                              │
    │   ;-- loop_func:                                     │
    │   ;[x] CALL XREF from sym.bound_condition @ 0x87c(x) │
    │ 76: dbg.loop_func (int64_t arg1);                    │
    │ `- args(x0) vars(5:sp[0x10..0x30])                   │
    │ stp x29, x30, [sp, -0x30]!; {                        │
    │ mov x29, sp                                          │
    │ stp x19, x20, [var_10h]                              │
    │ ; arg1                                               │
    │ mov w20, w0                                          │
    │ mov w19, 0; int a = 0;                               │
    │ str x21, [var_20h]; {                                │
    │ adrp x21, 0; printf("loop_func count: %d\n", a);     │
    │ ; 0x8bc                                              │
    │ ; "loop_func count: %d\n"                            │
    │ add x21, x21, str.loop_func_count:__d_n              │
    └──────────────────────────────────────────────────────┘
        v
        │
        └───────────────────────┐
                                │
                                │
                                │
       ┌────────────────────────┘
┌────────┐
│      │ │                                                      
│┌─────────────────────────────────────────────────────────────┐
││  0x848                                                      │
││ ;[x] CODE XREF from dbg.loop_func @ 0x85c(x)                │
││ mov w1, w19; printf("loop_func count: %d\n", a);            │
││ ; const char *format                                        │
││ mov x0, x21                                                 │
││ add w19, w19, 1; a++;                                       │
││ ; int printf(const char *format)                            │
││ bl sym.imp.printf; printf("loop_func count: %d\n", a);;[oa] │
││ cmp w19, 0x64; a++;                                         │
││ b.ne 0x848                                                  │
│└─────────────────────────────────────────────────────────────┘
│        f t
│        │ │
└──────────┘
         └──────┐
                │                                   
            ┌──────────────────────────────────────┐
            │  0x860                               │
            │ ldr x21, [var_20h]; return c + a;    │
            │ add w0, w20, 0x64                    │
            │ ldp x19, x20, [var_10h]              │
            │ ldp x29, x30, [sp], 0x30; }          │
            │ ret                                  │
            └──────────────────────────────────────┘
```
