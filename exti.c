#include "exti.h"
#include "stm32f10x.h"                  // Device header

void exti_init()
{
 	// enable clock for Alternate Function
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0 & AFIO_EXTICR1_EXTI0_PA;
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1 & AFIO_EXTICR1_EXTI1_PA;
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2 & AFIO_EXTICR1_EXTI2_PA;
	AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3 & AFIO_EXTICR1_EXTI3_PA;
	
	//Set rising edge trigger
	EXTI->RTSR |= EXTI_FTSR_TR0 | EXTI_RTSR_TR1 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3;
	
	//Mask out interrupt line
	EXTI->IMR  |= EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR2 | EXTI_IMR_MR3; 	
}