/*
 * Main.c
 *
 *  Created on: 18 Aug 2020
 *      Author: Belal_Elmahdy
 */


#include "../HAL/LCD.h"
#include "../HAL/KeyPad.h"
#include "../MCAL/ADC.h"
#include "../MCAL/Timer2_delay.h"
#include "../MCAL/EEPROM.h"

uint8_t Current_Temp=0;
uint8_t Max = 0;
uint8_t Min = 0;
uint8_t keypressed = 0 ;
uint16_t temp=0;
//uint8_t Desired_Temp = 30;

uint8_t Current[] = "Current Temp:";
uint8_t Desired[] ="Desired Temp:";
uint8_t MAX[] =" MAX:";
uint8_t MIN[] ="  MIN:";

uint8_t Stop_Buzzer_Flag =0;
uint8_t count1=2;
uint8_t count2=2;

ISR(ADC_vect)
{
	temp = ADC;
}

ISR(TIMER2_OVF_vect)
{
	static uint8_t count =0;
	count++;

	/*delay 1 sec using Timer2*/
	if(count == 31)
	{
		ADC_read(0);

		Current_Temp = temp * (500.0/1023.0);
		count =0;
	}
}

ISR(INT0_vect)
{
	Stop_Buzzer_Flag =1;
}

ISR(INT1_vect)
{
	LCD_Clear_Display();
	count1 = 2;
	count2 = 2;
	while(count1 >0)
	{
		LCD_GoTO_Row_Colunmn(0,0);
		LCD_Write_String(MAX);
		while(keypad_get_pressed_key()==0);

		keypressed = keypad_get_pressed_key();

		if(count1 == 2)
		{
			//LCD_Clear_Display();
			//LCD_GoTO_Row_Colunmn(0,0);
			//LCD_write_num(keypressed);
			Max = keypressed*10;
			count1--;
		}
		else if(count1 ==1)
		{
			//LCD_write_num(keypressed);
			Max += keypressed;
			EEPROM_write(3 , Max);
			break;
		}
		_delay_ms(300);
	}
	LCD_write_num(Max);
	_delay_ms(300);
	LCD_Clear_Display();
	while(count2 >0)
	{
		LCD_GoTO_Row_Colunmn(0,0);
		LCD_Write_String(MIN);
		while(keypad_get_pressed_key()==0);
		keypressed = keypad_get_pressed_key();

		if(count2 ==2 )
		{
			//LCD_write_num(keypressed);
			Min = keypressed*10;
			count2--;
		}
		else if(count2 ==1)
		{
			//LCD_write_num(keypressed);
			Min += keypressed;
			EEPROM_write(4 , Min);
			break;
		}
		_delay_ms(300);
	}
	LCD_write_num(Min);
	_delay_ms(300);
	LCD_Clear_Display();

}


int main()
{

	uint8_t Warning[] = "Warning";

	/*Relay 2 pins 2 => Cooling | 3 => Heating*/
	SET_BIT(DDRC , 2);
	SET_BIT(DDRC , 3);

	/*Buzzer*/
	SET_BIT(DDRD , 7);

	/*External Buttons*/
	//INT0
	CLEAR_BIT(DDRD , 2);
	SET_BIT(PORTD ,2);
	//INT1
	CLEAR_BIT(DDRD , 3);
	SET_BIT(PORTD ,3);

	/*Initialization*/
	LCD_init();
	keypad_init();
	ADC_init();
	Timer2_init();

	/*External interrupts*/
	SET_BIT(MCUCR,ISC10);
	CLEAR_BIT(MCUCR,ISC11);

	SET_BIT(MCUCR,ISC00);
	CLEAR_BIT(MCUCR,ISC01);

	SET_BIT(GICR,INT0);
	SET_BIT(GICR,INT1);
	SET_BIT(SREG,7);

	/*Default Values*/
	EEPROM_write(3 , 33);
	EEPROM_write(4 , 29);

	Max = EEPROM_read(3);
	Min = EEPROM_read(4);

	while(1)
	{
		/*Temperature Sensor Channel*/
		ADC_read(5);

		if (Current_Temp > (Max) )
		{

			SET_BIT(PORTC , 2);
			CLEAR_BIT(PORTC , 3);

			/*Interrupt Button for user*/
			if(Stop_Buzzer_Flag ==0)
			{
				SET_BIT(PORTD , 7);

				LCD_Clear_Display();
				LCD_GoTO_Row_Colunmn(0,0);
				LCD_Write_String(Warning);
				LCD_Write_String(MAX);
				LCD_write_num(Max);
				LCD_GoTO_Row_Colunmn(1,0);
				LCD_Write_String(Current);
				LCD_write_num(Current_Temp);

				_delay_ms(100);
			}
			else
			{
				CLEAR_BIT(PORTD , 7);

				LCD_GoTO_Row_Colunmn(0,0);
				LCD_Write_String(Current);
				LCD_write_num(Current_Temp);
				LCD_GoTO_Row_Colunmn(1,0);
				LCD_Write_String(MAX);
				LCD_write_num(Max);
				LCD_Write_String(MIN);
				LCD_write_num(Min);

				_delay_ms(50);
			}

		}
		else if(Current_Temp < (Min))
		{
			CLEAR_BIT(PORTC , 2);
			SET_BIT(PORTC , 3);

			/*Interrupt Button for user*/
			if(Stop_Buzzer_Flag ==0)
			{
				SET_BIT(PORTD , 7);

				LCD_Clear_Display();
				LCD_GoTO_Row_Colunmn(0,0);
				LCD_Write_String(Warning);
				LCD_Write_String(MIN);
				LCD_write_num(Min);
				LCD_GoTO_Row_Colunmn(1,0);
				LCD_Write_String(Current);
				LCD_write_num(Current_Temp);

				_delay_ms(100);
			}
			else
			{
				CLEAR_BIT(PORTD , 7);

				LCD_GoTO_Row_Colunmn(0,0);
				LCD_Write_String(Current);
				LCD_write_num(Current_Temp);
				LCD_GoTO_Row_Colunmn(1,0);
				LCD_Write_String(MAX);
				LCD_write_num(Max);
				LCD_Write_String(MIN);
				LCD_write_num(Min);

				_delay_ms(50);
			}

		}
		else
		{
			/*Normal Mode*/
			CLEAR_BIT(PORTC , 2);
			CLEAR_BIT(PORTC , 3);
			CLEAR_BIT(PORTD , 7);

			LCD_GoTO_Row_Colunmn(0,0);
			LCD_Write_String(Current);
			LCD_write_num(Current_Temp);
			LCD_GoTO_Row_Colunmn(1,0);
			LCD_Write_String(MAX);
			LCD_write_num(Max);
			LCD_Write_String(MIN);
			LCD_write_num(Min);

			Stop_Buzzer_Flag =0;
		}
		//		LCD_GoTO_Row_Colunmn(0,0);
		//		LCD_Write_String(Current);
		//		LCD_write_num(Current_Temp);
		//		LCD_GoTO_Row_Colunmn(1,0);
		//		LCD_Write_String(Desired);
		//		LCD_write_num(Desired_Temp);

		_delay_ms(50);
	}
}
