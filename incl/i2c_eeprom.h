//i2c_eeprom.h

#ifndef I2C_EEPROM_H

#define I2C_EEPROM_H


#include "types.h"


/*void i2c_eeprom_bytewrite(u8 slaveAddr,

	                        u8 wBufAddr,

                          u8 dat) ;

u8 i2c_eeprom_randomread(u8 slaveAddr,

                         u8 rBufAddr);*/ 

void EEPROM_Write(u8 slaveAddr,

	                        u16 wBufStartAddr,

                          u8 *p,

                          u8 nBytes) ;


void EEPROM_Reed(u8 slaveAddr,

	                      u16 rBufStartAddr,

                        u8 *p,

                        u8 nBytes); 

u8 i2c_eeprom_randomread(u8 slaveAddr,
                         u8 rBufAddr);


void i2c_eeprom_bytewrite(u8 slaveAddr,
                                u8 wBufAddr,
                          u8 dat);


#endif
