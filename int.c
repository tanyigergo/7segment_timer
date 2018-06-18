#include "int.h"
#include "stm32f10x.h"

//configure interrupt line
void interruptInit()
{

	 

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn);
	
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 0);
	NVIC_SetPriority(EXTI2_IRQn, 0);
	NVIC_SetPriority(EXTI3_IRQn, 0);
	

}