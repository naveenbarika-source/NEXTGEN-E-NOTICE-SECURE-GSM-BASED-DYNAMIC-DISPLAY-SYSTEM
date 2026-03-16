#include "uart.h"        // UART communication functions
#include "types.h"       // User defined data types (u8, u32 etc.)
#include <string.h>      // String functions (strstr, strcpy, memset)
#include <LPC21xx.H>     // LPC21xx register definitions
#include "gsm.h"         // GSM function prototypes
#include "dotmatrix.h"   // Dot matrix display functions
#include "delay.h"       // Delay functions

// External variable used to store number of received UART characters
extern u32 indx;


/*---------------------------------------------------------
Function: gsm_init
Purpose : Initialize GSM module using AT commands
----------------------------------------------------------*/
void gsm_init(void)
{
  // Wait until GSM module sends "+PBREADY"
  // This indicates SIM card phonebook is ready
  while(strstr((char*)rx_buf,"+PBREADY")==0);

  indx=0;
  memset(rx_buf,'\0',300);

  // Send basic AT command to check GSM communication
  UART0_Str("AT\r\n");

  // Wait until some characters are received
  while(indx<3);

  delay_ms(500);

  rx_buf[indx]='\0';

  // Check if GSM responded with "OK"
  if(strstr((char*)rx_buf,"OK"))
  {
      indx=0;
      memset(rx_buf,'\0',300);

      // Disable command echo
      UART0_Str("ATE0\r\n");

      while(indx<3);

      delay_ms(500);

      rx_buf[indx]='\0';

      if(strstr((s8*)rx_buf,"OK"))
      {
          indx=0;
          memset(rx_buf,'\0',300);

          // Set GSM module to SMS text mode
          UART0_Str("AT+CMGF=1\r\n");

          while(indx<3);

          delay_ms(500);

          rx_buf[indx]='\0';

          if(strstr((s8*)rx_buf,"OK"))
          {
              indx=0;
              memset(rx_buf,'\0',300);

              // Configure GSM to notify microcontroller when new SMS arrives
              UART0_Str("AT+CNMI=2,1,0,0,0\r\n");

              while(indx<4);

              delay_ms(1100);

              rx_buf[indx]='\0';

              if(strstr((char*)rx_buf,"OK"))
              {
                  // GSM initialized successfully
                  Display(" GSM INIT SUCS ",300);
              }
              else
                  Display("  GSM INIT ERROR 4",100);
          }
          else
              Display("  GSM INIT ERROR 3",100);
      }
      else
          Display("  GSM INIT ERROR 2",100);
  }
  else
      Display("  GSM INIT ERROR 1",100);
}



/*---------------------------------------------------------
Function: send_sms
Purpose : Send SMS using GSM module
Parameters:
num  -> Destination phone number
info -> Information/header text
msg  -> Message content
----------------------------------------------------------*/
void send_sms(u8 *num, u8 *info, u8 *msg)
{
    indx=0;
    memset(rx_buf,'\0',300);

    // Send command to start SMS transmission
    UART0_Str("AT+CMGS=\"");

    // Send phone number
    UART0_Str(num);

    UART0_Str("\"\r\n");

    delay_ms(500);

    indx=0;

    // Send SMS text
    UART0_Str(info);
    UART0_Str(msg);

    // CTRL+Z (0x1A) indicates end of SMS message
    UART0_Tx(0x1A);

    delay_ms(5000);

    while(indx<3);

    rx_buf[indx]='\0';

    // Check if SMS was sent successfully
    if(strstr((s8*)rx_buf,"OK"))
    {
        // Message successfully sent
    }
}



/*---------------------------------------------------------
Function: delete_sms
Purpose : Delete SMS from GSM memory
----------------------------------------------------------*/
void delete_sms(void)
{
    indx=0;

    // Clear receive buffer
    memset(rx_buf,0,300);

    // Delete SMS stored at location 1
    UART0_Str("AT+CMGD=1\r\n");

    delay_ms(1000);

    // Wait for GSM response
    while(indx<3);
}



/*---------------------------------------------------------
Function: Read_sms
Purpose : Read SMS stored in GSM memory
Parameter:
sms -> buffer where SMS will be stored
----------------------------------------------------------*/
void Read_sms(u8 *sms)
{
   indx=0;

   // Clear receive buffer
   memset(rx_buf,'\0',300);

   // Command to read SMS stored at location 1
   UART0_Str("AT+CMGR=1\r\n");

   while(indx<3);

   delay_s(2);

   rx_buf[indx]='\0';

   // Check if GSM response is valid
   if(strstr((s8*)rx_buf,"OK"))
   {
        // Copy received SMS data into sms buffer
        strcpy((char*)sms,(char*)rx_buf);
   }
}
