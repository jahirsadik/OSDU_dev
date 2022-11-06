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

#include <sys_init.h>
#include <cm4.h>
#include <kmain.h>
#include <kstdio.h>
#include <kstring.h>
#include <stdint.h>
#include <usart.h>
//#include "../include/float.h"

#include <unistd.h>

void changeMode(uint32_t modeValue)
{
	__asm volatile("MOVS R12, %0"
				   :
				   : "r"(modeValue)
				   :);
	__asm volatile("MSR CONTROL, R12"
				   :
				   :
				   :);
	__asm volatile("ISB");
}

uint32_t getMode()
{
	uint32_t cRet;
	__asm volatile("MRS %0, CONTROL"
				   : "=r"(cRet)
				   :
				   :);
	return cRet;
}

uint32_t getIPSR()
{
	uint32_t cRet;
	__asm volatile("MRS %0, IPSR"
				   : "=r"(cRet)
				   :
				   :);
	kprintf("getIPSR: %d\n", cRet);
	return cRet;
}

uint32_t in_privileged()
{
	if (getIPSR() != 0)
		return 1; // True
	else
	{
		if ((getMode() & 0x1) == 0)
			return 1; // True
		else
			return 0; // False
	}
}

void setPSP(void)
{
	__asm volatile(".equ SRAM_END, (0x2000000 + (128 *1024))");
	__asm volatile(".equ STACK_PSP_START, (SRAM_END - 512)");
	__asm volatile("LDR R0,=STACK_PSP_START");
	__asm volatile("MSR PSP, R0");
	__asm volatile("ISB");
	//__asm volatile("MOVS R0, #0X02");
	// __asm volatile("MSR CONTROL, R0");
	//__asm volatile("BX LR");
}

uint32_t readPSP()
{
	uint32_t psp1;
	__asm volatile("MRS %0, PSP"
				   : "=r"(psp1)
				   :
				   :);
	return psp1;
}

uint32_t readMSP()
{
	uint32_t psp1;
	__asm volatile("MRS %0, MSP"
				   : "=r"(psp1)
				   :
				   :);
	return psp1;
}

uint32_t readR13()
{
	uint32_t psp1;
	__asm volatile("MOV %0, R13"
				   : "=r"(psp1)
				   :
				   :);
	return psp1;
}

void kmain(void)
{
	__sys_init();
	setPSP();

	uint32_t psp = readPSP();
	kprintf("PSP: %d\n", psp);
	psp = readR13();
	kprintf("R13: %d\n", psp);
	psp = readMSP();
	kprintf("MSP: %d\n", psp);

	// priority handling
	__NVIC_SetPriority(SVCall_IRQn, 0);
	__NVIC_SetPriority(USART2_STM_IRQn, 2);
	__NVIC_SetPriority(USART1_STM_IRQn, 2);
	__NVIC_SetPriority(USART3_STM_IRQn, 2);
	__NVIC_SetPriority(USART6_STM_IRQn, 2);
	__NVIC_SetPriority(SysTick_IRQn, 2);
	kprintf("SVCall_IRQn: %d\n", __NVIC_GetPriority(SVCall_IRQn));
	kprintf("SysTick_IRQn: %d\n", __NVIC_GetPriority(SysTick_IRQn));
	kprintf("USART_IRQn1: %d\n", __NVIC_GetPriority(USART1_STM_IRQn));
	kprintf("USART_IRQn2: %d\n", __NVIC_GetPriority(USART2_STM_IRQn));
	kprintf("USART_IRQn3: %d\n", __NVIC_GetPriority(USART3_STM_IRQn));
	kprintf("USART_IRQn6: %d\n", __NVIC_GetPriority(USART6_STM_IRQn));

	// ending priority handling

	changeMode(3);
	for (uint32_t i = 0; i < 10000000; i++)
		;
	uint32_t mode = getMode();
	kprintf("MODE in kmain: %d\n", mode);
	if (in_privileged())
	{
		kprintf("Privileged\n");
	}
	else
	{
		kprintf("Unprivileged\n");
	}
	kprintf("kmain - R13: %d, PSP: %d, MSP: %d\n", readR13(), readPSP(), readMSP());
	fu();
	kprintf("BACK IN KMAIN\n");
	while (1)
		;
}
