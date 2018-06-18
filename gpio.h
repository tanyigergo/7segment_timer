#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H




#include "stm32f10x.h"
#include "main.h"
#include <stdint.h>

#define PIN_0 	(uint32_t)(1UL << 0)
#define PIN_1 	(uint32_t)(1UL << 1)
#define PIN_2 	(uint32_t)(1UL << 2)
#define PIN_3 	(uint32_t)(1UL << 3)
#define PIN_4 	(uint32_t)(1UL << 4)
#define PIN_5 	(uint32_t)(1UL << 5)
#define PIN_6 	(uint32_t)(1UL << 6)
#define PIN_7 	(uint32_t)(1UL << 7)
#define PIN_8 	(uint32_t)(1UL << 8)
#define PIN_9 	(uint32_t)(1UL << 9)
#define PIN_10 	(uint32_t)(1UL << 10)
#define PIN_11 	(uint32_t)(1UL << 11)
#define PIN_12	(uint32_t)(1UL << 12)
#define PIN_13	(uint32_t)(1UL << 13)
#define PIN_14	(uint32_t)(1UL << 14)
#define PIN_15 	(uint32_t)(1UL << 15)


void init_gpio();

void setPin(GPIO_TypeDef* port, uint32_t pin);
void resetPin(GPIO_TypeDef* port, uint32_t pin);
void togglePin(GPIO_TypeDef* port, uint32_t pin);

void ledOn();
void ledOff();
void toggleLed();

uint32_t readButton1();
uint32_t readButton2();
uint32_t readButton3();
uint32_t readButtonStart();

#endif

