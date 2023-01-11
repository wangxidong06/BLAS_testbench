#include <stdio.h>
#include <time.h>

#define LoopCount 1000

int main()
{
    printf("Loop time: %d\n", LoopCount);
    clock_t start, end;
    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
        "    str	fp, [sp, #-4]!\n"
        "    add	fp, sp, #0\n"
        "    sub    sp, sp, #4\n"
        "    mov    r1, #24\n"
        "    mov    r2, #34\n"
        "    str    r1, [sp]\n"
        "    ldr    r3, [sp]\n"
        "    add    r0, r0, r2\n"
        "    eor    r0, r0, r3\n"
        "    mov	r3, #0\n"
        "    mov	r0, r3\n"
        "    add	sp, fp, #0\n"
        "    ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("Before optimization: %dms.\n", end-start);

    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
        "    str	fp, [sp, #-4]!\n"
        "    add	fp, sp, #0\n"
        "    sub    sp, sp, #4\n"
        "    mov    r1, #24\n"
        "    mov    r2, #34\n"
        "    str    r1, [sp]\n"
        "    add    r0, r0, r2\n"
        "    ldr    r3, [sp]\n"
        "    eor    r0, r0, r3\n"
        "    mov	r3, #0\n"
        "    mov	r0, r3\n"
        "    add	sp, fp, #0\n"
        "    ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}