#include "timer.h"
#include "stm32f10x.h"                  // Device header


void timer_init()
{
	//enable clock to tim2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	//set prescalar
	TIM2->PSC = 999;
	
	//Auto-reload value
	TIM2->ARR = 8000;
	
	//Enable timer interrupt
	TIM2->DIER |= TIM_DIER_UIE;
}

void timer_start()
{
	//enable counter register
	TIM2->CR1 |= TIM_CR1_CEN;
}