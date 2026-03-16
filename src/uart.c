#include "uart_def.h"   // UART related macro definitions
#include <LPC21xx.H>    // LPC21xx microcontroller register definitions
#include "types.h"      // User defined data types (u8, u32 etc.)
#include <string.h>     // String functions like strstr(), strcmp()
#include "delay.h"      // Delay functions
#include "security.h"   // Security related functions for the project

// Buffer to store received UART data (from GSM module)
u8 rx_buf[300], new_var;

// Index used to store received characters into buffer
u32 indx;

// Flags used in program
u8 sms_flag = 0, t_flag;

// Variable to store received character
u8 ch;


/*---------------------------------------------------------
Function: UART0_interrupt
Purpose : Interrupt Service Routine for UART0
          Handles receiving and transmitting data
----------------------------------------------------------*/
void UART0_interrupt(void) __irq
{
	// Read UART interrupt identification register
	new_var = U0IIR;

	// Check if interrupt is due to received data
	if((new_var & 0x04))
	{
		// Read received character from UART receive buffer
		ch = U0RBR;

		// Store character in buffer if buffer not full
		if(indx < 300)
		{
			rx_buf[indx++] = ch;

			// Check if GSM response contains "+CMTI"
			// +CMTI indicates a new SMS has arrived
			if(strstr((s8*)rx_buf,"+CMTI"))
			{
			   sms_flag = 1;   // Set SMS flag
			}

			/* Code to detect incoming call (disabled currently)
			if(strcmp((s8*)rx_buf,"+CLIP"))
			{
			    UART0_Str("ATH\r\n");  // Hang up call
				memset(rx_buf,'\0',300); // Clear buffer
			}
			*/
		}
	}

	// Check if interrupt is due to THRE (Transmit Holding Register Empty)
	else if(new_var & 0x02)
	{
		t_flag = 1;  // Transmission complete
	}

	// Clear interrupt in VIC
	VICVectAddr = 0;
}


/*---------------------------------------------------------
Function: UART0_Init
Purpose : Initialize UART0 for serial communication
          Used for GSM module communication
----------------------------------------------------------*/
void UART0_Init()
{
	// Enable TXD0 and RXD0 pins
	PINSEL0 |= (TXD0_EN | RXD0_EN);

	// Set UART word length and enable divisor latch
	U0LCR = (WORD_LEN_SEL | (1<<DLAB_BIT));

	// Set baud rate (for example 9600 depending on PCLK)
	U0DLL = 97;
	U0DLM = 0;

	// Disable divisor latch
	U0LCR &= ~(1<<DLAB_BIT);

	// Configure UART interrupt in VIC
	VICVectAddr0 = (unsigned)UART0_interrupt;
	VICVectCntl0 = 0x20 | UART0_CHNO;
	VICIntEnable = 1<<UART0_CHNO;

	// Enable receive and transmit interrupts
	U0IER = RBR_INTERRUPT_EN | THRE_INTERRUPT_EN;
}


/*---------------------------------------------------------
Function: UART0_Tx
Purpose : Transmit a single character through UART
----------------------------------------------------------*/
void UART0_Tx(unsigned char ch)
{
	t_flag = 0;     // Clear transmit flag
	U0THR = ch;     // Load character into transmit register

	// Wait until transmission is completed
	while(t_flag == 0);
}


/*---------------------------------------------------------
Function: UART0_Str
Purpose : Send a complete string through UART
----------------------------------------------------------*/
void UART0_Str(unsigned char *str)
{
	while(*str)
		UART0_Tx(*str++);  // Send characters one by one
}


/*---------------------------------------------------------
Function: UART0_Rx
Purpose : Receive one character from UART
----------------------------------------------------------*/
char UART0_Rx(void)
{
	// Wait until data is available in receive buffer
	while (!(U0LSR & 0x01));

	// Return received character
	return (U0RBR);

}
