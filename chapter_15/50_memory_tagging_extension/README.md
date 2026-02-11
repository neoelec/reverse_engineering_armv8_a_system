## Chapter 15: Building Defenses with Key Security Features of Armv8-A

### Memory Tagging Extension (MTE)
- 아쉽게도 책에서는 MTE의 예제는 소개하지 않는다.
- 예제를 통해 MTE의 동작을 살펴본다.
- MTE 사용 조건에서 Tag-Mismatch가 발생하면 `SIGSEGV`가 발생한다.
- 이것을 이용해 다음의 테스트를 진행한다.
  1. Top-Byte를 손상시킨 Bad Pointer를 만든다.
  2. `PR_MTE_TCF_NONE` 설정 후 Bad Pointer를 통해 메모리를 접근한다.
    - 이 때는 `SIGSEG`가 발생하지 않는다.
  3. `PR_MTE_TCF_SYNC` 설정 후 Bad Pointer를 통해 메모리를 접근한다.
    - 이 때는 `SIGSEG`가 발생하고, Signal Handler에서 로그 출력 후 복귀

```
[INFO] tagged ptr = 0x200ffffbe1d7000
[INFO] bad ptr    = 0x300ffffbe1d7000
[INFO] PR_MTE_TCF_NONE
[PASS] *0x300ffffbe1d7000 = 0xdeadbeef
[PASS] PR_MTE_TCF_NONE - test passed
[INFO] PR_MTE_TCF_SYNC
[WARN] SIGSEGV
[PASS] PR_MTE_TCF_SYNC - test passed
```
