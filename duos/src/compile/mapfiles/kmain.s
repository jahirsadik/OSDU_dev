
object/kmain.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <changeMode>:
   0:	4603      	mov	r3, r0
   2:	ea5f 0c03 	movs.w	ip, r3
   6:	f38c 8814 	msr	CONTROL, ip
   a:	bf00      	nop

0000000c <getMode>:
   c:	f3ef 8314 	mrs	r3, CONTROL
  10:	461c      	mov	r4, r3
  12:	4621      	mov	r1, r4
  14:	4802      	ldr	r0, [pc, #8]	; (20 <getMode+0x14>)
  16:	f7ff fffe 	bl	0 <kprintf>
  1a:	f004 030f 	and.w	r3, r4, #15
  1e:	4618      	mov	r0, r3
  20:	00000000 	.word	0x00000000

00000024 <getIPSR>:
  24:	f3ef 8305 	mrs	r3, IPSR
  28:	461c      	mov	r4, r3
  2a:	4621      	mov	r1, r4
  2c:	4802      	ldr	r0, [pc, #8]	; (38 <getIPSR+0x14>)
  2e:	f7ff fffe 	bl	0 <kprintf>
  32:	f004 030f 	and.w	r3, r4, #15
  36:	4618      	mov	r0, r3
  38:	00000010 	.word	0x00000010

0000003c <kmain>:
  3c:	b5b0      	push	{r4, r5, r7, lr}
  3e:	b086      	sub	sp, #24
  40:	af02      	add	r7, sp, #8
  42:	f7ff fffe 	bl	0 <__sys_init>
  46:	4b2d      	ldr	r3, [pc, #180]	; (fc <kmain+0xc0>)
  48:	60bb      	str	r3, [r7, #8]
  4a:	2317      	movs	r3, #23
  4c:	71fb      	strb	r3, [r7, #7]
  4e:	2338      	movs	r3, #56	; 0x38
  50:	71bb      	strb	r3, [r7, #6]
  52:	edd7 7a02 	vldr	s15, [r7, #8]
  56:	eeb7 7a00 	vmov.f32	s14, #112	; 0x3f800000  1.0
  5a:	ee77 7a87 	vadd.f32	s15, s15, s14
  5e:	edc7 7a02 	vstr	s15, [r7, #8]
  62:	79fc      	ldrb	r4, [r7, #7]
  64:	79bd      	ldrb	r5, [r7, #6]
  66:	68b8      	ldr	r0, [r7, #8]
  68:	f7ff fffe 	bl	0 <__aeabi_f2d>
  6c:	4602      	mov	r2, r0
  6e:	460b      	mov	r3, r1
  70:	e9cd 2300 	strd	r2, r3, [sp]
  74:	462a      	mov	r2, r5
  76:	4621      	mov	r1, r4
  78:	4821      	ldr	r0, [pc, #132]	; (100 <kmain+0xc4>)
  7a:	f7ff fffe 	bl	0 <kprintf>
  7e:	4821      	ldr	r0, [pc, #132]	; (104 <kmain+0xc8>)
  80:	f7ff fffe 	bl	0 <kprintf>
  84:	481f      	ldr	r0, [pc, #124]	; (104 <kmain+0xc8>)
  86:	f7ff fffe 	bl	0 <kprintf>
  8a:	f7ff fffe 	bl	0 <__getTime>
  8e:	4603      	mov	r3, r0
  90:	4619      	mov	r1, r3
  92:	481d      	ldr	r0, [pc, #116]	; (108 <kmain+0xcc>)
  94:	f7ff fffe 	bl	0 <kprintf>
  98:	2001      	movs	r0, #1
  9a:	f7ff fffe 	bl	0 <changeMode>
  9e:	2300      	movs	r3, #0
  a0:	60fb      	str	r3, [r7, #12]
  a2:	e002      	b.n	aa <kmain+0x6e>
  a4:	68fb      	ldr	r3, [r7, #12]
  a6:	3301      	adds	r3, #1
  a8:	60fb      	str	r3, [r7, #12]
  aa:	68fb      	ldr	r3, [r7, #12]
  ac:	4a17      	ldr	r2, [pc, #92]	; (10c <kmain+0xd0>)
  ae:	4293      	cmp	r3, r2
  b0:	d9f8      	bls.n	a4 <kmain+0x68>
  b2:	f7ff fffe 	bl	c <getMode>
  b6:	6038      	str	r0, [r7, #0]
  b8:	6839      	ldr	r1, [r7, #0]
  ba:	4815      	ldr	r0, [pc, #84]	; (110 <kmain+0xd4>)
  bc:	f7ff fffe 	bl	0 <kprintf>
  c0:	f7ff fffe 	bl	24 <getIPSR>
  c4:	4603      	mov	r3, r0
  c6:	2b00      	cmp	r3, #0
  c8:	d003      	beq.n	d2 <kmain+0x96>
  ca:	4812      	ldr	r0, [pc, #72]	; (114 <kmain+0xd8>)
  cc:	f7ff fffe 	bl	0 <kprintf>
  d0:	e00d      	b.n	ee <kmain+0xb2>
  d2:	f7ff fffe 	bl	c <getMode>
  d6:	4603      	mov	r3, r0
  d8:	f003 0301 	and.w	r3, r3, #1
  dc:	2b00      	cmp	r3, #0
  de:	d103      	bne.n	e8 <kmain+0xac>
  e0:	480c      	ldr	r0, [pc, #48]	; (114 <kmain+0xd8>)
  e2:	f7ff fffe 	bl	0 <kprintf>
  e6:	e002      	b.n	ee <kmain+0xb2>
  e8:	480a      	ldr	r0, [pc, #40]	; (114 <kmain+0xd8>)
  ea:	f7ff fffe 	bl	0 <kprintf>
  ee:	f7ff fffe 	bl	0 <duprintf>
  f2:	bf00      	nop
  f4:	3710      	adds	r7, #16
  f6:	46bd      	mov	sp, r7
  f8:	bdb0      	pop	{r4, r5, r7, pc}
  fa:	bf00      	nop
  fc:	424a5c29 	.word	0x424a5c29
 100:	00000024 	.word	0x00000024
 104:	00000030 	.word	0x00000030
 108:	00000040 	.word	0x00000040
 10c:	000f423f 	.word	0x000f423f
 110:	00000054 	.word	0x00000054
 114:	00000064 	.word	0x00000064
