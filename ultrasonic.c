/*
 * ultrasonic.c
 *
 *  Created on: Oct 13, 2022
 *      Author: AbdElRuhman
 */

#include "ultrasonic.h"
#include "icu.h"
#include <util/delay.h>
#include "gpio.h"

uint8 g_countEdge=0;
uint16 g_timeHigh=0;


config_ICU configICU={pre8,rising};


void Ultrasonic_init(void)
{
	GPIO_setupPinDirection(PORTD_ID,PIN5_ID,PIN_OUTPUT);

	Icu_init(&configICU);

	Icu_setCallBackFun(Ultrasonic_edgeProcessing);
}



void Ultrasonic_Trigger(void)
{
	GPIO_writePin(PORTD_ID,PIN5_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(PORTD_ID,PIN5_ID,LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	return ((float)(g_timeHigh/58.8));

}

void Ultrasonic_edgeProcessing(void)
{
	g_countEdge++;
	if(g_countEdge==1)
	{

		Icu_clearTimerValue();
		Icu_setTyepEdge(falling);
	}
	else if(g_countEdge==2)
	{

		g_timeHigh=Icu_getInputCaptureValue();
		Icu_setTyepEdge(rising);
		g_countEdge=0;
	}

}

