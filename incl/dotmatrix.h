#include "types.h"   // Includes user-defined data types like u8 (unsigned 8-bit) and u32 (unsigned 32-bit)

/*---------------------------------------------------------
Function: Init_dm_rows
Purpose : Initialize dot matrix display rows

Description:
This function initializes the hardware related to the
dot matrix display rows. It sets the row pins as outputs
and prepares the display for operation.
----------------------------------------------------------*/
void Init_dm_rows(void);


/*---------------------------------------------------------
Function: display_str
Purpose : Display characters on the dot matrix display

Parameters:
str -> Pointer to the string that needs to be displayed
dly -> Delay time for which the characters should be shown

Description:
This function takes a string and displays it on the
dot matrix display for a specified delay time.
----------------------------------------------------------*/
void display_str(u8 *str, u32 dly);


/*---------------------------------------------------------
Function: Display
Purpose : Scroll and display a message on the dot matrix

Parameters:
ptr -> Pointer to the message string to be displayed
num -> Number of times or duration to display the message

Description:
This function is used to scroll or continuously display
a message on the dot matrix display.
----------------------------------------------------------*/


void Display(u8* ptr, u32 num);

