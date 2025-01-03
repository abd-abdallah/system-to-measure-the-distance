/*
 * icu.h
 *
 *  Created on: Oct 11, 2022
 *      Author: AbdElRuhman
 */

#ifndef ICU_H_
#define ICU_H_

#include "gpio.h"

typedef enum{
	noClock,noPre,pre8,pre64,pre256,pre1024
}type_pre;


typedef enum{
	falling,rising
}type_edge;


typedef struct{
	type_pre prescaler;
	type_edge edge;
}config_ICU;


void Icu_init(const config_ICU *ptr_config);

void Icu_setCallBackFun(void(*ptr_fun)(void));

void Icu_setTyepEdge(const type_edge typeEdge);


uint16 Icu_getInputCaptureValue(void);

void Icu_clearTimerValue(void);

void Icu_DiInit(void);
#endif /* ICU_H_ */
