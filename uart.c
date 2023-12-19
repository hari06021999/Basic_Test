#include "../include/uart.h"

/* Definition */

void Uart2Init(void)
{

	/* Enabling clock gating of Peripheral and UART2 Clock in domain 0 for all condition*/
	*(T_U32*)0x303844A0 = 0x3UL;

	/* Enabling clock gating of Peripheral clock for IOMUX module*/
	*(T_U32*)0x303841B0 = 0x3UL;

	/* Selecting 100Mhz clock root i.e SYSTEM_PLL2_DIV10 for Module clock*/
	*(T_U32*)0x3038af80 = 0x13000000UL; //0x30388480


	/*Initializing Io-muxing */
	/* ALT0 Mode i.e UART1_RX to UART1_RXD and  UART1_TX to UART1_TXD */
	*(T_U32*)0x3033023C = 0x00UL; //RX Normal --10
	*(T_U32*)0x303304FC = 0x01UL; //RX Daisy --00

	*(T_U32*)0x30330240 = 0x00UL;//TX Normal
	//TX Daisy -- register not found


	/* Configuring UART1 in RS232 Mode */
	ptr_uart2 -> UCR1 = 0x0001UL; /* Enable the UART */
	ptr_uart2 -> UCR2 = 0x6027UL; /* Set hardware flow control, data format and enable transmitter and receiver 0x2127UL--enable hw-ctr;*/
	ptr_uart2 -> UCR3 = 0x0704UL; /* Set UCR3[RXDMUXSEL] = 1 */
	ptr_uart2 -> UCR4 = 0x7C00UL; /* Set CTS trigger level to 31 */
	ptr_uart2 -> UFCR = 0x1081UL; /*Set internal clock divider = 5 i.e 100 MHz/5 = 20 MHz .0x089EUL - to change threshold */
	ptr_uart2 -> UBIR = 0x08FFUL; /*set baud rate to 921.6Kbps based on the 20MHz reference clock */
	ptr_uart2 -> UBMR = 0x0C34UL;
	ptr_uart2 -> UCR1 = 0x2201UL; /* Enable the TRDY and RRDY interrupts */
	ptr_uart2 -> UMCR = 0x0000UL; /* stay at default value 0x0000 */

	my_printf("IMX8M BareMetal Initializing\r\n");
	my_printf("CurrentEL : %d\r\n", getel());
}

void Uart2Transmit(void* pt_data_buff, T_U32 t_length)
{
	T_U8 *local_buff_pt = (T_U8*)pt_data_buff;
	T_U32 count;
	for(count=0;count<t_length;count++)
	{
		/* Check for Transmit Ready */
		/* note: Can also be done by checking FIFO empty*/
		while( M_ZERO == (ptr_uart2 ->USR1 & TRDY_BM));
		ptr_uart2 ->UTXD = *local_buff_pt;
		local_buff_pt++;
	}

}
void UartPutChar(uint8_t pt_data_buff)
{
	//T_U32 count;
	//T_U8 *pt_tx_data_buff = (char)pt_data_buff;
	//T_U32 t_length = sizeof(pt_data_buff)/sizeof(T_U8);
	//for(count=0;count<t_length;count++)
	//	{
			/* Check for Transmit Ready */
			/* note: Can also be done by checking FIFO empty*/
			while( M_ZERO == (ptr_uart2 ->USR1 & TRDY_BM));
			ptr_uart2 ->UTXD = pt_data_buff;

		//}

}

void Uart2Receive(void* pt_data_buff, T_U32 t_length)
{
	T_U8 *local_buff_pt = (T_U8*)pt_data_buff;
	T_U32 count;
	for(count=M_ZERO;count<t_length;count++)
	{
		/* Check for Receive Ready */
		while( M_ZERO == (ptr_uart2 ->USR1 & RRDY_BM));
		*local_buff_pt = ptr_uart2 ->URXD;
		local_buff_pt++;
	}

}
