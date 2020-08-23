/*
 * KeyPad.h
 *
 *  Created on: 5 May 2019
 *      Author: Belal Elmahdy
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../MCAL/DIO.h"
#include <util/delay.h>
#include <avr/io.h>

//Rows of keypad
#define KEYPAD_PORT_DIR_R DDRA
#define KEYPAD_PORT_OUT_R PORTA
#define KEYPAD_PORT_IN_R PINA

//columns of keypad
#define KEYPAD_PORT_DIR_C DDRC
#define KEYPAD_PORT_OUT_C PORTC
#define KEYPAD_PORT_IN_C PINC

//Number of pins
#define FIRST_ROW (2)
#define SECOND_ROW (1)
#define THIRD_ROW (0)

//Number of pins
#define FIRST_COL (5)
#define SECOND_COL (6)
#define THIRD_COL (7)

void keypad_init (void);
uint8_t keypad_get_pressed_key(void);


#endif /* KEYPAD_H_ */
