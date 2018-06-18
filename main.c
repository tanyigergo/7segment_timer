#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "main.h"
#include "Delay.h"
#include "7_segment.h"
#include "int.h"
#include "exti.h"
#include "timer.h"



volatile uint32_t btn1, btn2, btn3, btnStart;

uint8_t disp1_value = 0;
uint8_t disp2_value = 0;
uint8_t disp3_value = 0;


typedef enum {RESET_STATE, 
	      FLASHING_STATE, 
	      COUNTDOWN_STATE,
	      ALARM_STATE} FSM_Type;
uint8_t currentState = RESET_STATE;

bool timerEndFlag = false;

int main()
{
	init_gpio();
	timer_init();
	exti_init();
	interruptInit();
	
	SysTick_Config(SystemCoreClock/1000);

	writeToDisplay(DISP1, 0);
	writeToDisplay(DISP2, 0);
	writeToDisplay(DISP3, 0);
	
	while(1)
	{
		
		switch(currentState)
		{
			case RESET_STATE:
				NVIC_EnableIRQ(EXTI0_IRQn);
				NVIC_EnableIRQ(EXTI1_IRQn);
				NVIC_EnableIRQ(EXTI2_IRQn);
				NVIC_EnableIRQ(EXTI3_IRQn);
			break;
			
			case FLASHING_STATE:				
				NVIC_DisableIRQ(EXTI0_IRQn);
				NVIC_DisableIRQ(EXTI1_IRQn);
				NVIC_DisableIRQ(EXTI2_IRQn);
				NVIC_DisableIRQ(EXTI3_IRQn);
			
				//Flash displays before countdown
				for(int i = 0; i < 10; i++)
				{
					
					resetDisplay(DISP1);
					resetDisplay(DISP2);
					resetDisplay(DISP3);
									
					writeToDisplay(DISP1, disp1_value);
					writeToDisplay(DISP2, disp2_value);
					writeToDisplay(DISP3, disp3_value);
					
					delay(50);
				}
				
				currentState = COUNTDOWN_STATE;				
			break;
			
			case COUNTDOWN_STATE:				
				setPin(GPIOB, UV_RLY);
				timer_start();
			
				if(timerEndFlag == true)
				{
					resetPin(GPIOB, UV_RLY);
					currentState = ALARM_STATE;
				}				
			break;
				
				
			case ALARM_STATE:				
				//Turn on/off buzzer 3 times
				for(int i = 0; i < 3; i++)
				{
					setPin(GPIOB, BUZZER);
					delay(500);
					resetPin(GPIOB, BUZZER);
					delay(500);
				}		
				currentState = RESET_STATE;
				
				//Reset everything to initial values
				writeToDisplay(DISP1, 0);
				writeToDisplay(DISP2, 0);
				writeToDisplay(DISP3, 0);
				
				disp1_value = 0;
			        disp2_value = 0;
				disp3_value = 0;
				
				timerEndFlag = false;					
			break;
		}
	}

	return 0;
}





void TIM2_IRQHandler()
{
	if(TIM2->SR & TIM_SR_UIF)
	{
		writeToDisplay(DISP1, disp1_value);
		writeToDisplay(DISP2, disp2_value);
		writeToDisplay(DISP3, disp3_value);
		
		//If timer reaches zero
		if (disp1_value == 0 && disp2_value == 0 && disp3_value == 0)
		{
			//Turn off timer
			TIM2->CR1 &= ~TIM_CR1_CEN;
			
			//Turn off UV LED matrix
			resetPin(GPIOB, UV_RLY);
			
			timerEndFlag = true;
		}
		
	
		//Decrement display1 if its not 0
		else if(disp1_value > 0)
		{
			disp1_value--;
		}
		
		//if display1 is 0 but tens are not 0
		else if(disp1_value == 0 &&  disp2_value > 0)
		{
			disp1_value = 9;
			disp2_value--;
		}
		
		//if display2 and display1 are both zero but display3 is not 0
		else if(disp1_value == 0 && disp2_value == 0 && disp3_value > 0)
		{
			disp1_value = 9;
			disp2_value = 5;
			disp3_value--;
		}
		


	}
	
	TIM2->SR &= ~TIM_SR_UIF;	//clear interrupt flag
}



void EXTI0_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR0)
	{
		disp1_value++;
		disp1_value = disp1_value % 10;
		writeToDisplay(DISP1, disp1_value);
		EXTI->PR |= EXTI_PR_PR0 ;		
	}	
	
	for(int i = 0; i < 10000; i++){} 
}



void EXTI1_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR1)
	{
		disp2_value++;
		disp2_value = disp2_value % 6;
		writeToDisplay(DISP2, disp2_value);
		EXTI->PR |= EXTI_PR_PR1 ;		
	}	
	
	for(int i = 0; i < 10000; i++){} 
}



void EXTI2_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR2)
	{
		disp3_value++;
		disp3_value = disp3_value % 10;
		writeToDisplay(DISP3, disp3_value);
		EXTI->PR |= EXTI_PR_PR2 ;		
	}
	
	for(int i = 0; i < 10000; i++){} 
}



void EXTI3_IRQHandler()
{
	if(EXTI->PR & EXTI_PR_PR3)
	{
		currentState = FLASHING_STATE;
		EXTI->PR |= EXTI_PR_PR3 ;		
	}

}

