/*
 * LCD.h
 *
 *  Created on: 18 Aug 2020
 *      Author: Belal_Elmahdy
 */

#ifndef LCD_H_
#define LCD_H_

#include "../MCAL/DIO.h"

#define RS PA3
#define EN PD6

#define LCD_CTRL_PORT_DIR_RS (DDRA)
#define LCD_CTRL_PORT_RS (PORTA)
#define LCD_CTRL_PORT_DIR_EN (DDRD)
#define LCD_CTRL_PORT_EN (PORTD)
#define LCD_DATA_PORT (PORTB)
#define LCD_DATA_PORT_DIR (DDRB)

#define _8BIT_2LINE (0x38)
#define _4BIT_2LINE (0x28)
#define DISPLAY_ON_CURSOR_ON (0x0E)
#define DISPLAY_ON_CURSOR_OFF (0x0C)
#define CLEAR_DISPLAY (0x01)
#define SET_CURSOR_LOCATION (0x80)
#define ReturnHome (0x02)

void LCD_init();
void LCD_Clear_Display(void);
void LCD_GoTO_Row_Colunmn(char Row,char Column);
void LCD_Write_Command(uint8_t command);
void LCD_Write_Char(uint8_t data);
void LCD_Write_String(uint8_t* txt);
void LCD_write_num(uint16_t num);


#endif /* LCD_H_ */
