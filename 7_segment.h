#ifndef __7_SEGMENT_H
#define	__7_SEGMENT_H



/*
**Three one digit seven segment display driver
*/
typedef enum{DISP1, DISP2, DISP3 } eDisplay;


void writeToDisplay (eDisplay display, char digit);
void resetDisplay (eDisplay display);

#endif

