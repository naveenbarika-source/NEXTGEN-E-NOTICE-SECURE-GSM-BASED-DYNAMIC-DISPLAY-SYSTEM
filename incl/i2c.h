#ifndef I2C_H
#define I2C_H


#include "types.h"   // Contains user-defined data types such as u8


/*---------------------------------------------------------
Function: init_i2c
Purpose : Initialize the I2C module of the microcontroller

Description:
This function configures the I2C hardware registers and
sets the required clock speed for communication with
I2C devices such as EEPROM.
----------------------------------------------------------*/
void init_i2c(void);


/*---------------------------------------------------------
Function: i2c_start
Purpose : Generate START condition on the I2C bus

Description:
This function initiates communication with an I2C slave
device by sending the START signal.
----------------------------------------------------------*/
void i2c_start(void);


/*---------------------------------------------------------
Function: i2c_restart
Purpose : Generate RESTART condition on the I2C bus

Description:
This function is used when communication with the same
device continues without releasing the bus.
----------------------------------------------------------*/
void i2c_restart(void);


/*---------------------------------------------------------
Function: i2c_stop
Purpose : Generate STOP condition on the I2C bus

Description:
This function terminates the communication between the
master and the slave device on the I2C bus.
----------------------------------------------------------*/
void i2c_stop(void);


/*---------------------------------------------------------
Function: i2c_write
Purpose : Send one byte of data on the I2C bus

Parameter:
dat -> 8-bit data to be transmitted to the slave device
----------------------------------------------------------*/
void i2c_write(u8 dat);


/*---------------------------------------------------------
Function: i2c_nack
Purpose : Read a byte from I2C bus and send NACK

Description:
NACK (Not Acknowledge) indicates that the master does
not want to receive more data from the slave device.
----------------------------------------------------------*/
u8 i2c_nack(void);


/*---------------------------------------------------------
Function: i2c_mack
Purpose : Read a byte from I2C bus and send ACK

Description:
ACK (Acknowledge) indicates that the master is ready to
receive more data from the slave device.
----------------------------------------------------------*/
u8 i2c_mack(void);


#endif
