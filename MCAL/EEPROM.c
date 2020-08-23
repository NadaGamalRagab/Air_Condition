/*
 * EEPROM.c
 *
 *  Created on: 21 Aug 2020
 *      Author: Belal_Elmahdy
 */

#include "EEPROM.h"

void EEPROM_write(uint16_t Address,uint8_t Data)
 {
	while(EECR&(1<<EEWE));

	EEAR=Address;
	EEDR=Data;

	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);

 }

uint8_t EEPROM_read(uint16_t Address)
 {
	while(EECR&(1<<EEWE));

	EEAR=Address;

	SET_BIT(EECR,EERE);
	return EEDR;
 }
