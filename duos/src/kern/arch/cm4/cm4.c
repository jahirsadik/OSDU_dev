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

#include <cm4.h>
#include <clock.h>
#include <kstdio.h>
#include <syscall.h>
volatile static uint32_t __mscount;
/************************************************************************************
 * __SysTick_init(uint32_t reload)
 * Function initialize the SysTick clock. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

void __SysTick_init(uint32_t reload)
{
    SYSTICK->CTRL &= ~(1 << 0); // disable systick timer
    SYSTICK->VAL = 0;           // initialize the counter
    __mscount = 0;
    SYSTICK->LOAD = PLL_N * reload;
    SYSTICK->CTRL |= 1 << 1 | 1 << 2; // enable interrupt and internal clock source
    SYSTICK->CTRL |= 1 << 0;          // enable systick counter
}

/************************************************************************************
 * __sysTick_enable(void)
 * The function enables the SysTick clock if already not enabled.
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/
void __sysTick_enable(void)
{
    if (SYSTICK->CTRL & ~(1 << 0))
        SYSTICK->CTRL |= 1 << 0;
}
void __sysTick_disable(void)
{
    if (!(SYSTICK->CTRL & ~(1 << 0)))
        SYSTICK->CTRL &= ~(1 << 0);
}
uint32_t __getSysTickCount(void)
{
    return SYSTICK->VAL;
}
/************************************************************************************
 * __updateSysTick(uint32_t count)
 * Function reinitialize the SysTick clock. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

void __updateSysTick(uint32_t count)
{
    SYSTICK->CTRL &= ~(1 << 0); // disable systick timer
    SYSTICK->VAL = 0;           // initialize the counter
    __mscount = 0;
    SYSTICK->CTRL |= 1 << 1 | 1 << 2; // enable interrupt and internal clock source
    SYSTICK->LOAD = PLL_N * count;
    SYSTICK->CTRL |= 1 << 0; // enable systick counter
}

/************************************************************************************
 * __getTime(void)
 * Function return the SysTick elapsed time from the begining or reinitialing. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

uint32_t __getTime(void)
{
    return (__mscount + (SYSTICK->LOAD - SYSTICK->VAL) / (PLL_N * 1000));
}
void SysTick_Handler()
{
    __mscount += (SYSTICK->LOAD) / (PLL_N * 1000);
    kprintf("\n..Inside Systick..\n");
}

void __enable_fpu()
{
    SCB->CPACR |= ((0xF << 20));
}

/*
void NVIC SetPriority (IRQn TypeDef IRQn,uint32 t priority): This function takes two argu-
ments (i) interrupt number and sets the priority to the interrupt. Note that priority in the above
NVIC register is 8-bit. The priority puts the preference to the ISR executing before the lower
(higher number) priority interrupts.
*/
void __NVIC_SetPriority(IRQn_TypeDef IRQn, uint32_t priority)
{
    if (IRQn >= 0)
    {
        NVIC->IP[IRQn] = ((priority << 4) & 0xFFU);
    }
    else
    {
        switch (IRQn)
        {
        // mem management fault
        case -12:
            SCB->SHPR1 |= (uint8_t)(0xFFU & priority) << 0;
            break;
        // BusFault_IRQn
        case -11:
            SCB->SHPR1 |= (uint8_t)(0xFFU & priority) << 8;
            break;
        // UsageFault_IRQn
        case -10:
            SCB->SHPR1 |= (uint8_t)(0xFFU & priority) << 16;
            break;
        // SVCall_IRQn
        case -5:
            SCB->SHPR2 |= (uint8_t)(0xFFU & priority) << 24;
            break;
        // PendSV
        case -2:
            SCB->SHPR3 |= (uint8_t)(0xFFU & priority) << 16;
            break;
        // SysTick exception
        case -1:
            SCB->SHPR3 |= (uint8_t)(0xFFU & priority) << 24;
            break;
        default:
            return;
        }
    }
}

/*
    uint32 t NVIC GetPriority(IRQn TypeDef IRQn): Return the priority set to the interrupt.
*/
uint32_t __NVIC_GetPriority(IRQn_TypeDef IRQn)
{
    if (IRQn >= 0)
    {
        return (NVIC->IP[IRQn]) >> 4;
    }
    else
    {
        switch (IRQn)
        {
        // mem management fault
        case -12:
            return (SCB->SHPR1 & (0xFFU << 0)) >> 0;
        // BusFault_IRQn
        case -11:
            return (SCB->SHPR1 & (0xFFU << 8)) >> 8;
        // UsageFault_IRQn
        case -10:
            return (SCB->SHPR1 & (0xFFU << 16)) >> 16;
        // SVCall_IRQn
        case -5:
            return (SCB->SHPR2 & (0xFFU << 24)) >> 24;
        // PendSV
        case -2:
            return (SCB->SHPR3 & (0xFFU << 16)) >> 16;
        // SysTick exception
        case -1:
            return (SCB->SHPR3 & (0xFFU << 24)) >> 24;
        default:
            return 0;
        }
    }
}

