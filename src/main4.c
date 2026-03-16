#include <string.h>          // String handling functions
#include "uart.h"           // UART communication functions
#include "types.h"          // User defined data types (u8, u32, etc.)
#include "delay.h"          // Delay functions
#include "i2c_eeprom.h"     // EEPROM read/write functions
#include "gsm.h"            // GSM module functions
#include "security.h"       // SMS security and validation functions
#include "i2c_eeprom_defines.h" // EEPROM address definitions
#include "dotmatrix.h"      // Dot matrix display functions
#include "i2c.h"            // I2C initialization and communication


// Buffer to store invalid message
u8 Invalid[200] = "";

// Default message shown on dot matrix until SMS arrives
u8 stored_msg[200] = "   WAITING FORB THE MSG  ";

// Buffer to store new SMS message read from GSM
u8 new_msg[300];

// Authorized mobile number allowed to send commands
u8 auth_number[] = "9951826554";

// External variables from UART interrupt file
extern u8 sms_flag;   // Flag set when new SMS arrives
extern u32 indx;      // Index used while receiving UART data


/*---------------------------------------------------------
Function: init_sym
Purpose : Initialize all peripherals used in the project
----------------------------------------------------------*/
void init_sym()
{
	UART0_Init();     // Initialize UART for GSM communication
    init_i2c();      // Initialize I2C bus for EEPROM
    Init_dm_rows();  // Initialize dot matrix display rows
	gsm_init();      // Initialize GSM module
}


/*---------------------------------------------------------
Main Function
Purpose : Control the complete e-notice board system
----------------------------------------------------------*/
int main(void)
{
    s32 N_Bytes = 50;   // Number of bytes to read/write from EEPROM

    // Initialize all system peripherals
    init_sym();

    // Check if a message is stored in EEPROM
	if((i2c_eeprom_randomread(I2C_EEPROM_SA1, EE_MSGI)) == '7')
        	EEPROM_Reed(I2C_EEPROM_SA1, EE_MSG, stored_msg, N_Bytes);

    //  Read stored authorized mobile number from EEPROM
	if((i2c_eeprom_randomread(I2C_EEPROM_SA1,EE_MOBI))=='4')
        	EEPROM_Reed(I2C_EEPROM_SA1,EE_MOB,auth_number,11);


    while(1)
    {
	    // Reset UART receive index
	    indx = 0;

        // Clear UART receive buffer
	  	memset(rx_buf,'\0',300);

        // Display stored message continuously
	    do
		  {
            Display(stored_msg,500);   // Show message on dot matrix
	  	}
        // Loop until new SMS is detected
		 while(sms_flag == 0);

        // Reset SMS flag after detection
		sms_flag = 0;

        // Read received SMS from GSM module
		Read_sms(new_msg);

        // Check SMS format and sender authorization
       switch(verify_format(new_msg, auth_number))
       {

            // Case 1: Valid display message command
       case 1:
                extract_content(new_msg, stored_msg);  // Extract display text

                N_Bytes = mystrlen(stored_msg);        // Get message length

                // Store message indicator in EEPROM
				         i2c_eeprom_bytewrite(I2C_EEPROM_SA1, EE_MSGI, '7');

                // Save new message in EEPROM
				        EEPROM_Write(I2C_EEPROM_SA1, EE_MSG, stored_msg, N_Bytes);

                delete_sms();   // Delete processed SMS
				          break;


                  // Case 2: Authorized number change command
			case 2:
                extract_num(new_msg, auth_number); // Extract new number

                // Store indicator for mobile number in EEPROM
				        i2c_eeprom_bytewrite(I2C_EEPROM_SA1, EE_MOBI, '4');

                // Save new authorized number in EEPROM
			          EEPROM_Write(I2C_EEPROM_SA1, EE_MOB, auth_number, 11);

                delete_sms();   // Delete processed SMS
				          break;


                 // Case 3: Authorized user but wrong message format
			case 3:   Invalid_msg(new_msg, Invalid);  // Extract invalid message

                // Send SMS informing correct format
	         			send_sms(auth_number, "Inavlid format ","\r\ncorrect format is 1404Dmsg$");
  
                delete_sms();  // Delete invalid SMS
				        break;


               // Case 4: Unauthorized user
			case 4:
                Invalid_num(new_msg, Invalid);  // Extract sender number

                // Send SMS warning for unauthorized access
				       send_sms(auth_number,  "Invalid access number ",Invalid);

                delete_sms();   // Delete SMS
				break;
		}
    }
}


           
