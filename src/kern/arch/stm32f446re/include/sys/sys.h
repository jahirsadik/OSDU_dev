#ifndef __SYS_H__
#define __SYS_H__
#include <stdint.h>



typedef struct {
	volatile uint32_t CTRL;  // Enable SysTick
	volatile uint32_t LOAD;  // 24
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
} SysTick_Typedef;

// Address for SysTick 0xE000E010
#define SYSTICK ((SysTick_Typedef *) 0xE000E010 )
#define SYSTICK_CTRL_CLKSOURCE_AHB (1 << 2)
#define SYSTICK_CTRL_TICKINT (1 << 1)
#define SYSTICK_CTRL_ENABLE (1 << 0)
#define SYSTICK_CTRL_DISABLE ~(1 << 0)
#define PER_TICK_TIME_DELAY_MS 10U
/* 
		SysTick Test Code
		180*10^6*10^(-2)-1 = 1799999 = Reload value for 10ms, for AHBCLK = 180Mhz
		SysTick Interrup Time Period = (SysTick_LOAD + 1) * Clock_Period 
*/
#define SYSTICK_LOAD_VAL_10MS (((180*10*10*10*10*10*10)*(PER_TICK_TIME_DELAY_MS)/1000) - 1)

/*
This function configure the system timer with interrupt. This function must disable the SysTick
timer, set ‘0’ to VAL register content, and load the reload value so the SysTick timer can interrupt every 10ms. Initialize a global variable ‘mscount’ to ‘0’. The ‘mscount’ variable keeps track of the time in milliseconds from the SysTick timer’s beginning. Then enable the SysTick timer.
*/
void sysTick_init(uint32_t load_value);
/*
This function enables the disabled SysTick timer. The function does not modify an active SysTick timer and ‘mscount’ global variable. However, if the timer is currently disabled, the function must initialize the ‘mscount’ to ‘0’ before enabling it.
*/
void sysTick_enable(void);
// The sysTick disable function disables the SysTick timer if it is currently disabled.
void sysTick_disable(void);
// This function returns the current content of the VAL register.
uint32_t getSysTickCount();
/*
he update function disables the timer, initializes the reload value to the LOAD register, and finally initializes the ‘mscount’ variable.
*/
void updateSysTick(uint32_t reload_val);
/*
This function returns milliseconds by combining the ‘mscount’ and VAL-Register values. You can
use this function to get the execution time required for a code block.
*/
uint32_t getTime(void);
void setTime(uint32_t _mscount);
void SysTick_Delay(uint32_t delay_amount_in_ms);
void SysTick_Handler(void); 

#endif
