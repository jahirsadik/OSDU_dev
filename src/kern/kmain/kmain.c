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

	__disable_irq();
	uint32_t num;
	uint32_t numh;
	uint32_t total_time = 0;
	_USART_WRITE(USART2,(uint8_t*)"Booting OS CSE: ");
	_USART_WRITE(USART2,(uint8_t*)"Version: 1.1\n");
	_USART_WRITE(USART2,(uint8_t*)"Welcome .... \n");


	while(1){
		sysTick_enable(); // demonstration of sysTick Enable
		_USART_WRITE(USART2,(uint8_t*)"++++++++++++++++++++++++++++++++++++++++++++++\n");
		_USART_WRITE(USART2,(uint8_t*)"SysTickCount Before:");
		num = getSysTickCount();
		kprintf((uint8_t*)"%d",(uint8_t*)&num);
		_USART_WRITE(USART2,(uint8_t*)"Time Before:");
		numh = getTime();
		kprintf((uint8_t*)"%d",(uint8_t*)&numh);
		// Calculating the time to execute this loop
		uint32_t sum = 0;
		for(uint32_t i=0;i<1000000;i++){
			sum += i;
		};
		_USART_WRITE(USART2,(uint8_t*)"SysTickCount After:");
		num = getSysTickCount();
		kprintf((uint8_t*)"%d",(uint8_t*)&num);
		_USART_WRITE(USART2,(uint8_t*)"Time After:");
		numh = getTime();
		kprintf((uint8_t*)"%d",(uint8_t*)&numh);
		total_time += numh;
		_USART_WRITE(USART2,(uint8_t*)"Total Time:");
		kprintf((uint8_t*)"%d",(uint8_t*)&total_time);
		sysTick_disable();  // demonstration of sysTick Disable
		_USART_WRITE(USART2,(uint8_t*)"--------------------------------------------");
	}
}

