#include <LPC21xx.H>     // Header file for LPC21xx ARM7 microcontroller registers

#include "delay.h"       // Delay functions (microsecond delay)
#include "defines.h"     // Macro definitions like SETBIT, WRITEBIT etc.


/*---------------------------------------------------------
74HC164 SIPO Shift Register Connections
Each shift register controls one part of the dot matrix
SIN = Serial Input
CP  = Clock Pulse
----------------------------------------------------------*/

// 74HC164 Shift Register 1 connections
#define SIN_1 8          // Serial data input pin connected to P0.8
#define CP_1  9          // Clock pin connected to P0.9

// 74HC164 Shift Register 2 connections
#define SIN_2 10         // Serial data input pin connected to P0.10
#define CP_2  11         // Clock pin connected to P0.11

// 74HC164 Shift Register 3 connections
#define SIN_3 12         // Serial data input pin connected to P0.12
#define CP_3  13         // Clock pin connected to P0.13

// 74HC164 Shift Register 4 connections
#define SIN_4 14         // Serial data input pin connected to P0.14
#define CP_4  15         // Clock pin connected to P0.15


/*---------------------------------------------------------
Function: Init_SIPO_74HC164
Purpose : Configure all SIN and CP pins as output pins
----------------------------------------------------------*/
void Init_SIPO_74HC164(void)
{
	SETBIT(IODIR0,SIN_1);   // Set SIN_1 pin as output
	SETBIT(IODIR0,CP_1);    // Set CP_1 pin as output
	
	SETBIT(IODIR0,SIN_2);   // Set SIN_2 pin as output
	SETBIT(IODIR0,CP_2);    // Set CP_2 pin as output
	
	SETBIT(IODIR0,SIN_3);   // Set SIN_3 pin as output
	SETBIT(IODIR0,CP_3);    // Set CP_3 pin as output
	
	SETBIT(IODIR0,SIN_4);   // Set SIN_4 pin as output
	SETBIT(IODIR0,CP_4);    // Set CP_4 pin as output
}


/*---------------------------------------------------------
Function: SIPO_74HC164_1
Purpose : Send 8-bit data serially to Shift Register 1
Input   : sDat -> 8-bit data to shift register
----------------------------------------------------------*/
void SIPO_74HC164_1(unsigned char sDat)
{
	unsigned char i;
	
	for(i=0;i<8;i++)  // Send 8 bits one by one
	{
		// Send MSB first
		WRITEBIT(IOPIN0,SIN_1,((sDat>>(7-i))&1));
		
		// Generate clock pulse
		IOCLR0 = 1<<CP_1;   // Clock LOW
		delay_us(1);
		
		IOSET0 = 1<<CP_1;   // Clock HIGH (data shifted)
		delay_us(1);
	}
}


/*---------------------------------------------------------
Function: SIPO_74HC164_2
Purpose : Send 8-bit data to Shift Register 2
----------------------------------------------------------*/
void SIPO_74HC164_2(unsigned char sDat)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		// Send data bit by bit
		WRITEBIT(IOPIN0,SIN_2,((sDat>>(7-i))&1));
		
		// Generate clock pulse
		IOCLR0 = 1<<CP_2;
		delay_us(1);
		
		IOSET0 = 1<<CP_2;
		delay_us(1);
	}	
}


/*---------------------------------------------------------
Function: SIPO_74HC164_3
Purpose : Send 8-bit data to Shift Register 3
----------------------------------------------------------*/
void SIPO_74HC164_3(unsigned char sDat)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		// Shift data serially
		WRITEBIT(IOPIN0,SIN_3,((sDat>>(7-i))&1));
		
		// Clock pulse to shift data
		IOCLR0 = 1<<CP_3;
		delay_us(1);
		
		IOSET0 = 1<<CP_3;
		delay_us(1);
	}	
}


/*---------------------------------------------------------
Function: SIPO_74HC164_4
Purpose : Send 8-bit data to Shift Register 4
----------------------------------------------------------*/
void SIPO_74HC164_4(unsigned char sDat)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		// Send data serially (MSB first)
		WRITEBIT(IOPIN0,SIN_4,((sDat>>(7-i))&1));
		
		// Generate clock pulse
		IOCLR0 = 1<<CP_4;
		delay_us(1);
		
		IOSET0 = 1<<CP_4;
		delay_us(1);
	}	

}
