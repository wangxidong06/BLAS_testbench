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
"	sub	sp, sp, #36\n"
"	mov	r3, #52\n"
"	str	r3, [fp, #-8]\n"
"	mov	r3, #34\n"
"	str	r3, [fp, #-12]\n"
"	mov	r3, #32\n"
"	str	r3, [fp, #-16]\n"
"	mov	r3, #53\n"
"	str	r3, [fp, #-20]\n"
"	mov	r3, #85\n"
"	str	r3, [fp, #-24]\n"
"	mov	r3, #2\n"
"	str	r3, [fp, #-28]\n"
"	mov	r3, #90\n"
"	str	r3, [fp, #-32]\n"
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
"	sub	sp, sp, #36\n"
"	mov	r0, #52\n"
"	mov	r1, #34\n"
"	mov	r2, #32\n"
"	mov	r3, #53\n"
"	mov	r4, #85\n"
"	mov	r5, #2\n"
"	mov	r6, #90\n"
"	stmia sp, {r0, r1, r2, r3, r4, r5, r6}\n"
"	mov	r3, #0\n"
"	mov	r0, r3\n"
"	add	sp, fp, #0\n"
"	ldr	fp, [sp], #4\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}