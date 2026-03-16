#include "types.h"   // Includes user-defined data types like u8, u32 etc.

/*---------------------------------------------------------
Function: verify_format
Purpose : Verify whether the received SMS format is valid
          and from the authorized mobile number.

Parameters:
msg      -> Pointer to the received SMS message
Ath_num  -> Pointer to the authorized mobile number

Return:
1 -> Valid display message format
2 -> Valid mobile number update format
3 -> Authorized number but incorrect format
4 -> Unauthorized number
----------------------------------------------------------*/
int verify_format(u8 *msg, u8 *Ath_num);


/*---------------------------------------------------------
Function: extract_content
Purpose : Extract the message content from the received SMS
          that will be displayed on the dot matrix display.

Parameters:
msg    -> Pointer to the received SMS
output -> Buffer where the extracted message will be stored
----------------------------------------------------------*/
void extract_content(u8 *msg, u8 *output);


/*---------------------------------------------------------
Function: extract_num
Purpose : Extract a mobile number from the received SMS.

Parameters:
msg -> Pointer to the received SMS
num -> Buffer where the extracted mobile number will be stored
----------------------------------------------------------*/
void extract_num(u8 *msg, u8 *num);


/*---------------------------------------------------------
Function: Invalid_msg
Purpose : Extract and store the message when the SMS format
          is invalid but sent from an authorized number.

Parameters:
msg        -> Pointer to the received SMS
inval_msg  -> Buffer to store the invalid message
----------------------------------------------------------*/
void Invalid_msg(u8 *msg, u8 *inval_msg);


/*---------------------------------------------------------
Function: Invalid_num
Purpose : Extract the phone number when the SMS is received
          from an unauthorized number.

Parameters:
msg        -> Pointer to the received SMS
inval_msg  -> Buffer where the invalid number will be stored
----------------------------------------------------------*/

void Invalid_num(u8 *msg, u8 *inval_msg);
