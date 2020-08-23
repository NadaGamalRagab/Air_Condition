/*
 * LCD.c
 *
 *  Created on: 18 Aug 2020
 *      Author: Belal_Elmahdy
 */

#include "LCD.h"

//4-bit Mode
void LCD_init()
{
	LCD_CTRL_PORT_DIR_RS |= (1<<RS);
	LCD_CTRL_PORT_DIR_EN |=(1<<EN);

	LCD_DATA_PORT_DIR |= 0x0F;
	LCD_Write_Command(ReturnHome);
	LCD_Write_Command(_4BIT_2LINE);
	_delay_ms(1);
	LCD_Write_Command(CLEAR_DISPLAY);
	LCD_Write_Command(DISPLAY_ON_CURSOR_OFF);

}

void LCD_Clear_Display(void)
{
	LCD_Write_Command(CLEAR_DISPLAY);
}

void LCD_GoTO_Row_Colunmn(char Row,char Column)
{
	uint8_t address = 0;

	switch(Row)
	{
	case 0 : address = (Column);break;
	case 1 : address = (Column +0x40);break;
	//for bigger LCDs
	case 2:address =(Column+0x10);break;
	case 3:address =(Column+0x50);break;

	}

	/* we need to apply the corresponding command 0b10000000+Address */
	LCD_Write_Command(address|(SET_CURSOR_LOCATION));
}

void LCD_Write_Command(uint8_t command)
{
	LCD_CTRL_PORT_RS &=~(1<<RS); // command mode
	_delay_ms(1);
	LCD_CTRL_PORT_EN |=(1<<EN);
	_delay_ms(1);
	/*The most bits*/
	/* Clearing Data Port  For new Data*/
	LCD_DATA_PORT &= (0xF0);
	/* Shift command right to send the most bits and 0x0F to use the port 4 bits only*/
	LCD_DATA_PORT |=((command>>4)&0x0F);
	LCD_CTRL_PORT_EN &=~(1<<EN);
	_delay_ms(1);

	LCD_CTRL_PORT_RS &=~(1<<RS); // command mode
	_delay_ms(1);
	LCD_CTRL_PORT_EN |=(1<<EN);
	_delay_ms(1);
	/*The least bits*/
	/* Clearing Data Port  For new Data*/
	LCD_DATA_PORT &= (0xF0);
	/* send the command means sending the least bits and 0x0F to use the port 4 bits only*/
	LCD_DATA_PORT |=((command)&0x0F);
	LCD_CTRL_PORT_EN &=~(1<<EN);
	_delay_ms(1);

}
void LCD_Write_Char(uint8_t character)
{
	LCD_CTRL_PORT_RS |=(1<<RS); // Data mode
	_delay_ms(1);
	LCD_CTRL_PORT_EN |=(1<<EN);
	_delay_ms(1);

	/* Clearing Data Port  For new Data*/
	LCD_DATA_PORT &= (0xF0);
	/* Shift character right to send the most bits and 0x0F to use the port 4 bits only*/
	LCD_DATA_PORT |=((character >> 4) & 0x0F);
	LCD_CTRL_PORT_EN &=~(1<<EN);
	_delay_ms(1);

	LCD_CTRL_PORT_RS |=(1<<RS); // Data mode
	LCD_CTRL_PORT_EN |=(1<<EN);
	_delay_ms(1);
	/* Clearing Data Port  For new Data*/
	LCD_DATA_PORT &= (0xF0);
	/* send the character means sending the least bits and 0x0F to use the port 4 bits only*/
	LCD_DATA_PORT |=(character & 0x0F);
	LCD_CTRL_PORT_EN &=~(1<<EN);
	_delay_ms(1);

}
void LCD_Write_String(uint8_t* txt)
{
	int i =0;
	for(i=0 ; txt[i] != '\0' ; i++ )
	{
		LCD_Write_Char(txt[i]);
	}

}
/*
 * for remembering :)
1234 %10 --> 4
1234 / 10 = 123

123%10 --> 3
123/10 = 12

12%10 --> 2
12/10 = 1

1%10 --> 1
1/10 = 0




1 2 3 4
1+48
2+48
3+48
4+48

 */
void LCD_write_num(uint16_t num)
{
	uint8_t txt[10] = {0};
	int8_t i = 0;
	if(num == 0)
	{
		LCD_Write_Char('0');
		return;
	}
	for (i = 0; num != 0; i++ )
	{
		txt[i] = num%10 + 48;
		num = num  / 10 ;
	}
	i--;
	while(i >= 0)
	{
		LCD_Write_Char(txt[i]);
		i--;
	}

}