/*
 Enable interrupt given as argument or interrupt number (IRQn typeDef) – data structure (enumerator) defined earlier.
*/
void __NVIC_EnableIRQn(IRQn_TypeDef IRQn)
{
    int bit_position = (IRQn % 32);
    if (IRQn >= 0)
    {
        NVIC->ISER[IRQn >> 5] |= (1 << bit_position);
    }
    else
    {
        switch (IRQn)
        {
        // USGFAULTENA:
        case -10:
            SCB->SHCSR |= (1 << 18);
            break;
        // BUSFAULTENA
        case -11:
            SCB->SHCSR |= (1 << 17);
            break;
        // MEMFAULTENA:
        case -12:
            SCB->SHCSR |= (1 << 16);
            break;
        default:
            return;
        }
    }
}

// Disable interrupt
void __NVIC_DisableIRQn(IRQn_TypeDef IRQn)
{
    int bit_position = (IRQn % 32);
    if (IRQn >= 0)
    {
        NVIC->ICER[IRQn >> 5] |= (1 << bit_position);
    }
    else
    {
        switch (IRQn)
        {
        // USGFAULTENA:
        case -10:
            SCB->SHCSR &= ~(1 << 18);
            break;
        // BUSFAULTENA
        case -11:
            SCB->SHCSR &= ~(1 << 17);
            break;
        // MEMFAULTENA:
        case -12:
            SCB->SHCSR &= ~(1 << 16);
            break;
        default:
            return;
        }
    }
}

// Set BASEPRI
// The Value needs to be shifted by 4 when passing the arg
// This is assuming that only 4 bits are implemented
__attribute__((naked)) void __set_BASEPRI(uint32_t value)
{
    __asm volatile("MOVS R12, %0"
                   :
                   : "r"(value & 0xFFU)
                   :);
    __asm volatile("MSR BASEPRI, R12"
                   :
                   :
                   :);
}

uint32_t __get_BASEPRI(void)
{
    uint32_t result;

    __asm volatile("MRS %0, basepri"
                   : "=r"(result));
    return (result >> 4);
}

// Unset BASEPRI
__attribute__((naked)) void __unset_BASEPRI()
{
    __set_BASEPRI(0x00U);
}

__attribute__((naked)) void __set_PRIMASK(uint32_t priMask)
{
    __asm volatile("MOVS R12, %0"
                   :
                   : "r"(priMask & 0x01U)
                   :);
    __asm volatile("MSR PRIMASK, R12"
                   :
                   :
                   :);
}

__attribute__((naked)) uint32_t __get_PRIMASK(void)
{
    uint32_t pmRet;
    __asm volatile("MRS %0, PRIMASK"
                   : "=r"(pmRet)
                   :
                   :);
    return pmRet & 0x01U;
}

__attribute__((naked)) void __set_FAULTMASK(uint32_t faultMask)
{
    __asm volatile("MOVS R12, %0"
                   :
                   : "r"(faultMask & 0x01U)
                   :);
    __asm volatile("MSR FAULTMASK, R12"
                   :
                   :
                   :);
}

__attribute__((naked)) uint32_t __get_FAULTMASK(void)
{
    uint32_t fmRet;
    __asm volatile("MRS %0, FAULTMASK"
                   : "=r"(fmRet)
                   :
                   :);
    return fmRet & 0x01U;
}

void __clear_pending_IRQn(IRQn_TypeDef IRQn)
{
    if (IRQn >= 0)
    {
        int bit_position = (IRQn % 32);
        NVIC->ICPR[IRQn >> 5] |= (1 << bit_position);
    }
}

uint32_t __get_pending_IRQn(IRQn_TypeDef IRQn)
{
    if (IRQn >= 0)
    {
        int bit_position = (IRQn % 32);
        return ((NVIC->ISPR[IRQn >> 5] & (1 << bit_position)) >> (bit_position));
    }
    else
    {
        switch (IRQn)
        {
            // SVCALL PEND
        case -5:
            return (SCB->SHCSR & (1 << 15)) >> 15;
        // USGFAULT PEND
        case -10:
            return (SCB->SHCSR & (1 << 14)) >> 14;
        // BUSFAULT PEND
        case -11:
            return (SCB->SHCSR & (1 << 13)) >> 13;
        // MEMFAULT PEND
        case -12:
            return (SCB->SHCSR & (1 << 12)) >> 12;
        default:
            return 0;
        }
    }
}

uint32_t __NVIC_GetActive(IRQn_TypeDef IRQn)
{
    if (IRQn >= 0)
    {
        int bit_position = (IRQn % 32);
        return (NVIC->IABR[IRQn >> 5] & (1 << bit_position));
    }
    else
    {
        switch (IRQn)
        {
            // SYSTICK ACT
        case -1:
            return (SCB->SHCSR & (1 << 11)) >> 11;
        // PENDSV ACT
        case -2:
            return (SCB->SHCSR & (1 << 10)) >> 10;
        // Debug monitor ACT
        case -4:
            return (SCB->SHCSR & (1 << 8)) >> 8;
        // SVCALL ACT
        case -5:
            return (SCB->SHCSR & (1 << 7)) >> 7;
        // USGFAULT ACT
        case -10:
            return (SCB->SHCSR & (1 << 3)) >> 3;
        // BUSFAULT ACT
        case -11:
            return (SCB->SHCSR & (1 << 1)) >> 1;
        // MEMFAULT ACT
        case -12:
            return (SCB->SHCSR & (1 << 0)) >> 0;
        default:
            return 0;
        }
    }
}
