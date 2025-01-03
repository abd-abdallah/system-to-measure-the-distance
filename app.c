/*
 * app.c
 *
 *  Created on: Oct 12, 2022
 *      Author: AbdElRuhman Abdallah
 */

#include "ultrasonic.h"
#include "lcd.h"
#include <util/delay.h>
#include "gpio.h"

int main(void)
{
	uint16 distance=0;
	SREG |= (1<<7);

	Ultrasonic_init();
	LCD_init();

	LCD_displayString("Distance= ");
	while(1)
	{
		LCD_moveCursor(0,10);
		distance=Ultrasonic_readDistance();
		LCD_intgerToString(distance);
		LCD_displayString("cm  ");


	}
}

