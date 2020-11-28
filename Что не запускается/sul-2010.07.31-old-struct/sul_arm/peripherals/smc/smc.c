
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _SMC_H_
	#include "smc.h"
#endif

void SMC_Configure(AT91S_HSMC4_CS *hsmc)
{
	hsmc->HSMC4_MODE = 0x3 | (0x0 << 12); // WR | RD | DBW = 0
	hsmc->HSMC4_SETUP = 0x4 | (0x4 << 8) | (0x4 << 16) | (0x4 << 24); // NWE_SETUP | NCS_WR_SETUP | NRD_SETUP | NCS_RD_SETUP
	hsmc->HSMC4_PULSE = 0x4 | (0xC << 8) | (0x4 << 16) | (0xC << 24); // NWE_PULSE | NCS_WR_PULSE | NRD_PULSE | NCS_RD_PULSE 
	//hsmc->HSMC4_SETUP = 0x4 | (0x4 << 8); // NWE_SETUP | NCS_WR_SETUP | NRD_SETUP | NCS_RD_SETUP
	//hsmc->HSMC4_PULSE = 0x4 | (0xC << 8); // NWE_PULSE | NCS_WR_PULSE | NRD_PULSE | NCS_RD_PULSE 
	hsmc->HSMC4_CYCLE = 0xF | (0xF << 16); // NWE_CYCLE
}

void SMC_Write(unsigned int offset, unsigned char data)
{
	*((unsigned char*)smc_chip_select2 + offset) = data;
}

unsigned char SMC_Read(unsigned int offset)
{
	return *((unsigned char*)smc_chip_select2 + offset);
}

