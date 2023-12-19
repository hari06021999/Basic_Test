
#include <stdint.h>

#define UART2_TEST

#ifdef UART2_TEST

/* Macros */
#define T_U32								unsigned int
#define T_U8								unsigned char
#define T_S32 								signed int
#define T_S8 								signed char
#define M_UART_2_BASE_ADDRESS               0x30890000
#define M_ZERO 								0UL
#define M_ONE 								1UL
#define M_THIRTEEN 							13UL
#define M_NINE 						 		9UL
#define M_SIX 								6UL
#define M_SEVEN 							7UL
#define M_EIGHT 							8UL
#define M_TWELVE 							12UL
#define TRDY_BM            				   ((T_U32)M_ONE << M_THIRTEEN)
#define RRDY_BM            				   ((T_U32)M_ONE << M_NINE)
#define STOP_BITS_BM            		   ((T_U32)M_ONE << M_SIX)
#define PARITY_CHECK_BM            		   ((T_U32)M_ONE << M_EIGHT)
#define PARITY_BM            			   ((T_U32)M_ONE << M_SEVEN)
#define LOOP_BM            			 	   ((T_U32)M_ONE << M_TWELVE)

#define SET_TWO_STOP_BIT       			   ptr_uart2 ->UCR2 |= STOP_BITS_BM /* 2bits */
#define SET_ONE_STOP_BIT 				   ptr_uart2 ->UCR2 &= ~STOP_BITS_BM /* one bit*/
#define DISABLE_PARITY					   ptr_uart2 ->UCR2 &= ~PARITY_CHECK_BM /* parity disable i.e No parity*/
#define ENABLE_PARITY					   ptr_uart2 ->UCR2 |= PARITY_CHECK_BM /* parity enable*/
#define SET_ODD_PARITY					   ptr_uart2 ->UCR2 &= ~PARITY_BM /* odd parity*/
#define SET_EVEN_PARITY 				   ptr_uart2 ->UCR2 |= PARITY_BM /* even parity*/
#define ENABLE_LOOP_BACK				   ptr_uart2 -> UTS |= LOOP_BM
#define DISABLE_LOOP_BACK				   ptr_uart2 -> UTS |= ~LOOP_BM



/* UART Layout */
typedef struct
{									/* offset - Description 						-Access		-Reset Values 		*/
	volatile T_U32 URXD;			/* +0x00 - UART Receiver Register   			-R			-0x0000_0000		*/
	volatile T_U32 NOT_USED_1[15];	/* +0x04 - Not Used					   			-NA			-NA					*/
	volatile T_U32 UTXD;			/* +0x40 - UART Transmitter Register 			-W			-0x0000_0000		*/
	volatile T_U32 NOT_USED_2[15];	/* +0x44 - Not Used					   			-NA			-NA					*/
	volatile T_U32 UCR1;			/* +0x80 - UART Control Register 1 				-R/W		-0x0000_0000		*/
	volatile T_U32 UCR2;			/* +0x84 - UART Control Register 2 				-R/W		-0x0000_0001		*/
	volatile T_U32 UCR3;			/* +0x88 - UART Control Register 3 				-R/W		-0x0000_0700		*/
	volatile T_U32 UCR4;			/* +0x8C - UART Control Register 4 				-R/W		-0x0000_8000		*/
	volatile T_U32 UFCR;			/* +0x90 - UART FIFO Control Register			-R/W		-0x0000_0801		*/
	volatile T_U32 USR1;			/* +0x94 - UART Status Register 1   			-R/W		-0x0000_2040		*/
	volatile T_U32 USR2;			/* +0x98 - UART Status Register 2  				-R/W		-0x0000_4028		*/
	volatile T_U32 UESC;			/* +0x9C - UART Escape Character Register		-R/W		-0x0000_002B		*/
	volatile T_U32 UTIM;			/* +0xA0 - UART Escape Timer Register			-R/W		-0x0000_0000		*/
	volatile T_U32 UBIR;			/* +0xA4 - UART BRM Incremental Register		-R/W		-0x0000_0000		*/
	volatile T_U32 UBMR;			/* +0xA8 - UART BRM Modulator Register			-R/W		-0x0000_0000		*/
	volatile T_U32 UBRC;			/* +0xAC - UART Baud Rate Count Register		-R			-0x0000_0004		*/
	volatile T_U32 ONEMS;			/* +0xB0 - UART One Millisecond Register		-R/W		-0x0000_0000		*/
	volatile T_U32 UTS;				/* +0xB4 - UART Test Register					-R/W		-0x0000_0060		*/
	volatile T_U32 UMCR;			/* +0xB8 - UART RS-485 Mode Control Register	-R/W		-0x0000_0000		*/
} UART_DEVICE_DRIVER;


/* Pointer for UART1 */
volatile UART_DEVICE_DRIVER	*ptr_uart2  =(UART_DEVICE_DRIVER*) M_UART_2_BASE_ADDRESS;

/* Prototype */
void Uart2Init(void);
void Uart2Transmit(void* pt_data_buff, T_U32 t_length);
void Uart2Receive(void* pt_data_buff, T_U32 t_length);
void UartPutChar(uint8_t pt_data_buff);
#endif