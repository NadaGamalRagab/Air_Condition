/*
 * EEPROM.h
 *
 *  Created on: 21 Aug 2020
 *      Author: Belal_Elmahdy
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "DIO.h"

void EEPROM_write(uint16_t Address,uint8_t Data);
uint8_t EEPROM_read(uint16_t Address);


#endif /* EEPROM_H_ */
