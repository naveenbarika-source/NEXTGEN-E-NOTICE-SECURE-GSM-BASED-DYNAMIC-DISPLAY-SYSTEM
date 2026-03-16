#include <string.h>     // For string functions like strstr(), strchr(), memset()
#include "security.h"   // Security related definitions and prototypes


/*---------------------------------------------------------
Function: verify_format
Purpose : Check whether the received SMS format is valid
Input   : msg      -> received SMS message
          Ath_num  -> authorized phone number
Return  :
          1 -> Valid Display message (1404D)
          2 -> Valid Mobile number change message (1404M)
          3 -> Authorized number but wrong format
          4 -> Unauthorized number
----------------------------------------------------------*/
int verify_format(u8 *msg,u8*Ath_num)
{
  // Check if message contains authorized number
  if(strstr((s8*)msg,(s8*)Ath_num))
  {
        // Check if message contains display command "1404D"
        // and terminating symbol '$'
   	if((strstr((s8*)msg,"1404D")) && (strstr((s8*)msg,"$")))
   	{
   			return 1;   // Display message format
   	}

        // Check if message contains mobile number change command "1404M"
   	else if((strstr((s8*)msg,"1404M")) && (strstr((s8*)msg,"$")))
   	{
   			return 2;   // Mobile number update command
   	}
   	else
   	{
            return 3;   // Authorized user but wrong format
   	}
  }
  else
   return 4;            // Unauthorized phone number
}



/*---------------------------------------------------------
Function: extract_content
Purpose : Extract display message from SMS
Example : "1404DHELLO$"
Output  : "HELLO"
----------------------------------------------------------*/
void extract_content(u8 *msg1,u8 *output)
{
    u32 i,j=0;
	s8*msg=NULL;

	memset(output,'\0',200);    // Clear output buffer

    // Find starting point of display command "1404D"
  	msg=strstr((s8*)msg1,"1404D");

    // Extract characters until '$' symbol
	for(i=3; msg[i]!='$'; i++)
	{
	    if(i<5)
		   output[j++]=' ';    // Add spaces at beginning
		else
			output[j++]=msg[i]; // Copy message characters
	}

	output[j++]=' ';           // Add trailing spaces
	output[j++]=' ';
	output[j++]=' ';
	output[j]='\0';            // End string
}



/*---------------------------------------------------------
Function: extract_num
Purpose : Extract new authorized mobile number
Example : "1404M9876543210$"
Output  : "9876543210"
----------------------------------------------------------*/
void extract_num(u8 *msg1,u8 *num)
{
    u32 i,j=0;
	s8*msg=(s8*)msg1;

    // Find mobile number command
	msg=strstr((s8*)msg1,"1404M");

    // Extract number until '$'
	for(i=5; msg[i]!='$'; i++)
	{
		num[j++]=msg[i];
	}

	num[j]='\0';    // End string
}



/*---------------------------------------------------------
Function: Invalid_msg
Purpose : Extract message when SMS format is invalid
----------------------------------------------------------*/
void Invalid_msg(u8*msg,u8*inval_msg)
{
       u32 newline=0,i=0,j=0;
	   s8*pts=NULL;

	   pts=(s8*)msg;

       // Locate second newline in GSM response
	   while(1)
	   {
	     pts=strchr(pts,'\n');
		 pts++;
		 newline++;

		 if(newline==2)
		     break;  
	   }

       // Calculate index of message start
	   i=pts-(s8*)msg;

       // Copy message until carriage return
	   for(; msg[i]!=0x0D; i++)
	   {
	   		inval_msg[j++]=msg[i];
	   }

	   inval_msg[j]='\0';  // End string
}



/*---------------------------------------------------------
Function: Invalid_num
Purpose : Extract phone number from invalid message
----------------------------------------------------------*/
void Invalid_num(u8*msg,u8*inval_msg)
{
   s8*ptm=NULL;
   u32 i;

   ptm=(s8*)msg;

   // Find "UNREAD" section in GSM SMS response
   ptm=strstr((s8*)msg,"UNREAD");

   // Move pointer to phone number location
   ptm=ptm+11;

   // Copy 10 digit phone number
   for(i=0;i<10;i++)
   {
     inval_msg[i]=ptm[i];
   }

	inval_msg[i]='\0';   // End string
}




