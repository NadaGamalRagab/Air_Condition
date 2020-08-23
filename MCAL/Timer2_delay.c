/*
 * Timer2_delay.c
 *
 *  Created on: 19 Aug 2020
 *      Author: Belal_Elmahdy
 */

#include "Timer2_delay.h"

void Timer2_init()
{
	TCCR2=(1<<FOC2)|(1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK = (1<<TOIE2);
	sei();
	TCNT2=0;
}
