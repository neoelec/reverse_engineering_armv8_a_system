/* SPDX-License-Identifier: MIT */

/*
 * Copyright (c) 2026 YOUNGJIN JOO (neoelec@gmail.com)
 */

#define _POSIX_C_SOURCE 2

#include <linux/prctl.h>
#include <setjmp.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/auxv.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <unistd.h>

#include <rcn_c/debug.h>

uintptr_t insert_random_tag(uintptr_t ptr)
{
    uintptr_t tagged_ptr;

    __asm__ volatile("irg %0, %1" : "=r"(tagged_ptr) : "r"(ptr));

    return tagged_ptr;
}

void set_memory_tag(uintptr_t ptr)
{
    __asm__ volatile("stg %0, [%0]" : : "r"(ptr) : "memory");
}

void check_at_hwcap2(void)
{
    if (!(getauxval(AT_HWCAP2) & HWCAP2_MTE)) {
        dbg_pr_fail("MTE is not supported\n");
        exit(EXIT_FAILURE);
    }

    if (prctl(PR_SET_TAGGED_ADDR_CTRL,
              PR_TAGGED_ADDR_ENABLE | PR_MTE_TCF_SYNC |
                  (0xfffe << PR_MTE_TAG_SHIFT),
              0, 0, 0) == -1) {
        dbg_pr_fail("prctl failed\n");
        exit(EXIT_FAILURE);
    }
}

jmp_buf buf;

void signal_handler(int sig)
{
    if (sig == SIGSEGV) {
        dbg_pr_warn("SIGSEGV\n");
        siglongjmp(buf, 1);
    }
}

void set_up_sigsegv(void)
{
    struct sigaction sa = {
        .sa_flags = SA_SIGINFO,
        .sa_handler = signal_handler,
    };

    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, NULL);
}

size_t len;
void *ptr;
uintptr_t tagged_ptr, bad_ptr;

void test_prolog(void)
{
    len = sysconf(_SC_PAGESIZE);

    if ((ptr = mmap(NULL, len, PROT_READ | PROT_WRITE | PROT_MTE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
        dbg_pr_fail("map() filed\n");
        exit(EXIT_FAILURE);
    }

    tagged_ptr = insert_random_tag((uintptr_t)ptr);
    bad_ptr = tagged_ptr + (1ULL << 56);

    for (size_t offset = 0; offset < len; offset += 16) {
        set_memory_tag(tagged_ptr + offset);
    }

    dbg_pr_info("tagged ptr = %#lx\n", tagged_ptr);
    dbg_pr_info("bad ptr    = %#lx\n", bad_ptr);
}

void test_body_0(void)
{
    dbg_pr_info("PR_MTE_TCF_NONE\n");

    if (prctl(PR_SET_TAGGED_ADDR_CTRL,
              PR_TAGGED_ADDR_ENABLE | PR_MTE_TCF_NONE |
                  (0xfffe << PR_MTE_TAG_SHIFT),
              0, 0, 0) == -1) {
        dbg_pr_fail("prctl failed\n");
        munmap(ptr, len);
        exit(EXIT_FAILURE);
    }

    *(volatile int *)bad_ptr = 0xdeadbeef;
    dbg_pr_pass("*%#lx = %#x\n", bad_ptr, *(unsigned int *)bad_ptr);
    dbg_pr_pass("PR_MTE_TCF_NONE - test passed\n");
}

void test_body_1(void)
{
    dbg_pr_info("PR_MTE_TCF_SYNC\n");

    if (prctl(PR_SET_TAGGED_ADDR_CTRL,
              PR_TAGGED_ADDR_ENABLE | PR_MTE_TCF_SYNC |
                  (0xfffe << PR_MTE_TAG_SHIFT),
              0, 0, 0) == -1) {
        dbg_pr_fail("prctl failed\n");
        munmap(ptr, len);
        exit(EXIT_FAILURE);
    }

    if (sigsetjmp(buf, 1) == 0) {
        *(volatile int *)bad_ptr = 0xcab0cafe;
        dbg_pr_fail("PR_MTE_TCF_SYNC - test failed\n");
    } else {
        dbg_pr_pass("PR_MTE_TCF_SYNC - test passed\n");
    }
}

void test_epilog(void)
{
    munmap(ptr, len);
}

int main(void)
{
    check_at_hwcap2();
    set_up_sigsegv();

    test_prolog();
    test_body_0();
    test_body_1();
    test_epilog();

    return 0;
}
