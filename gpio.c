#include "gpio.h"


void init_gpio()
{
	//Enable clock to AFIO registers
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	//Disable primary jtag functions  from PB3 and PB4 writing in AFIO_MAPR in bits SWJ_CFG = 010;
	AFIO->MAPR = AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
	
	
	/*
	***************************************************************************CONFIGURE PORT A**************************************************
	**********************************************************************************************************************************************
	*/
	
	//ENABLE CLOCK TO PORTA
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	
	
	//CONFIGURE  PULL DOWN INPUTS
	
	//PA0 = BTN1
	//PA1 = BTN2
	//PA2 = BTN3
	//PA3 = BTN_START
	GPIOA->CRL |= (GPIO_CRL_MODE0  | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3);
	GPIOA->CRL |= (GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF2_1);
	GPIOA->BRR &= (GPIO_ODR_ODR0 | GPIO_ODR_ODR1 | GPIO_ODR_ODR2 | GPIO_ODR_ODR3);
	//GPIOA->BRR = (uint32_t)(PIN_0 | PIN_1 | PIN_2 | PIN_3);		/*set pull down*/
	
	
	
	/****CONFIGURE  PUSHPULL OUTPUTS*******************************************************************/
	
	//PA4 = BCD3_A
	//PA5 = BCD3_B
	//PA6 = BCD3_C
	//PA7 = BCD3_D
	GPIOA->CRL |= (GPIO_CRL_MODE4_0 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE7_0);
	GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
	
	//PA8  = BCD1_A
	//PA9  = BCD1_B
	//PA10 = BCD1_C
	//PA11 = BCD1_D
	GPIOA->CRH |= (GPIO_CRH_MODE8_0 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE10_0 |GPIO_CRH_MODE11_0);
	GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_CNF9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF11);
	/**************************************************************************************************/
	
	/*
	********************************************************************CONFIGURE PORTB**************************************************
	**************************************************************************************************************************************
	*/
	
	/*****ENABLE CLOCK FOR PORTB****************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	/********************************************/
	
	
	
	/*****CONFIGURE OUTPUT PUSH PULL***********/ 
	//PB8 = DISP_RESET
	GPIOB->CRH |= GPIO_CRH_MODE8_0;
	GPIOB->CRH &= ~(GPIO_CRH_CNF8);
	//Set pin to high (active low)
	GPIOB->BSRR |= DISP_RST;
	/******************************************/
	
	
	/****CONFIGURE OUTPUT PUSH PULL*********************************************************************************************************/ 
	//PB3 = BCD2_A
	//PB4 = BCD2_B
	//PB5 = BCD2_C
	//PB6 = BCD2_D
	//PB7 = BUZZER
	//PB1 = UV_RELAY
	GPIOB->CRL |= (GPIO_CRL_MODE1_0 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE4_0 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE7_0);
	GPIOB->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_CNF3 | GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);
	/*****************************************************************************************************************************************/
	
	/*
	***********************************************************************CONFIGURE PORT C*********************************************************************
	************************************************************************************************************************************************************
	*/
	
	
	/*****ENABLE CLOCK TO GPIOC***************/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	/*****************************************/

	
	/*****SET PIN13 (LED) ON PORT C AS OUTPUT PUSH PULL****/
	GPIOC->CRH |= GPIO_CRH_MODE13_0;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);
	//set LED off
	GPIOC->ODR  |= PIN_13;
	/*******************************************************/

	
}

void setPin(GPIO_TypeDef* port, uint32_t pin)
{
	port->BSRR |= pin;
}

void resetPin(GPIO_TypeDef* port, uint32_t pin)
{
	port->BSRR |= pin << 16;
}

void togglePin(GPIO_TypeDef* port, uint32_t pin)
{
	port->ODR ^= pin;
}

void ledOn()
{
	resetPin(GPIOC, LED);
}

void ledOff()
{
	setPin(GPIOC, LED);
}

void toggleLed()
{
	GPIOC->ODR ^= LED;
}


uint32_t readButton1()
{
	uint32_t tmp = ((GPIOA->IDR & PIN_0) >> 0);
	return tmp;
}
uint32_t readButton2()
{
	uint32_t tmp = ((GPIOA->IDR & PIN_0) >> 1);
	return tmp;
}
uint32_t readButton3()
{
	uint32_t tmp = ((GPIOA->IDR & PIN_0) >> 2);
	return tmp;
}
uint32_t readButtonStart()
{
	uint32_t tmp = ((GPIOA->IDR & PIN_0) >> 3);
	return tmp;
}
