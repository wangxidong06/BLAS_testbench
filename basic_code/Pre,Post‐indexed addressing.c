#include <stdio.h>
#include <time.h>

#define LoopCount 100

int main()
{
    printf("Loop time: %d\n", LoopCount);
    clock_t start, end;
    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
            "   str	fp, [sp, #-4]!\n"
            "	add	fp, sp, #0\n"
            "	sub	sp, sp, #400\n"
            "	mov	r3, #0\n"
            "	b	.BLK2\n"
            ".BLK3:\n"
            "   mov r2, r3, lsl #2\n"
            "   mov r1, #0\n"
            "   str r1, [sp, r2]\n"
            "   add r3, r3, #1\n"
            ".BLK2:\n"
            "	cmp	r3, #99\n"
            "	ble	.BLK3\n"
            "	mov	r3, #0\n"
            "	mov	r2, #0\n"
            "	mov	r0, r3\n"
            "	mov sp, fp\n"
            "	ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("Before optimization: %dms.\n", end-start);

    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
            "   .align 3 \n"
            "   stp x29, x30, [sp,-16]! \n"
            "	sub	sp, sp, 400\n"
            "	mov	x3, 0\n"
            "   mov x2, sp\n"
            "	b	.BL2\n"
            ".BL3:\n"
            "   mov x1, 0\n"
            "   str x1, [r2], 4\n"
            "   add x3, x3, 1\n"
            ".BL2:\n"
            "	cmp	x3, 99\n"
            "	blt	.BL3\n"

            "	mov	x0, 0\n"
            "	add	sp, sp, 64\n"
            "   ldp x29, x30, [sp], 16\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}