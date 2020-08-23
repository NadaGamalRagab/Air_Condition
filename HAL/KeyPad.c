/*
 * KeyPad.c
 *
 *  Created on: 5 May 2019
 *      Author: Belal Elmahdy
 */

#include "KeyPad.h"



/* * * *c1  c2 c3
 * row1  1  2  3
 * row2  4  5  6
 * row3  7  8  9
 */

void keypad_init (void)
{
	// Set columns as output and rows are input
	KEYPAD_PORT_DIR_R &= 0xF8;
	KEYPAD_PORT_DIR_C |= 0xE0;

	// Pull up resistor
	SET_BIT(KEYPAD_PORT_OUT_R,FIRST_ROW);
	SET_BIT(KEYPAD_PORT_OUT_R,SECOND_ROW);
	SET_BIT(KEYPAD_PORT_OUT_R,THIRD_ROW);

	SET_BIT(KEYPAD_PORT_OUT_C,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,THIRD_COL);
}

uint8_t keypad_get_pressed_key(void)
{
	uint8_t KeyPressed =0  ;

	_delay_ms(5);

	//Make first column input in port register and make other columns output
	CLEAR_BIT(KEYPAD_PORT_OUT_C,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,THIRD_COL);

	_delay_ms(5);

	//check if switch is pushed and when it pushed it read 0
	//so we check if the bit is cleared =0
	if (BIT_CLEARED(KEYPAD_PORT_IN_R,FIRST_ROW))
	{
		KeyPressed = 1;
	}
	else if (BIT_CLEARED(KEYPAD_PORT_IN_R,SECOND_ROW))
	{
		 KeyPressed = 4;
	}
	else if(BIT_CLEARED(KEYPAD_PORT_IN_R,THIRD_ROW))
	{
		 KeyPressed = 7;
	}

	_delay_ms(5);

	//Make Second column input in port register and make other columns output
	CLEAR_BIT(KEYPAD_PORT_OUT_C,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,THIRD_COL);

	_delay_ms(5);

	if (BIT_CLEARED(KEYPAD_PORT_IN_R,FIRST_ROW))
	{
		 KeyPressed = 2;
	}
	else if (BIT_CLEARED(KEYPAD_PORT_IN_R,SECOND_ROW))
	{
		 KeyPressed = 5;
	}
	else if(BIT_CLEARED(KEYPAD_PORT_IN_R,THIRD_ROW))
	{
		 KeyPressed = 8;
	}

	_delay_ms(5);

	//Make third column input in port register and make other columns output
	CLEAR_BIT(KEYPAD_PORT_OUT_C,THIRD_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT_C,SECOND_COL);

	_delay_ms(5);

	if (BIT_CLEARED(KEYPAD_PORT_IN_R,FIRST_ROW))
	{
		 KeyPressed = 3;
	}
	else if (BIT_CLEARED(KEYPAD_PORT_IN_R,SECOND_ROW))
	{
		 KeyPressed = 6;
	}
	else if(BIT_CLEARED(KEYPAD_PORT_IN_R,THIRD_ROW))
	{
		 KeyPressed = 9;
	}

	return KeyPressed;
}
