## Chapter 9: Understanding Basic Static Analysis

### The if with return statement

```
                                      ┌───────────────────────────────────────────────┐
                                      │  0x874                                        │
                                      │   ;[x] CALL XREF from dbg.main @ 0x6cc(x)     │
                                      │ 44: sym.bound_condition (int64_t arg1);       │
                                      │ `- args(x0) vars(2:sp[0x8..0x10])             │
                                      │ stp x29, x30, [sp, -0x10]!; {                 │
                                      │ mov x29, sp                                   │
                                      │ bl dbg.loop_func; retval = loop_func(a);;[oa] │
                                      │ cmp w0, 1; if (retval == 1) {                 │
                                      │ b.eq 0x898                                    │
                                      └───────────────────────────────────────────────┘
                                              f t
                                              │ │
                                              │ └───────────────────┐
    ┌─────────────────────────────────────────┘                     │
    │                                                               │                                                        
┌──────────────────────────────────────────────────────────┐    ┌───────────────────────────────────────────────────────────┐
│  0x888                                                   │    │  0x898                                                    │
│ ldp x29, x30, [sp], 0x10; void bound_condition(int a)    │    │ ;[x] CODE XREF from sym.bound_condition @ 0x884(x)        │
│ adrp x0, 0; puts("do something others");                 │    │ ldp x29, x30, [sp], 0x10; puts("do something others");    │
│ ; 0x8d1                                                  │    │ ret                                                       │
│ ; "do something others"                                  │    └───────────────────────────────────────────────────────────┘
│ add x0, x0, str.do_something_others                      │
│ b sym.imp.puts                                           │
└──────────────────────────────────────────────────────────┘
```
