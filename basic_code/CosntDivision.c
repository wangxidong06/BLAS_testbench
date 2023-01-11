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
"	str	fp, [sp, #-4]!\n"
"	add	fp, sp, #0\n"
"	sub	sp, sp, #12\n"
"	mov	r3, #52\n"
"	str	r3, [fp, #-8]\n"
"	ldr	r2, [fp, #-8]\n"
"	mov r3, #3\n"
"	sdiv r3, r2, r3\n"
"	str	r3, [fp, #-12]\n"
"	mov	r3, #0\n"
"	mov	r0, r3\n"
"	add	sp, fp, #0\n"
"	ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("Before optimization: %dms.\n", end-start);

    start = clock();

    for (int i=0; i<LoopCount; i++){

        __asm(
"	str	fp, [sp, #-4]!\n"
"	add	fp, sp, #0\n"
"	sub	sp, sp, #12\n"
"	mov	r3, #52\n"
"	str	r3, [fp, #-8]\n"
"	ldr	r2, [fp, #-8]\n"
"	movw	r3, #21846\n"
"	movt	r3, 21845\n"
"	smull	r3, r1, r3, r2\n"
"	asr	r3, r2, #31\n"
"	sub	r3, r1, r3\n"
"	str	r3, [fp, #-12]\n"
"	mov	r3, #0\n"
"	mov	r0, r3\n"
"	add	sp, fp, #0\n"
"	ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}