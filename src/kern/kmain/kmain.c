#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include "../arch/stm32f446re/include/dev/usart.h"
#include "../arch/stm32f446re/include/sys/stm32_peps.h"
#include "../arch/stm32f446re/include/sys/sys.h"
#include <stdint.h>

void kmain(void)
{
	__sys_init();
	sysTick_init(SYSTICK_LOAD_VAL_10MS); // demonstration of sysTick Init
	uint32_t num;
	uint32_t numh;
	_USART_WRITE(USART2, (uint8_t *)"Booting OS CSE: ");
	_USART_WRITE(USART2, (uint8_t *)"Version: 1.1\n");
	_USART_WRITE(USART2, (uint8_t *)"Welcome .... \n");
	SCB->AIRCR |= (3 << 8); // set priority grouping 11 means 4 bits for group 0 bits for subgroup
	__NVIC_SetPriority(USART2_STM_IRQn, 0); // Setting USART2 IRQ to max priority (lowest value)
	__enable_irq();
	__NVIC_EnableIRQn(EXTI0_STM_IRQn); // enabling EXTI0 IRQ
	uint32_t pri1 = __NVIC_GetPriority(USART2_STM_IRQn); // checking if USART2 priority was set
	kprintf((uint8_t *)"%d", (uint8_t *)&pri1);
	int i = 0;
	while (1)
	{
		i++;

		_USART_WRITE(USART2, (uint8_t *)"Time Before:");
		num = getTime();
		kprintf((uint8_t *)"%d", (uint8_t *)&num);

		_USART_WRITE(USART2, (uint8_t *)"Iteration: ");
		kprintf((uint8_t *)"%d", (uint8_t *)&i);

		// Demonstration of Interrupt Handler Invocation
		if (i == 4)
		{
			NVIC->STIR = EXTI0_STM_IRQn;
			__NVIC_SetPriority(EXTI0_STM_IRQn, 5);
			uint32_t pri2 = __NVIC_GetPriority(EXTI0_STM_IRQn);
			kprintf((uint8_t *)"%d", (uint8_t *)&pri2);
		}
		// Demo. of BASEPRI, doesn't mask as EXTI0 priority is lower value
		if (i == 5)
		{
			__set_BASEPRI(6 << 4);
			uint32_t pri3 = __get_BASEPRI();
			kprintf((uint8_t *)"%d", (uint8_t *)&pri3);
			NVIC->STIR = EXTI0_STM_IRQn;
		}
		// Demo. of BASEPRI, masks now
		if (i == 6)
		{
			__set_BASEPRI(4 << 4);
			uint32_t pri3 = __get_BASEPRI();
			kprintf((uint8_t *)"%d", (uint8_t *)&pri3);
			NVIC->STIR = EXTI0_STM_IRQn;
		}
		// Checking values of FAULTMASK AND PRIMASK
		if (i == 7)
		{
			uint32_t a = __get_FAULTMASK();
			uint32_t b = __get_PRIMASK();
			kprintf((uint8_t *)"%d", (uint8_t *)&a);
			kprintf((uint8_t *)"%d", (uint8_t *)&b);
			NVIC->STIR = EXTI0_STM_IRQn;
		}
		// Demo. of FaultMask
		if (i == 8)
		{
			_USART_WRITE(USART2, (uint8_t *)"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			__set_FAULTMASK(0x1U);
			_USART_WRITE(USART2, (uint8_t *)"***********************************************************************\n");
		}
		// Re-enabling Interrupts by setting FaultMask = 0
		if (i == 12)
		{
			_USART_WRITE(USART2, (uint8_t *)"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			__enable_fault_irq();
			_USART_WRITE(USART2, (uint8_t *)"***********************************************************************\n");
		}
		// Demo. of PriMask
		if (i == 13)
		{
			_USART_WRITE(USART2, (uint8_t *)"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			__set_PRIMASK(0x1U);
			_USART_WRITE(USART2, (uint8_t *)"***********************************************************************\n");
		}

		// Calculating the time to execute this loop
		uint32_t sum = 0;
		for (uint32_t i = 0; i < 1000000; i++)
		{
			sum += i;
		};
		_USART_WRITE(USART2, (uint8_t *)"Time After:");
		numh = getTime();
		kprintf((uint8_t *)"%d", (uint8_t *)&numh);
		_USART_WRITE(USART2, (uint8_t *)"--------------------------------------------\n");
		if (i > 15)
		{
			break;
		}
	}
}
