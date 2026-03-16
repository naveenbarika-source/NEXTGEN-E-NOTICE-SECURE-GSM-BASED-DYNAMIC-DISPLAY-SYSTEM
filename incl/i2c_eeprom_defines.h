//i2c_eeprom_defines.h

#ifndef I2C_EEPROM_DEFINES_H
#define I2C_EEPROM_DEFINES_H


/*---------------------------------------------------------
I2C EEPROM Slave Addresses (7-bit addressing)

These addresses are used to communicate with I2C EEPROM.
Depending on the hardware configuration (A0, A1, A2 pins),
the EEPROM slave address can range from 0x50 to 0x57.
----------------------------------------------------------*/

#define I2C_EEPROM_SA1 0x50   // EEPROM Slave Address 1
#define I2C_EEPROM_SA2 0x51   // EEPROM Slave Address 2
#define I2C_EEPROM_SA3 0x52   // EEPROM Slave Address 3
#define I2C_EEPROM_SA4 0x53   // EEPROM Slave Address 4
#define I2C_EEPROM_SA5 0x54   // EEPROM Slave Address 5
#define I2C_EEPROM_SA6 0x55   // EEPROM Slave Address 6
#define I2C_EEPROM_SA7 0x56   // EEPROM Slave Address 7
#define I2C_EEPROM_SA8 0x57   // EEPROM Slave Address 8


/*---------------------------------------------------------
EEPROM Memory Locations

These locations are used to store important data such as
authorized mobile number and SMS message content.
----------------------------------------------------------*/

#define EE_MOBI  0x00   // EEPROM starting index for storing mobile number
#define EE_MOB   0x01   // EEPROM location where mobile number begins

#define EE_MSGI  0x14   // EEPROM starting index for message storage
#define EE_MSG   0x15   // EEPROM location where message begins


#endif

