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
        "str     fp, [sp, #-4]!\n\t"
        "add     fp, sp, #0\n\t"
        "sub     sp, sp, #20\n\t"
        "mov     r3, #4\n\t"
        "str     r3, [fp, #-8]\n\t"
        "mov     r3, #5\n\t"
        "str     r3, [fp, #-12]\n\t"
        "ldr     r2, [fp, #-8]\n\t"
        "ldr     r3, [fp, #-12]\n\t"
        "sub     r3, r2, r3\n\t"
        "str     r3, [fp, #-16]\n\t"
        "ldr     r3, [fp, #-16]\n\t"
        "cmp     r3, #0\n\t"
        "ble     .BLK2\n\t"
        "ldr     r3, [fp, #-8]\n\t"
        "add     r3, r3, #10\n\t"
        "str     r3, [fp, #-8]\n\t"
        "b       .BLK3\n\t"
        ".BLK2:\n\t"
        "ldr     r3, [fp, #-16]\n\t"
        "cmp     r3, #0\n\t"
        "bge     .BLK3\n\t"
        "ldr     r3, [fp, #-8]\n\t"
        "sub     r3, r3, #10\n\t"
        "str     r3, [fp, #-8]\n\t"
        ".BLK3:\n\t"
        "mov     r3, #0\n\t"
        "mov     r0, r3\n\t"
        "add     sp, fp, #0\n\t"
        "ldr     fp, [sp], #4\n\t"
        );

    }
    end = clock();
    printf("Before optimization: %dms.\n", end-start);


    start = clock();
    for (int i=0; i<LoopCount; i++){

        __asm(
        "str     fp, [sp, #-4]!\n\t"
        "add     fp, sp, #0\n\t"
        "sub     sp, sp, #20\n\t"
        "mov     r3, #4\n\t"
        "str     r3, [fp, #-8]\n\t"
        "mov     r3, #5\n\t"
        "str     r3, [fp, #-12]\n\t"
        "ldr     r2, [fp, #-8]\n\t"
        "ldr     r3, [fp, #-12]\n\t"
        "subs     r3, r2, r3\n\t"
        "ble     .BL2\n\t"
        "ldr     r3, [fp, #-8]\n\t"
        "add     r3, r3, #10\n\t"
        "str     r3, [fp, #-8]\n\t"
        "b       .BL3\n\t"
        ".BL2:\n\t"
        "bge     .BL3\n\t"
        "ldr     r3, [fp, #-8]\n\t"
        "sub     r3, r3, #10\n\t"
        "str     r3, [fp, #-8]\n\t"
        ".BL3:\n\t"
        "mov     r3, #0\n\t"
        "mov     r0, r3\n\t"
        "add     sp, fp, #0\n\t"
        "ldr     fp, [sp], #4\n\t"
        );

    }
    end = clock();
    printf("After optimization: %dms.\n", end-start);
}