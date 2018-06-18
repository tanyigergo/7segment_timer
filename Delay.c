#include "Delay.h"


static volatile  uint32_t tick = 0;

void SysTick_Handler()
{
	tick++;	
}


/**
  * @brief  Simple delay based on sysTick
  * @param  uint32_t millis: duration of delay in milliseconds
  * @retval None
  */
void delay(uint32_t millis)
{
	
	uint32_t tickCount = 0;
	tick = 0;
	while(tickCount < millis)
	{
		__disable_irq();
		tickCount = tick;
		__enable_irq();
	}
}
