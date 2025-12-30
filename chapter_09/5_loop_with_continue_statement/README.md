## Chapter 9: Understanding Basic Static Analysis

### A for loop with a continue statement

```
┌──────────────────────────────────────────────────────┐
│  0x828                                               │
│ ; int loop_func(int c);                              │
│   ;-- loop_func:                                     │
│   ;-- pc:                                            │
│   ;[x] CALL XREF from sym.bound_condition @ 0x88c(x) │
│ 92: dbg.loop_func (int64_t arg1);                    │
│ `- args(x0) vars(6:sp[0x8..0x30])                    │
│ stp x29, x30, [sp, -0x30]!; {                        │
│ mov x29, sp                                          │
│ stp x19, x20, [var_10h]                              │
│ ; arg1                                               │
│ mov w19, w0                                          │
│ mov w20, 0; int a = 0;                               │
│ stp x21, x22, [var_20h]; {                           │
│ adrp x22, 0; printf("loop_func count: %d\n", a);     │
│ ; 0x8cc                                              │
│ ; "loop_func count: %d\n"                            │
│ add x22, x22, str.loop_func_count:__d_n              │
│ mov w21, 0; for (int i = 0; i < 100; i++) {          │
└──────────────────────────────────────────────────────┘
    v
    │
    └─────┐
┌───────────┐
│         │ │                                       
│   ┌──────────────────────────────────────────────┐
│   │  0x84c                                       │
│   │ ;[x] CODE XREF from dbg.loop_func @ 0x86c(x) │
│   │ cmp w19, w21; if (i == c) {                  │
│   │ b.eq 0x864                                   │
│   └──────────────────────────────────────────────┘
│           f t
│           │ │
│           │ └────────────────────────────────────────────┐
│    ┌──────┘                                              │
│    │                                                     │
│┌─────────────────────────────────────────────────────┐   │
││  0x854                                              │   │
││ mov w1, w20; printf("loop_func count: %d\n", a);    │   │
││ add w20, w20, 1; a++;                               │   │
││ ; const char *format                                │   │
││ mov x0, x22; printf("loop_func count: %d\n", a);    │   │
││ ; int printf(const char *format)                    │   │
││ bl sym.imp.printf;[oa]                              │   │
│└─────────────────────────────────────────────────────┘   │
│    v                                                     │
│    │                                                     │
│    └──┐                                                  │
│       │ ┌────────────────────────────────────────────────┘
│       │ │                                            
│ ┌───────────────────────────────────────────────────┐
│ │  0x864                                            │
│ │ ;[x] CODE XREF from dbg.loop_func @ 0x850(x)      │
│ │ add w21, w21, 1; a++;                             │
│ │ cmp w21, 0x64; for (int i = 0; i < 100; i++) {    │
│ │ b.ne 0x84c                                        │
│ └───────────────────────────────────────────────────┘
│         f t
│         │ │
└───────────┘
          └──┐
             │                                 
         ┌────────────────────────────────────┐
         │  0x870                             │
         │ add w0, w20, w19; return c + a;    │
         │ ldp x19, x20, [var_10h]            │
         │ ldp x21, x22, [var_20h]; }         │
         │ ldp x29, x30, [sp], 0x30           │
         │ ret                                │
         └────────────────────────────────────┘
```
