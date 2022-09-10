#include "../include/sys/sys.h"
#include "../include/dev/usart.h"

// The ‘mscount’ variable keeps track of the time in milliseconds from the SysTick timer’s beginning
volatile uint32_t mscount;

/*
This function configure the system timer with interrupt. This function must disable the SysTick
timer, set ‘0’ to VAL register content, and load the reload value so the SysTick timer can interrupt
every 10ms. Initialize a global variable ‘mscount’ to ‘0’. The ‘mscount’ variable keeps track of the
time in milliseconds from the SysTick timer’s beginning. Then enable the SysTick timer.
*/
void sysTick_init(uint32_t load_value)
{
    SYSTICK->CTRL = 0;         // Disables systick and previous configs
    updateSysTick(load_value); // demonstration of sysTick update
    // Enables SysTick exception
    SYSTICK->CTRL |= SYSTICK_CTRL_TICKINT;
    // Indicates the clock source, processor clock source 0: AHB/8, 1: Processor clock (AHB
    SYSTICK->CTRL |= SYSTICK_CTRL_CLKSOURCE_AHB;
    sysTick_enable();
}

/*
This function enables the disabled SysTick timer. The function does not modify an active SysTick
timer and ‘mscount’ global variable. However, if the timer is currently disabled, the function must
initialize the ‘mscount’ to ‘0’ before enabling it.
*/
void sysTick_enable(void)
{
    if (!(SYSTICK->CTRL & SYSTICK_CTRL_ENABLE))
    {
        // if the timer is currently disabled, the function must initialize the ‘mscount’ to ‘0’ before enabling it
        mscount = 0;
    }
    SYSTICK->CTRL |= SYSTICK_CTRL_ENABLE;
}

// The sysTick disable function disables the SysTick timer if it is currently disabled.
void sysTick_disable(void)
{
    SYSTICK->CTRL &= SYSTICK_CTRL_DISABLE;
}

/*
The update function disables the timer, initializes the reload value to the LOAD register,
and finally initializes the ‘mscount’ variable.
*/
void updateSysTick(uint32_t reload_val)
{
    sysTick_disable();          // first disable the SysTick timer
    SYSTICK->VAL = 0;           // set ‘0’ to VAL register content
    SYSTICK->LOAD = reload_val; // CAUTION: load the reload value, max 24 bit!
}

// This function returns the current content of the VAL register.
uint32_t getSysTickCount()
{
    return SYSTICK->VAL;
}

/*
This function returns milliseconds by combining the ‘mscount’ and VAL-Register values. You can
use this function to get the execution time required for a code block.
*/
uint32_t getTime(void)
{
    float f = ((SYSTICK_LOAD_VAL_10MS - getSysTickCount()) * PER_TICK_TIME_DELAY_MS) / SYSTICK_LOAD_VAL_10MS;
    return mscount + (uint32_t)f;
}

void setTime(uint32_t _mscount)
{
    mscount = _mscount;
}

// Implementation of SystickInterrupt Handler
void SysTick_Handler(void)
{
    mscount += PER_TICK_TIME_DELAY_MS;
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
// Note that the value needs to be shifted by 4 when passing the arg
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

void EXTI0_Handler(void)
{
    _USART_WRITE(USART2, (uint8_t *)"AMMAAAAA JAAAAAAN\n");
}