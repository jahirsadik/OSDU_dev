
object/stm32_startup.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <Reset_Handler>:
   0:	b580      	push	{r7, lr}
   2:	b086      	sub	sp, #24
   4:	af00      	add	r7, sp, #0
   6:	4a22      	ldr	r2, [pc, #136]	; (90 <Reset_Handler+0x90>)
   8:	4b22      	ldr	r3, [pc, #136]	; (94 <Reset_Handler+0x94>)
   a:	1ad3      	subs	r3, r2, r3
   c:	607b      	str	r3, [r7, #4]
   e:	4b21      	ldr	r3, [pc, #132]	; (94 <Reset_Handler+0x94>)
  10:	617b      	str	r3, [r7, #20]
  12:	4b21      	ldr	r3, [pc, #132]	; (98 <Reset_Handler+0x98>)
  14:	613b      	str	r3, [r7, #16]
  16:	2300      	movs	r3, #0
  18:	60fb      	str	r3, [r7, #12]
  1a:	e00a      	b.n	32 <Reset_Handler+0x32>
  1c:	693a      	ldr	r2, [r7, #16]
  1e:	1c53      	adds	r3, r2, #1
  20:	613b      	str	r3, [r7, #16]
  22:	697b      	ldr	r3, [r7, #20]
  24:	1c59      	adds	r1, r3, #1
  26:	6179      	str	r1, [r7, #20]
  28:	7812      	ldrb	r2, [r2, #0]
  2a:	701a      	strb	r2, [r3, #0]
  2c:	68fb      	ldr	r3, [r7, #12]
  2e:	3301      	adds	r3, #1
  30:	60fb      	str	r3, [r7, #12]
  32:	68fa      	ldr	r2, [r7, #12]
  34:	687b      	ldr	r3, [r7, #4]
  36:	429a      	cmp	r2, r3
  38:	d3f0      	bcc.n	1c <Reset_Handler+0x1c>
  3a:	4a18      	ldr	r2, [pc, #96]	; (9c <Reset_Handler+0x9c>)
  3c:	4b18      	ldr	r3, [pc, #96]	; (a0 <Reset_Handler+0xa0>)
  3e:	1ad3      	subs	r3, r2, r3
  40:	607b      	str	r3, [r7, #4]
  42:	4b17      	ldr	r3, [pc, #92]	; (a0 <Reset_Handler+0xa0>)
  44:	617b      	str	r3, [r7, #20]
  46:	2300      	movs	r3, #0
  48:	60bb      	str	r3, [r7, #8]
  4a:	e007      	b.n	5c <Reset_Handler+0x5c>
  4c:	697b      	ldr	r3, [r7, #20]
  4e:	1c5a      	adds	r2, r3, #1
  50:	617a      	str	r2, [r7, #20]
  52:	2200      	movs	r2, #0
  54:	701a      	strb	r2, [r3, #0]
  56:	68bb      	ldr	r3, [r7, #8]
  58:	3301      	adds	r3, #1
  5a:	60bb      	str	r3, [r7, #8]
  5c:	68ba      	ldr	r2, [r7, #8]
  5e:	687b      	ldr	r3, [r7, #4]
  60:	429a      	cmp	r2, r3
  62:	d3f3      	bcc.n	4c <Reset_Handler+0x4c>
  64:	4a0f      	ldr	r2, [pc, #60]	; (a4 <Reset_Handler+0xa4>)
  66:	4b10      	ldr	r3, [pc, #64]	; (a8 <Reset_Handler+0xa8>)
  68:	1ad3      	subs	r3, r2, r3
  6a:	4a10      	ldr	r2, [pc, #64]	; (ac <Reset_Handler+0xac>)
  6c:	6013      	str	r3, [r2, #0]
  6e:	4a08      	ldr	r2, [pc, #32]	; (90 <Reset_Handler+0x90>)
  70:	4b08      	ldr	r3, [pc, #32]	; (94 <Reset_Handler+0x94>)
  72:	1ad3      	subs	r3, r2, r3
  74:	4a0e      	ldr	r2, [pc, #56]	; (b0 <Reset_Handler+0xb0>)
  76:	6013      	str	r3, [r2, #0]
  78:	4a08      	ldr	r2, [pc, #32]	; (9c <Reset_Handler+0x9c>)
  7a:	4b09      	ldr	r3, [pc, #36]	; (a0 <Reset_Handler+0xa0>)
  7c:	1ad3      	subs	r3, r2, r3
  7e:	4a0d      	ldr	r2, [pc, #52]	; (b4 <Reset_Handler+0xb4>)
  80:	6013      	str	r3, [r2, #0]
  82:	f7ff fffe 	bl	0 <kmain>
  86:	bf00      	nop
  88:	3718      	adds	r7, #24
  8a:	46bd      	mov	sp, r7
  8c:	bd80      	pop	{r7, pc}
  8e:	bf00      	nop
	...

000000b8 <Default_Handler>:
  b8:	b480      	push	{r7}
  ba:	af00      	add	r7, sp, #0
  bc:	e7fe      	b.n	bc <Default_Handler+0x4>

000000be <HardFault_Handler>:
  be:	b480      	push	{r7}
  c0:	af00      	add	r7, sp, #0
  c2:	e7fe      	b.n	c2 <HardFault_Handler+0x4>

000000c4 <MemManage_Handler>:
  c4:	b480      	push	{r7}
  c6:	af00      	add	r7, sp, #0
  c8:	e7fe      	b.n	c8 <MemManage_Handler+0x4>

000000ca <BusFault_Handler>:
  ca:	b480      	push	{r7}
  cc:	af00      	add	r7, sp, #0
  ce:	e7fe      	b.n	ce <BusFault_Handler+0x4>

000000d0 <SVCall_Handler>:
  d0:	b580      	push	{r7, lr}
  d2:	af00      	add	r7, sp, #0
  d4:	4806      	ldr	r0, [pc, #24]	; (f0 <SVCall_Handler+0x20>)
  d6:	f7ff fffe 	bl	0 <kprintf>
  da:	f01e 0f04 	tst.w	lr, #4
  de:	bf0c      	ite	eq
  e0:	f3ef 8008 	mrseq	r0, MSP
  e4:	f3ef 8009 	mrsne	r0, PSP
  e8:	f7ff bffe 	b.w	0 <SVC_Handler_Main>
  ec:	bf00      	nop
  ee:	bd80      	pop	{r7, pc}
  f0:	00000000 	.word	0x00000000
