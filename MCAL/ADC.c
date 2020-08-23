/*
 * ADC.c
 *
 *  Created on: 18 Aug 2020
 *      Author: Belal_Elmahdy
 */

#include "ADC.h"

void ADC_init()
{
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADCSRA,ADEN);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
#if Interrupt ==1
	SET_BIT(ADCSRA,ADIE);
	sei();
#endif

}

uint16_t ADC_read(uint8_t Channel)
{
#if Interrupt ==0
	//ADMUX &=0xE0; // clear least 5 bits (channel)
	CLEAR_BIT(ADMUX,MUX0);
	CLEAR_BIT(ADMUX,MUX1);
	CLEAR_BIT(ADMUX,MUX2);
	CLEAR_BIT(ADMUX,MUX3);
	CLEAR_BIT(ADMUX,MUX4);
	Channel &=0x07; //reassignation for the input argument
	ADMUX |=Channel; // start conversion
	
	ADCSRA |=(1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return ADC;
#elif Interrupt ==1
	if(Channel <= 7 && Channel >=0)
	{
		ADMUX &= 0xE0; // clear least 5 bits (channel)
		ADMUX |= Channel;
		ADCSRA |=(1<<ADSC); // start conversion
	}
	return 0;
#endif
}
