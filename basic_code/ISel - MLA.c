#include <stdio.h>
#include <time.h>

#define LoopCount 10000

// ML{A/S}: Mlultiply Accumulate/SubStract
// Rd = Rn + Rm * Rs
// SMLAL: Signed Multiply Accumulate Long
// RdHi,RdLo = RdHi,RdLo + Rm*Rs
// @see ARMARM.P179
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
            "	mov	x0, 1\n"    
            "	str	x0, [sp, 8]\n"  //store a
            "	mov	x0, 2\n"    
            "	str	x0, [sp, 16]\n" //store b
            "	mov	x0, 3\n"    
            "	str	x0, [sp, 24]\n" //store c
            "	ldr	x0, [sp, 8]\n"  //load  a
            "	ldr	x1, [sp, 16]\n" //load  b
            "	ldr	x2, [sp, 24]\n" //load  c
            "	add	x0, x1, x0\n"   //a+b
            "	mul	x2, x2, x0\n"   //(a+b)*c
            "	str	x0, [sp, 32]\n" //store (a+b)*c
            "	mov	x0, 0\n"
            "	add	sp, sp, 64\n"
            "   ldp x29, x30, [sp], 16\n"
        );

    }

    end = clock();
    printf("Before optimization: %dms.\n", end-start);

    start = clock();

    for (int i=0; i<(LoopCount/4); i++){

        __asm(
            "   .align 2 \n"
            "   stp x29, x30, [sp,-16]! \n"
            "	sub	sp, sp, #64\n"
            "	mov	w0, 1\n"    
            "	str	w0, [sp]\n"     //store a
            "	mov	w0, 2\n"    
            "	str	w0, [sp, 4]\n"  //store b
            "	mov	w0, 3\n"    
            "	str	w0, [sp, 8]\n" //store c
            "	ld3r {v0.4S, v1.4S, v2.4S}, [sp]\n"  //load  a,b,c
            "	mul	v3.4S, v2.4S, v0.4S\n"   //a*c
            "	mla	v3.4S, v1.4S, v2.4S\n"   //a*c+b*c
            "	st1	{v0.4S}, [sp]\n"         //store a*c+b*c
            "	mov	x0, 0\n"
            "	add	sp, sp, 64\n"
            "   ldp x29, x30, [sp], 16\n"
        );

    }

    end = clock();
    printf("After optimization: %dms.\n", end-start);
}