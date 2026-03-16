/*---------------------------------------------------------
User Defined Data Types
These typedef statements define shorter names for common
data types used in embedded systems programming.
----------------------------------------------------------*/

typedef unsigned char u8;      // 8-bit unsigned integer (0 to 255)

typedef char s8;               // 8-bit signed integer (-128 to 127)

typedef unsigned int u32;      // 32-bit unsigned integer

typedef unsigned short int u16; // 16-bit unsigned integer

typedef signed int s32;        // 32-bit signed integer

typedef float f32;             // 32-bit floating point number

typedef double f64;            // 64-bit floating point number


/*---------------------------------------------------------
Function Prototype: mystrlen
Purpose : Calculate the length of a string

Parameter*/

u32 mystrlen(u8*mstr);

