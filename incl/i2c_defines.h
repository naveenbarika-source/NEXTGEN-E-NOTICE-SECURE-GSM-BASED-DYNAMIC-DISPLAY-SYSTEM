//i2c_defines.h


#ifndef I2C_DEFINES_H
#define I2C_DEFINES_H


/*---------------------------------------------------------
Pin Function Definitions
These macros configure the pin selection register (PINSEL)
to enable I2C communication pins.
----------------------------------------------------------*/

#define SCL_0_2   0x00000010   // Configure P0.2 as SCL (I2C Clock Line)
#define SDA_0_3   0x00000040   // Configure P0.3 as SDA (I2C Data Line)



/*---------------------------------------------------------
I2C Speed Configuration
These macros define the system clock values and calculate
the divider required to generate the desired I2C clock speed.
----------------------------------------------------------*/

#define FOSC      12000000      // Oscillator frequency = 12 MHz

#define CCLK      (5*FOSC )     // CPU clock (CCLK) = 5 × FOSC = 60 MHz

#define PCLK      (CCLK/4)      // Peripheral clock (PCLK) = CCLK / 4

#define I2C_SPEED 100000        // Desired I2C communication speed = 100 kHz (Standard Mode)



/*---------------------------------------------------------
I2C Clock Divider
Used to set SCLH and SCLL registers to generate the required
I2C clock frequency.
----------------------------------------------------------*/

#define I2C_DIVIDER   ((PCLK/I2C_SPEED)/2)



/*---------------------------------------------------------
Bit Definitions for I2CONSET Register
These bits control I2C operations like start, stop, enable etc.
----------------------------------------------------------*/

#define AA_BIT   2   // Assert Acknowledge bit
#define SI_BIT   3   // I2C Interrupt flag bit
#define STO_BIT  4   // STOP condition bit
#define STA_BIT  5   // START condition bit
#define I2EN_BIT 6   // I2C Enable bit



/*---------------------------------------------------------
Bit Definitions for I2CONCLR Register
These bits are used to clear specific control bits.
----------------------------------------------------------*/

#define AAC_BIT   2   // Clear Acknowledge bit
#define SIC_BIT   3   // Clear Interrupt flag
#define STAC_BIT  5   // Clear START condition
#define I2ENC_BIT 6   // Disable I2C interface


#endif


