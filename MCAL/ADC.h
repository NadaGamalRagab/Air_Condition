/*
 * ADC.h
 *
 *  Created on: 18 Aug 2020
 *      Author: Belal_Elmahdy
 */

#ifndef ADC_H_
#define ADC_H_

#include "DIO.h"
#include <avr/interrupt.h>

#define Interrupt 1

void ADC_init();
uint16_t ADC_read(uint8_t Channel);


#endif /* ADC_H_ */
