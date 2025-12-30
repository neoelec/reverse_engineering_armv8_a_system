## Chapter 9: Understanding Basic Static Analysis

### A for loop with a return 0 statement

```
                       ┌──────────────────────────────────────────────────────┐
                       │  0x828                                               │
                       │ ; int loop_func(int c);                              │
                       │   ;-- loop_func:                                     │
                       │   ;[x] CALL XREF from sym.bound_condition @ 0x88c(x) │
                       │ 92: dbg.loop_func (int64_t arg1);                    │
                       │ `- args(x0) vars(5:sp[0x10..0x30])                   │
                       │ stp x29, x30, [sp, -0x30]!; {                        │
                       │ mov x29, sp                                          │
                       │ stp x19, x20, [var_10h]                              │
                       │ ; arg1                                               │
                       │ mov w19, w0                                          │
                       │ mov w20, 0; int a = 0;                               │
                       │ str x21, [var_20h]; {                                │
                       │ adrp x21, 0; printf("loop_func count: %d\n", a);     │
                       │ ; 0x8cc                                              │
                       │ ; "loop_func count: %d\n"                            │
                       │ add x21, x21, str.loop_func_count:__d_n              │
                       └──────────────────────────────────────────────────────┘
                           v
                           │
                           └─────┐
┌──────────────────────────────────┐
│                                │ │                                       
│                          ┌──────────────────────────────────────────────┐
│                          │  0x848                                       │
│                          │ ;[x] CODE XREF from dbg.loop_func @ 0x864(x) │
│                          │ cmp w19, w20; if (i == c) {                  │
│                          │ b.eq 0x87c                                   │
│                          └──────────────────────────────────────────────┘
│                                  f t
│                                  │ │
│                                  │ └─────────────────────────────────┐
│    ┌─────────────────────────────┘                                   │
│    │                                                                 │                                           
│┌─────────────────────────────────────────────────────────────┐   ┌──────────────────────────────────────────────┐
││  0x850                                                      │   │  0x87c                                       │
││ mov w1, w20; printf("loop_func count: %d\n", a);            │   │ ;[x] CODE XREF from dbg.loop_func @ 0x84c(x) │
││ ; const char *format                                        │   │ mov w0, 0; return 0;                         │
││ mov x0, x21                                                 │   │ b 0x86c                                      │
││ add w20, w20, 1; a++;                                       │   └──────────────────────────────────────────────┘
││ ; int printf(const char *format)                            │       v
││ bl sym.imp.printf; printf("loop_func count: %d\n", a);;[oa] │       │
││ cmp w20, 0x64; a++;                                         │       │
││ b.ne 0x848                                                  │       │
│└─────────────────────────────────────────────────────────────┘       │
│        f t                                                           │
│        │ │                                                           │
└──────────┘                                                           │
         └───┐                                                         │
             │                                                      ┌──┘
             │                                                      │
         ┌─────────────────────────────────────┐                    │
         │  0x868                              │                    │
         │ add w0, w19, 0x64; return c + a;    │                    │
         └─────────────────────────────────────┘                    │
             v                                                      │
             │                                                      │
             └────────────────┐                                     │
                              │ ┌───────────────────────────────────┘
                              │ │                                       
                        ┌──────────────────────────────────────────────┐
                        │  0x86c                                       │
                        │ ;[x] CODE XREF from dbg.loop_func @ 0x880(x) │
                        │ ldr x21, [var_20h]; }                        │
                        │ ldp x19, x20, [var_10h]                      │
                        │ ldp x29, x30, [sp], 0x30                     │
                        │ ret                                          │
                        └──────────────────────────────────────────────┘
```
