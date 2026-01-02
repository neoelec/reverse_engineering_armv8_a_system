## Chapter 13: Tracing Execution with uftrace

### Argument tracing

#### `-fno-builtin-printf`
- GCC는 `printf("string\n")` 를 `puts("string")`로 자동으로 최적화 한다(문자열 끝에 `'\n'`의 유무에 유의).
- 따라서 이 예제를 테스트 하려면 다음 두가지 중 한가지 방법을 선택해야 한다.
  1. `printf` 함수 대신 `puts`를 추적한다.
  2. 컴파일러 옵션에 `-fno-builtin-printf`를 추가해, `printf`를 `puts`로 변경하는 것을 막는다.

```
Hello, World!
WARN: child terminated by signal: 4: Illegal instruction
# DURATION     TID      FUNCTION
   6.691 us [    940] | __monstartup();
   3.696 us [    940] | __cxa_atexit();
            [    940] | main() {
   3.581 ms [    940] |   puts("Hello, World!");
   3.618 ms [    940] | } /* main *
```

```
Hello, World!
WARN: child terminated by signal: 4: Illegal instruction
# DURATION     TID      FUNCTION
   7.120 us [    856] | __monstartup();
   4.000 us [    856] | __cxa_atexit();
            [    856] | main() {
   4.571 ms [    856] |   printf("Hello, World!\n");
   4.717 ms [    856] | } /* main */
```
