/*---------------------------------------------------------
Macro: SETBIT
Purpose : Set (make 1) a specific bit in a register or variable

Parameters:
WORD -> Register or variable
BP   -> Bit position to be set
----------------------------------------------------------*/
#define SETBIT(WORD,BP) WORD|=(1<<BP)


/*---------------------------------------------------------
Macro: CLRBIT
Purpose : Clear (make 0) a specific bit in a register or variable

Parameters:
WORD -> Register or variable
BP   -> Bit position to be cleared
----------------------------------------------------------*/
#define CLRBIT(WORD,BP) WORD&=~(1<<BP)


/*---------------------------------------------------------
Macro: CPLBIT
Purpose : Toggle (complement) a specific bit in a register
          If bit is 1 it becomes 0, if 0 it becomes 1

Parameters:
WORD -> Register or variable
BP   -> Bit position to be toggled
----------------------------------------------------------*/
#define CPLBIT(WORD,BP) WORD^=(1<<BP)


/*---------------------------------------------------------
Macro: WRITEBIT
Purpose : Write a specific value (0 or 1) to a bit position

Parameters:
WORD -> Register or variable
BP   -> Bit position
BIT  -> Value to write (0 or 1)
----------------------------------------------------------*/
#define WRITEBIT(WORD,BP,BIT) WORD=((WORD&~(1<<BP))|(BIT<<BP))


/*---------------------------------------------------------
Macro: WRITENIBBLE
Purpose : Write a 4-bit value (nibble) starting from a
          specified bit position

Parameters:
WORD   -> Register or variable
SBP    -> Starting bit position
NIBBLE -> 4-bit value to write
----------------------------------------------------------*/
#define WRITENIBBLE(WORD,SBP,NIBBLE) WORD=((WORD&~(0xf<<SBP))|(NIBBLE<<SBP))


/*---------------------------------------------------------
Macro: WRITEBYTE
Purpose : Write an 8-bit value (byte) starting from a
          specified bit position

Parameters:
WORD -> Register or variable
SBP  -> Starting bit position
BYTE -> 8-bit value to write
----------------------------------------------------------*/
#define WRITEBYTE(WORD,SBP,BYTE) WORD=((WORD&~(0xff<<SBP))|(BYTE<<SBP))


/*---------------------------------------------------------
Macro: WRITEHWORD
Purpose : Write a 16-bit value (half-word) starting from
          a specified bit position

Parameters:
WORD  -> Register or variable
SBP   -> Starting bit position
HWORD -> 16-bit value to write
----------------------------------------------------------*/

#define WRITEHWORD(WORD,SBP,HWORD) WORD=((WORD&~(0xffff<<SBP))|(HWORD<<SBP))
