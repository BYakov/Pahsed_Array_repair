
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _SSC_H_
	#include "ssc.h"
#endif

void SSC_Configure()
{
	AT91C_BASE_SSC0->SSC_CR = AT91C_SSC_RXEN | AT91C_SSC_TXEN;	
	AT91C_BASE_SSC0->SSC_CMR = 1;

	AT91C_BASE_SSC0->SSC_RCMR = AT91C_SSC_CKS_DIV | 
								AT91C_SSC_CKO_CONTINOUS | 
								AT91C_SSC_STOP | 
								AT91C_SSC_STTDLY;

	AT91C_BASE_SSC0->SSC_RFMR = 31;

	AT91C_BASE_SSC0->SSC_TCMR = AT91C_SSC_CKS_DIV | 
								AT91C_SSC_CKO_CONTINOUS | 
								AT91C_SSC_STOP | 
								AT91C_SSC_STTDLY;

	AT91C_BASE_SSC0->SSC_TFMR = 31;
}

void SSC_Write(unsigned int frame)
{
    while ((AT91C_BASE_SSC0->SSC_SR & AT91C_SSC_TXRDY) == 0);
    AT91C_BASE_SSC0->SSC_THR = frame;
}

unsigned int SSC_Read()
{
    while ((AT91C_BASE_SSC0->SSC_SR & AT91C_SSC_RXRDY) == 0);
    return AT91C_BASE_SSC0->SSC_RHR;
}

