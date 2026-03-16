/*---------------------------------------------------------
Function: delay_us
Purpose : Generate delay in microseconds (µs)

Parameter:
tdly -> number of microseconds to delay

Description:
Creates a small delay using a software loop.
The value is multiplied by 12 to approximate
microsecond delay based on processor speed.
----------------------------------------------------------*/
void delay_us(unsigned int tdly)
{
	tdly *= 12;        // Adjust delay count for microseconds
	while(tdly--);     // Wait until counter becomes zero
}


/*---------------------------------------------------------
Function: delay_ms
Purpose : Generate delay in milliseconds (ms)

Parameter:
tdly -> number of milliseconds to delay

Description:
Creates delay in milliseconds using a loop.
The value is multiplied by 12000 to convert
milliseconds into loop count.
----------------------------------------------------------*/
void delay_ms(unsigned int tdly)
{
	tdly *= 12000;     // Adjust delay count for milliseconds
	while(tdly--);     // Wait until counter becomes zero
}


/*---------------------------------------------------------
Function: delay_s
Purpose : Generate delay in seconds (s)

Parameter:
tdly -> number of seconds to delay

Description:
Creates delay in seconds using a large loop
count for approximate second delay.
----------------------------------------------------------*/
void delay_s(unsigned int tdly)
{
	tdly *= 12000000;  // Adjust delay count for seconds
	while(tdly--);     // Wait until counter becomes zero

}
