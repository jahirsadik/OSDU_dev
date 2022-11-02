
object/unistd.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <SVC_Handler>:
   0:	b580      	push	{r7, lr}
   2:	af00      	add	r7, sp, #0
   4:	4806      	ldr	r0, [pc, #24]	; (20 <SVC_Handler+0x20>)
   6:	f7ff fffe 	bl	0 <kprintf>
   a:	f01e 0f04 	tst.w	lr, #4
   e:	bf0c      	ite	eq
  10:	f3ef 8008 	mrseq	r0, MSP
  14:	f3ef 8009 	mrsne	r0, PSP
  18:	f7ff bffe 	b.w	24 <SVC_Handler_Main>
  1c:	bf00      	nop
  1e:	bd80      	pop	{r7, pc}
  20:	00000000 	.word	0x00000000

00000024 <SVC_Handler_Main>:
  24:	b580      	push	{r7, lr}
  26:	b084      	sub	sp, #16
  28:	af00      	add	r7, sp, #0
  2a:	6078      	str	r0, [r7, #4]
  2c:	687b      	ldr	r3, [r7, #4]
  2e:	3318      	adds	r3, #24
  30:	681b      	ldr	r3, [r3, #0]
  32:	3b02      	subs	r3, #2
  34:	781b      	ldrb	r3, [r3, #0]
  36:	60fb      	str	r3, [r7, #12]
  38:	68fb      	ldr	r3, [r7, #12]
  3a:	2b37      	cmp	r3, #55	; 0x37
  3c:	d108      	bne.n	50 <SVC_Handler_Main+0x2c>
  3e:	687b      	ldr	r3, [r7, #4]
  40:	3304      	adds	r3, #4
  42:	681b      	ldr	r3, [r3, #0]
  44:	60bb      	str	r3, [r7, #8]
  46:	68b9      	ldr	r1, [r7, #8]
  48:	4804      	ldr	r0, [pc, #16]	; (5c <SVC_Handler_Main+0x38>)
  4a:	f7ff fffe 	bl	0 <kprintf>
  4e:	e000      	b.n	52 <SVC_Handler_Main+0x2e>
  50:	bf00      	nop
  52:	bf00      	nop
  54:	3710      	adds	r7, #16
  56:	46bd      	mov	sp, r7
  58:	bd80      	pop	{r7, pc}
  5a:	bf00      	nop
  5c:	00000008 	.word	0x00000008

00000060 <write>:
  60:	b480      	push	{r7}
  62:	b085      	sub	sp, #20
  64:	af00      	add	r7, sp, #0
  66:	60f8      	str	r0, [r7, #12]
  68:	60b9      	str	r1, [r7, #8]
  6a:	607a      	str	r2, [r7, #4]
  6c:	68fb      	ldr	r3, [r7, #12]
  6e:	0018      	movs	r0, r3
  70:	68bb      	ldr	r3, [r7, #8]
  72:	0019      	movs	r1, r3
  74:	687b      	ldr	r3, [r7, #4]
  76:	001a      	movs	r2, r3
  78:	df37      	svc	55	; 0x37
  7a:	2300      	movs	r3, #0
  7c:	4618      	mov	r0, r3
  7e:	3714      	adds	r7, #20
  80:	46bd      	mov	sp, r7
  82:	f85d 7b04 	ldr.w	r7, [sp], #4
  86:	4770      	bx	lr

00000088 <duprintf>:
  88:	b580      	push	{r7, lr}
  8a:	b082      	sub	sp, #8
  8c:	af00      	add	r7, sp, #0
  8e:	4b08      	ldr	r3, [pc, #32]	; (b0 <duprintf+0x28>)
  90:	607b      	str	r3, [r7, #4]
  92:	2207      	movs	r2, #7
  94:	6879      	ldr	r1, [r7, #4]
  96:	2001      	movs	r0, #1
  98:	f7ff fffe 	bl	60 <write>
  9c:	6038      	str	r0, [r7, #0]
  9e:	6839      	ldr	r1, [r7, #0]
  a0:	4804      	ldr	r0, [pc, #16]	; (b4 <duprintf+0x2c>)
  a2:	f7ff fffe 	bl	0 <kprintf>
  a6:	bf00      	nop
  a8:	3708      	adds	r7, #8
  aa:	46bd      	mov	sp, r7
  ac:	bd80      	pop	{r7, pc}
  ae:	bf00      	nop
  b0:	0000000c 	.word	0x0000000c
  b4:	00000018 	.word	0x00000018
