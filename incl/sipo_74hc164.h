#ifndef SIPO_74HC164_H
#define SIPO_74HC164_H


/*---------------------------------------------------------
Function: Init_SIPO_74HC164
Purpose : Initialize the 74HC164 Serial-In Parallel-Out
          (SIPO) shift registers.

Description:
This function configures the microcontroller pins connected
to the shift registers and prepares them for sending data.
These shift registers are used to control the columns of
the dot matrix display.
----------------------------------------------------------*/
void Init_SIPO_74HC164(void);


/*---------------------------------------------------------
Function: SIPO_74HC164_1
Purpose : Send 8-bit serial data to shift register 1.

Parameter:
unsigned char -> Data byte to be shifted into the register.

Description:
This function shifts data bit-by-bit into the first
74HC164 shift register which controls part of the
dot matrix display.
----------------------------------------------------------*/
void SIPO_74HC164_1(unsigned char);


/*---------------------------------------------------------
Function: SIPO_74HC164_2
Purpose : Send 8-bit serial data to shift register 2.

Description:
Used to control another section of the dot matrix
display through the second shift register.
----------------------------------------------------------*/
void SIPO_74HC164_2(unsigned char);


/*---------------------------------------------------------
Function: SIPO_74HC164_3
Purpose : Send 8-bit serial data to shift register 3.

Description:
This function shifts data to the third 74HC164 shift
register connected to the display.
----------------------------------------------------------*/
void SIPO_74HC164_3(unsigned char);


/*---------------------------------------------------------
Function: SIPO_74HC164_4
Purpose : Send 8-bit serial data to shift register 4.

Description:
Used to send data to the fourth shift register for
controlling additional columns of the dot matrix display.
----------------------------------------------------------*/
void SIPO_74HC164_4(unsigned char);


#endif
