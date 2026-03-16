

#define TX_LED 16 //P1.16

#define RX_LED 17 //P1.17


#define FOSC 12000000

#define CCLK (5*FOSC)

#define PCLK (CCLK/4)

#define BAUD 9600

#define DIVISOR (PCLK/(16*BAUD))


#define UART0_CHNO 6




#define TXD0_EN (1<<0)

#define RXD0_EN (1<<2)


#define _8BIT 3

#define WORD_LEN_SEL _8BIT

#define DLAB_BIT 7

#define DR_BIT 0

#define THRE_BIT 5

#define TEMT_BIT 6

#define RBR_INTERRUPT_EN (1<<0)

#define THRE_INTERRUPT_EN (1<<1)
