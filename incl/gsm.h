#include "types.h"   // Contains user-defined data types like u8, u16, u32


/*---------------------------------------------------------
Function: gsm_init
Purpose : Initialize the GSM module

Description:
This function initializes the GSM modem by sending required
AT commands through UART. It prepares the module for SMS
communication (text mode, message notifications, etc.).
----------------------------------------------------------*/
void gsm_init(void);


/*---------------------------------------------------------
Function: send_sms
Purpose : Send an SMS using the GSM module

Parameters:
num  -> Phone number to which the SMS will be sent
info -> Information or header text to send
msg  -> Actual message content

Description:
This function sends an SMS to the specified mobile number
by transmitting AT commands to the GSM module.
----------------------------------------------------------*/
void send_sms(u8 *num, u8* info, u8 *msg);


/*---------------------------------------------------------
Function: delete_sms
Purpose : Delete the currently read SMS from GSM memory

Description:
After processing the SMS (reading and verifying), this
function deletes the SMS from the GSM module to avoid
reading the same message again.
----------------------------------------------------------*/
void delete_sms(void);


/*---------------------------------------------------------
Function: Read_sms
Purpose : Read the received SMS from GSM module

Parameter:
sms -> Buffer to store the received SMS message

Description:
This function reads the SMS stored in the GSM module
memory and copies it into the provided buffer for
processing (verification, extracting message, etc.).
----------------------------------------------------------*/
void Read_sms(u8 *sms);


