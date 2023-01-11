	.arch armv8-a
	.file	"test.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	stp	x29, x30, [sp, -432]!
	add	x29, sp, 0
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [x0]
	str	x1, [x29, 424]
	mov	x1,0
	mov	w0, 100
	str	w0, [x29, 20]
	str	wzr, [x29, 16]
	b	.L2
.L3:
	ldrsw	x0, [x29, 16]
	lsl	x0, x0, 2
	add	x1, x29, 24
	str	wzr, [x1, x0]
	ldr	w0, [x29, 16]
	add	w0, w0, 1
	str	w0, [x29, 16]
.L2:
	ldr	w1, [x29, 16]
	ldr	w0, [x29, 20]
	cmp	w1, w0
	blt	.L3
	mov	w0, 0
	adrp	x1, :got:__stack_chk_guard
	ldr	x1, [x1, #:got_lo12:__stack_chk_guard]
	ldr	x2, [x29, 424]
	ldr	x1, [x1]
	eor	x1, x2, x1
	cmp	x1, 0
	beq	.L5
	bl	__stack_chk_fail
.L5:
	ldp	x29, x30, [sp], 432
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
