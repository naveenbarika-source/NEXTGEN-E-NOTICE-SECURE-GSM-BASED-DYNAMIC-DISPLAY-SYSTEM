/*---------------------------------------------------------
Function: delay_us
Purpose : Generate delay in microseconds (µs)

Parameter:
unsigned int -> number of microseconds to delay

Description:
This function prototype is used to declare a function
that creates a small delay in microseconds. It is mainly
used for precise timing in hardware operations.
----------------------------------------------------------*/
void delay_us(unsigned int);


/*---------------------------------------------------------
Function: delay_ms
Purpose : Generate delay in milliseconds (ms)

Parameter:
unsigned int -> number of milliseconds to delay

Description:
This function prototype is used to declare a delay
function that pauses program execution for a specified
number of milliseconds.
----------------------------------------------------------*/
void delay_ms(unsigned int);


/*---------------------------------------------------------
Function: delay_s
Purpose : Generate delay in seconds (s)

Parameter:
unsigned int -> number of seconds to delay

Description:
This function prototype declares a function that
creates delay in seconds. It is generally used for
longer waiting periods in embedded applications.
----------------------------------------------------------*/
void delay_s(unsigned int);;


