#include <stdio.h>
#include <time.h>

#define LoopCount 10000

// (mul x, 2^N + 1) => (add (shl x, N), x)
// (mul x, 2^N - 1) => (sub (shl x, N), x)
int main()
{
    printf("Loop time: %d\n", LoopCount);
    clock_t start, end;
    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
            "   .align 3 \n"
            "   stp x29, x30, [sp,-16]! \n"
            "	sub	sp, sp, #64\n"

            "	mov	x0, #52\n"
            "   mov x1, #32\n"
            "	mul	x2, x0, x1\n"
            "	str	x2, [sp]\n"

            "	mov	x0, 0\n"
            "	add	sp, sp, 64\n"
            "   ldp x29, x30, [sp], 16\n"
        );

    }

    end = clock();
    printf("Before optimization: %dms.\n", end-start);

    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
            "   .align 3 \n"
            "   stp x29, x30, [sp,-16]! \n"
            "	sub	sp, sp, #64\n"

            "	mov	x0, #52\n"
            "   lsr x1, x0, 5\n"
            "	str	x1, [sp]\n"
            
            "	mov	x0, 0\n"
            "	add	sp, sp, 64\n"
            "   ldp x29, x30, [sp], 16\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}