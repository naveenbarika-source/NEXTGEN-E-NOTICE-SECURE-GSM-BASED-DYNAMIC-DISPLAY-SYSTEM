#include "types.h"        // Contains user-defined data types like u8, u32, etc.
#include <LPC21xx.H>      // Header file for LPC21xx ARM7 microcontroller registers
#include <string.h>       // Standard string functions

#include "delay.h"        // Delay functions (microsecond/millisecond delay)
#include "defines.h"      // Macro definitions used in the project
#include "sipo_74hc164.h" // Functions for controlling 74HC164 SIPO shift register
#include "dot_mat_def.h"  // Dot matrix font definitions
#include "dotmatrix.h"    // Dot matrix display function declarations

extern u8 sms_flag;       // External flag used to stop display when SMS is received

/** 
 * Font array is connected to P0.0 to P0.6 through shift registers
 */


/*---------------------------------------------------------
Function: Init_dm_rows
Purpose : Initialize dot matrix row pins and shift registers
----------------------------------------------------------*/
void Init_dm_rows(void)
{
	Init_SIPO_74HC164();             // Initialize 74HC164 shift registers
	WRITEBYTE(IODIR0,ROWS,0xFF);     // Configure row pins as output
}


/*---------------------------------------------------------
Function: display_str
Purpose : Display 4 characters simultaneously on dot matrix
Inputs  : str -> pointer to string
          dly -> display delay
----------------------------------------------------------*/
void display_str(u8 *str,u32 dly)
{
	u8 i;        // Row index
	u32 d;       // Delay counter
	
	for(d=0; d<dly; d++)   // Repeat display for required delay time
	{
		for(i=0; i<8; i++)  // Scan through 8 rows of dot matrix
		{
			WRITEBYTE(IOPIN0,ROWS,0x00);  // Turn OFF all rows

			// Send column data for each character to shift registers
			SIPO_74HC164_1(font[str[0]-32][i]);
			SIPO_74HC164_2(font[str[1]-32][i]);
			SIPO_74HC164_3(font[str[2]-32][i]);
			SIPO_74HC164_4(font[str[3]-32][i]);

			// Enable current row
			WRITEBYTE(IOPIN0,ROWS,(1<<i));

			delay_us(40);   // Small delay for row refresh
		}
	}	
}


/*---------------------------------------------------------
Function: Display
Purpose : Scroll and display string on dot matrix
Inputs  : ptr -> pointer to message string
          num -> unused parameter (can be removed)
----------------------------------------------------------*/
void Display(u8*ptr,u32 num)
{
   s32 j;        // Loop variable
   u32 len;      // Length of string

	len = mystrlen(ptr);   // Calculate string length

    for(j=0; j<len-3; j++)   // Scroll characters one by one
	{
	   if(sms_flag == 1)     // Stop display if SMS flag is set
	      break;

	   display_str(ptr+j,500); // Display 4 characters at a time
	}
}


/*---------------------------------------------------------
Function: mystrlen
Purpose : Calculate length of string
Input   : mstr -> pointer to string
Return  : length of string
----------------------------------------------------------*/
u32 mystrlen(u8*mstr)
{
  u32 i, cnt=0;

	for(i=0; mstr[i] != '\0'; i++)  // Loop until null character
	    cnt++;                      // Count characters

	return cnt;                     // Return string length
}
