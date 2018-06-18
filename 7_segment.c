#include "7_segment.h"
#include "main.h"
#include "gpio.h"
#include "Delay.h"


/**
  * @brief  This function reset all LEDs on display
  * @param  display: the display to be reset
  * @retval None
  */
void resetDisplay (eDisplay display)
{
	//set output pin DISP_RESET to 0, this clears all display
		
	resetPin(GPIOB, DISP_RST);
	delay(10);
	setPin(GPIOB, DISP_RST);

}


/**
  * @brief  Sends BCD code to 7 segment display driver
  * @param  BCD_DRIVER displayNumber: display to write to
  *	    char digit: digit to be written
  * @retval None
  */
void writeToDisplay (eDisplay display, char digit)
{
	//creates BCD code from digit where "a" is LSB
	char a, b, c, d;
	a = ( digit & 0x01 ) >> 0;
	b = ( digit & 0x02 ) >> 1;
	c = ( digit & 0x04 ) >> 2;
	d = ( digit & 0x08 ) >> 3;
	
	//sends the converted BCD to the corresponding display driver
	switch (display)
	{
		//BCD code to GPIO pins PA8, PA9, PA10, PA11
		case DISP1:
			(a) ? setPin(GPIOA, BCD1_A) : resetPin(GPIOA, BCD1_A);
			(b) ? setPin(GPIOA, BCD1_B) : resetPin(GPIOA, BCD1_B);
			(c) ? setPin(GPIOA, BCD1_C) : resetPin(GPIOA, BCD1_C);
			(d) ? setPin(GPIOA, BCD1_D) : resetPin(GPIOA, BCD1_D);
			break;
		
		//BCD code to GPIO pins PB3, PB4, PB5, PB6
		case DISP2:
			(a) ? setPin(GPIOB, BCD2_A) : resetPin(GPIOB, BCD2_A);
			(b) ? setPin(GPIOB, BCD2_B) : resetPin(GPIOB, BCD2_B);
			(c) ? setPin(GPIOB, BCD2_C) : resetPin(GPIOB, BCD2_C);
			(d) ? setPin(GPIOB, BCD2_D) : resetPin(GPIOB, BCD2_D);
			break;
		
		//BCD code to GPIO pins PA4, PA5, PA6, PA7
		case DISP3:
			(a) ? setPin(GPIOA, BCD3_A) : resetPin(GPIOA, BCD3_A);
			(b) ? setPin(GPIOA, BCD3_B) : resetPin(GPIOA, BCD3_B);
			(c) ? setPin(GPIOA, BCD3_C) : resetPin(GPIOA, BCD3_C);
			(d) ? setPin(GPIOA, BCD3_D) : resetPin(GPIOA, BCD3_D);
			break;
	}
	
	
}

