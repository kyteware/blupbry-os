	.cpu arm7tdmi
	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"1-blink.c"
	.text
	.align	2
	.global	notmain
	.syntax unified
	.arm
	.type	notmain, %function
notmain:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #8
	mov	r3, #20
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	mov	r0, r3
	bl	gpio_set_output
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L2
.L3:
	ldr	r3, [fp, #-12]
	mov	r0, r3
	bl	gpio_set_on
	ldr	r0, .L4
	bl	delay_cycles
	ldr	r3, [fp, #-12]
	mov	r0, r3
	bl	gpio_set_off
	ldr	r0, .L4
	bl	delay_cycles
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L2:
	ldr	r3, [fp, #-8]
	cmp	r3, #9
	ble	.L3
	nop
	nop
	sub	sp, fp, #4
	@ sp needed
	pop	{fp, lr}
	bx	lr
.L5:
	.align	2
.L4:
	.word	1000000
	.size	notmain, .-notmain
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
