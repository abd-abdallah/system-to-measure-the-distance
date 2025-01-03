/*
 * icu.c
 *
 *  Created on: Oct 11, 2022
 *      Author: AbdElRuhman
 */



#include "icu.h"

static volatile void (*ptr_funCallBabk)(void)=NULL_PTR;

ISR(TIMER1_CAPT_vect)
{
	if(ptr_funCallBabk != NULL_PTR)
	{
		(*ptr_funCallBabk)();
	}
}


void Icu_init(const config_ICU *ptr_config)
{
	DDRD &= ~(1<<PD6);


	TCCR1A=(1<<FOC1A) |(1<<FOC1B);
//	TCCR1B=(1<<ICNC1);

	TCCR1B= (TCCR1B & 0xBF) |((ptr_config->edge)<<6);

	TCCR1B =(TCCR1B & 0xF8) |(ptr_config->prescaler);

	TCNT1=0;
	ICR1=0;

	TIMSK=(1<<TICIE1);
}

void Icu_setCallBackFun(void (*ptr_fun)(void))
{
	ptr_funCallBabk=ptr_fun;
}


void Icu_setTyepEdge(const type_edge typeEdge)
{
	TCCR1B= (TCCR1B & 0xBF) |(typeEdge<<6);
}


uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}

void Icu_clearTimerValue(void)
{
	TCNT1=0;
}

void Icu_DiInit(void)
{
	TCCR1A=0;
	TCCR1B=0;

	TCNT1=0;
	ICR1=0;



	TIMSK &= ~(1<<TICIE1);

}




