

#ifndef _BOARD_H_
	#include <board.h>
#endif

//------------------------------------------------------------------------------
/// Initializes the DBGU with the given parameters, and enables both the
/// transmitter and the receiver. The mode parameter contains the value of the
/// DBGU_MR register.
/// Value DBGU_STANDARD can be used for mode to get the most common configuration
/// (i.e. aysnchronous, 8bits, no parity, 1 stop bit, no flow control).
/// \param mode  Operating mode to configure.
/// \param baudrate  Desired baudrate (e.g. 115200).
/// \param mck  Frequency of the system master clock in Hz.
//------------------------------------------------------------------------------
void DBGU_Configure(
    unsigned int mode,
    unsigned int baudrate,
    unsigned int mck)
{
    #if defined(cortexm3)
    // Enable clock for UART
    AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_DBGU);
    #endif

    // Reset & disable receiver and transmitter, disable interrupts
    AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RSTRX | AT91C_US_RSTTX;
    AT91C_BASE_DBGU->DBGU_IDR = 0xFFFFFFFF;
    
    // Configure baud rate
    AT91C_BASE_DBGU->DBGU_BRGR = mck / (baudrate * 16);
    
    // Configure mode register
    AT91C_BASE_DBGU->DBGU_MR = mode;
    
    // Disable DMA channel
    AT91C_BASE_DBGU->DBGU_PTCR = AT91C_PDC_RXTDIS | AT91C_PDC_TXTDIS;

    // Enable receiver and transmitter
    AT91C_BASE_DBGU->DBGU_CR = AT91C_US_RXEN | AT91C_US_TXEN;
}

//------------------------------------------------------------------------------
/// Outputs a character on the DBGU line.
/// \note This function is synchronous (i.e. uses polling).
/// \param c  Character to send.
//------------------------------------------------------------------------------
void DBGU_PutChar(unsigned char c)
{
    // Wait for the transmitter to be ready
    while ((AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXEMPTY) == 0);
    
    // Send character
    AT91C_BASE_DBGU->DBGU_THR = c;
    
    // Wait for the transfer to complete
    while ((AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_TXEMPTY) == 0);
}

//------------------------------------------------------------------------------
/// Return 1 if a character can be read in DBGU
//------------------------------------------------------------------------------
unsigned int DBGU_IsRxReady()
{
    return (AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY);
}

//------------------------------------------------------------------------------
/// Reads and returns a character from the DBGU.
/// \note This function is synchronous (i.e. uses polling).
/// \return Character received.
//------------------------------------------------------------------------------
unsigned char DBGU_GetChar(void)
{
    while ((AT91C_BASE_DBGU->DBGU_CSR & AT91C_US_RXRDY) == 0);
    return AT91C_BASE_DBGU->DBGU_RHR;
}



