#include "../include/sys/sys.h"

// The ‘mscount’ variable keeps track of the time in milliseconds from the SysTick timer’s beginning
volatile uint32_t mscount;

/*
This function configure the system timer with interrupt. This function must disable the SysTick
timer, set ‘0’ to VAL register content, and load the reload value so the SysTick timer can interrupt every 10ms. Initialize a global variable ‘mscount’ to ‘0’. The ‘mscount’ variable keeps track of the time in milliseconds from the SysTick timer’s beginning. Then enable the SysTick timer. 
*/
void sysTick_init(uint32_t load_value){
    SYSTICK->CTRL = 0; // Disables systick and previous configs
    updateSysTick(load_value); // demonstration of sysTick update
    // Enables SysTick exception
    SYSTICK->CTRL |= SYSTICK_CTRL_TICKINT;
    // Indicates the clock source, processor clock source 0: AHB/8, 1: Processor clock (AHB
    SYSTICK->CTRL |= SYSTICK_CTRL_CLKSOURCE_AHB;
    sysTick_enable();
}

/*
This function enables the disabled SysTick timer. The function does not modify an active SysTick timer and ‘mscount’ global variable. However, if the timer is currently disabled, the function must initialize the ‘mscount’ to ‘0’ before enabling it.
*/
void sysTick_enable(void){
    if(!(SYSTICK->CTRL & SYSTICK_CTRL_ENABLE)){
        // if the timer is currently disabled, the function must initialize the ‘mscount’ to ‘0’ before enabling it
        mscount = 0;
    }
    SYSTICK->CTRL |= SYSTICK_CTRL_ENABLE;
}

// The sysTick disable function disables the SysTick timer if it is currently disabled.
void sysTick_disable(void){
    SYSTICK->CTRL &= SYSTICK_CTRL_DISABLE;
}

/*
The update function disables the timer, initializes the reload value to the LOAD register, and finally initializes the ‘mscount’ variable.
*/
void updateSysTick(uint32_t reload_val){
    sysTick_disable(); // first disable the SysTick timer
    SYSTICK->VAL = 0; // set ‘0’ to VAL register content
    SYSTICK->LOAD = reload_val; // CAUTION: load the reload value, max 24 bit! 
}

// This function returns the current content of the VAL register.
uint32_t getSysTickCount(){
    return SYSTICK->VAL;
}

/*
This function returns milliseconds by combining the ‘mscount’ and VAL-Register values. You can
use this function to get the execution time required for a code block.
*/
uint32_t getTime(void){
    float f = ((SYSTICK_LOAD_VAL_10MS - getSysTickCount())*PER_TICK_TIME_DELAY_MS)/SYSTICK_LOAD_VAL_10MS;
    return mscount + (uint32_t)f;
}

void setTime(uint32_t _mscount){
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
void __NVIC_SetPriority (IRQn_TypeDef IRQn,uint32_t priority){
    NVIC->IP[IRQn] = (uint8_t)(0xFF & priority);
}

/*
    uint32 t NVIC GetPriority(IRQn TypeDef IRQn): Return the priority set to the interrupt.
*/
uint32_t __NVIC_GetPriority (IRQn_TypeDef IRQn){
    return (0xFF & NVIC->IP[IRQn]);
}

/*
 Enable interrupt given as argument or interrupt number (IRQn typeDef) – data structure (enumerator) defined earlier.
*/
void __NVIC_EnableIRQn(IRQn_TypeDef IRQn){
    int bit_position = (IRQn % 32);
    NVIC->ISER[IRQn >> 5] |= (1 << bit_position);
}

// Disable interrupt
void __NVIC_DisableIRQn(IRQn_TypeDef IRQn){
    int bit_position = (IRQn % 32);
    NVIC->ICER[IRQn >> 5] |= (1 << bit_position);
}