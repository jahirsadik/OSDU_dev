/*
 * Copyright (c) 2022
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stm32_startup.h>
#include <kstdio.h>
#include <kmain.h>
void Reset_Handler(void)
{
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	uint8_t *pDst = (uint8_t *)&_sdata;
	uint8_t *pSrc = (uint8_t *)&_la_data;
	for (uint32_t i = 0; i < size; i++)
	{
		*pDst++ = *pSrc++;
	}
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	pDst = (uint8_t *)&_sbss;
	for (uint32_t i = 0; i < size; i++)
	{
		*pDst++ = 0;
	}
	_text_size = (uint32_t)&_etext - (uint32_t)&_stext;
	_data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
	_bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	kmain();
}
void Default_Handler(void)
{
	kprintf("Default_Handler\n");
	while (1)
		;
}
// 2. implement the fault handlers
void HardFault_Handler(void)
{
	kprintf("Exception : Hardfault\n");
	while (1)
		;
}

void MemManage_Handler(void)
{
	//	printf("Exception : MemManage\n");
	while (1)
		;
}

void BusFault_Handler(void)
{
	//	printf("Exception : BusFault\n");
	while (1)
		;
}

void SVC_Handler_Main(unsigned int *svc_args)
{
	unsigned int svc_number;
	/*
	 * Stack contains:
	 * r0, r1, r2, r3, r12, r14, the return address and xPSR
	 * First argument (r0) is svc_args[0]
	 */
	svc_number = ((char *)svc_args[6])[-2];
	uint32_t reg0 = svc_args;
	uint32_t reg1 = svc_args[1];
	uint32_t reg2 = svc_args[2];
	uint32_t reg3 = svc_args[3];
	uint32_t reg4 = svc_args[4];
	uint32_t reg5 = svc_args[5];
	uint32_t reg6 = svc_args[6];
	uint32_t reg7 = svc_args[7];

	switch (svc_number)
	{
	case 55:
		kprintf("SVC_Handler_Main: %d %d %d %d\n", reg0, reg1, reg2, reg3);
		kprintf("R13: %d, PSP: %d, MSP: %d\n", readR13(), readPSP(), readMSP());
		kprintf("SVC Number: %d\n", svc_number);
		kprintf("Pointer to Temp: %d\n", reg2);
		kprintf("STRING: %s\n", (char *)reg2);
		break;
	default: /* unknown SVC */
		break;
	}
}

__attribute__((naked)) void SVCall_Handler(void)
{
	/* Write code for SVC handler */
	/* the handler function evntually call syscall function with a call number */
	__asm volatile(
		".global SVC_Handler_Main\n"
		"TST lr, #4\n"
		"ITE EQ\n"
		"MRSEQ r0, MSP\n"
		"MRSNE r0, PSP\n"
		"B SVC_Handler_Main\n");
}
