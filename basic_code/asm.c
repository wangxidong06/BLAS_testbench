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
        "    sub	sp, sp, #20\n"
        "    mov	r3, #3\n"
        "    str	r3, [fp, #-8]\n"
        "    mov	r3, #5\n"
        "    str	r3, [fp, #-12]\n"
        "    ldr	r2, [fp, #-8]\n"
        "    ldr	r3, [fp, #-12]\n"
        "    cmp	r2, r3\n"
        "    ble	.BLK2\n"
        "    mov	r3, #2\n"
        "    str	r3, [fp, #-16]\n"
        "    b	.BLK3\n"
        ".BLK2:\n"
        "    mov	r3, #7\n"
        "    str	r3, [fp, #-16]\n"
        ".BLK3:\n"
        "    mov	r3, #0\n"
        "    mov	r0, r3\n"
        "    add	sp, fp, #0\n"
        "    @ sp needed\n"
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
        "    sub	sp, sp, #20\n"
        "    mov	r3, #3\n"
        "    str	r3, [fp, #-8]\n"
        "    mov	r3, #5\n"
        "    str	r3, [fp, #-12]\n"
        "    ldr	r2, [fp, #-8]\n"
        "    ldr	r3, [fp, #-12]\n"
        "    cmp	r2, r3\n"
        "    movgt	r3, #2\n"         // 这些
        "    strgt	r3, [fp, #-16]\n" // 这些
        "    movle	r3, #7\n"         // 这些
        "    strle	r3, [fp, #-16]\n" // 这些
        "    mov	r3, #0\n"
        "    mov	r0, r3\n"
        "    add	sp, fp, #0\n"
        "    @ sp needed\n"
        "    ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}