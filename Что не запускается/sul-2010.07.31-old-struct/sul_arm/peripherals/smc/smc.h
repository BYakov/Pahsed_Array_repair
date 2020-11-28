
#ifndef _SMC_H_
#define _SMC_H_

enum {
	smc_chip_select0 = 0x60000000,
	smc_chip_select1 = 0x61000000,
	smc_chip_select2 = 0x62000000,
	smc_chip_select3 = 0x63000000,
};

void SMC_Configure(AT91S_HSMC4_CS *hsmc);
void SMC_Write(unsigned int offset, unsigned char data);
unsigned char SMC_Read(unsigned int offset);

enum {
	usart_tx_base = 0,
	usart_rx_base = 0x20,
	//usart_reg0 = 0x1C,
	usart_command = 0x1D,
	usart_select = 0x1E,
	//usart_reg1 = 0x1C,
};

#endif //_SMC_H_
