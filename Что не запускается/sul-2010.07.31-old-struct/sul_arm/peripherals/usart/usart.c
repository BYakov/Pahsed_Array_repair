
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _USART_H_
	#include "usart.h"
#endif

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Configures an USART peripheral with the specified parameters.
/// \param usart  Pointer to the USART peripheral to configure.
/// \param mode  Desired value for the USART mode register (see the datasheet).
/// \param baudrate  Baudrate at which the USART should operate (in Hz).
/// \param masterClock  Frequency of the system master clock (in Hz).
//------------------------------------------------------------------------------
void USART_Configure(AT91S_USART *usart,
                     unsigned int mode,
                     unsigned int baudrate,
                     unsigned int masterClock)
{
    // Reset and disable receiver & transmitter
    usart->US_CR = AT91C_US_RSTRX | AT91C_US_RSTTX | AT91C_US_RXDIS | AT91C_US_TXDIS;

    // Configure mode
    usart->US_MR = mode;

    // Configure baudrate
    // Asynchronous, no oversampling
    if (((mode & AT91C_US_SYNC) == 0) && ((mode & AT91C_US_OVER) == 0)) {
    
        usart->US_BRGR = (masterClock / baudrate) / 16;
    }
}

//------------------------------------------------------------------------------
/// Enables or disables the transmitter of an USART peripheral.
/// \param usart  Pointer to an USART peripheral
/// \param enabled  If true, the transmitter is enabled; otherwise it is
///                 disabled.
//------------------------------------------------------------------------------
void USART_SetTransmitterEnabled(AT91S_USART *usart, unsigned char enabled)
{
    if (enabled) {

        usart->US_CR = AT91C_US_TXEN;
    }
    else {

        usart->US_CR = AT91C_US_TXDIS;
    }
}

//------------------------------------------------------------------------------
/// Enables or disables the receiver of an USART peripheral
/// \param usart  Pointer to an USART peripheral
/// \param enabled  If true, the receiver is enabled; otherwise it is disabled.
//------------------------------------------------------------------------------
void USART_SetReceiverEnabled(AT91S_USART *usart, unsigned char enabled)
{
    if (enabled) {

        usart->US_CR = AT91C_US_RXEN;
    }
    else {

        usart->US_CR = AT91C_US_RXDIS;
    }
}

//------------------------------------------------------------------------------

void USART_ResetReceiver(AT91S_USART *usart)
{
   	usart->US_CR |= AT91C_US_RSTRX;
	usart->US_CR &= ~AT91C_US_RSTRX;
}

//------------------------------------------------------------------------------
/// Sends one packet of data through the specified USART peripheral. This
/// function operates synchronously, so it only returns when the data has been
/// actually sent.
/// \param usart  Pointer to an USART peripheral.
/// \param data  Data to send including 9nth bit and sync field if necessary (in
///              the same format as the US_THR register in the datasheet).
/// \param timeOut  Time out value (0 = no timeout).
//------------------------------------------------------------------------------
void USART_Write( AT91S_USART *usart, unsigned short data, volatile unsigned int timeOut )
{
    if (timeOut == 0) {

        while ((usart->US_CSR & AT91C_US_TXEMPTY) == 0);
    }
    else {

        while ((usart->US_CSR & AT91C_US_TXEMPTY) == 0) {

            if (timeOut == 0) {

                //TRACE_ERROR("USART_Write: Timed out.\n\r");
                return;
            }
            timeOut--;
        }
    }

    usart->US_THR = data;
}

//------------------------------------------------------------------------------
/// Sends the contents of a data buffer through the specified USART peripheral.
/// This function returns immediately (1 if the buffer has been queued, 0
/// otherwise); poll the ENDTX and TXBUFE bits of the USART status register
/// to check for the transfer completion.
/// \param usart  Pointer to an USART peripheral.
/// \param buffer  Pointer to the data buffer to send.
/// \param size  Size of the data buffer (in bytes).
//------------------------------------------------------------------------------
unsigned char USART_WriteBuffer( AT91S_USART *usart, void *buffer, unsigned int size)
{
    // Check if the first PDC bank is free
    if ((usart->US_TCR == 0) && (usart->US_TNCR == 0)) {

        usart->US_TPR = (unsigned int) buffer;
        usart->US_TCR = size;
        usart->US_PTCR = AT91C_PDC_TXTEN;

        return 1;
    }
    // Check if the second PDC bank is free
    else if (usart->US_TNCR == 0) {

        usart->US_TNPR = (unsigned int) buffer;
        usart->US_TNCR = size;

        return 1;
    }
    else {

        return 0;
    }
}

//------------------------------------------------------------------------------
/// Reads and return a packet of data on the specified USART peripheral. This
/// function operates asynchronously, so it waits until some data has been
/// received.
/// \param usart  Pointer to an USART peripheral.
/// \param timeOut  Time out value (0 -> no timeout).
//------------------------------------------------------------------------------
unsigned short USART_Read( AT91S_USART *usart, volatile unsigned int timeOut )
{
    if (timeOut == 0) {

        while ((usart->US_CSR & AT91C_US_RXRDY) == 0);
    }
    else {

        while ((usart->US_CSR & AT91C_US_RXRDY) == 0) {

            if (timeOut == 0) {

                //TRACE_ERROR("USART_Read: Timed out.\n\r");
                return 0;
            }
            timeOut--;
        }
    }

    return usart->US_RHR;
}

//------------------------------------------------------------------------------
/// Reads data from an USART peripheral, filling the provided buffer until it
/// becomes full. This function returns immediately with 1 if the buffer has
/// been queued for transmission; otherwise 0.
/// \param usart  Pointer to an USART peripheral.
/// \param buffer  Pointer to the buffer where the received data will be stored.
/// \param size  Size of the data buffer (in bytes).
//------------------------------------------------------------------------------
unsigned char USART_ReadBuffer(AT91S_USART *usart, void *buffer, unsigned int size )
{
	if(!buffer || !size) {
		usart->US_RCR = 0;
        usart->US_PTCR = AT91C_PDC_RXTDIS;
		return 1;
	}

    // Check if the first PDC bank is free
    if ((usart->US_RCR == 0) && (usart->US_RNCR == 0)) {

        usart->US_RPR = (unsigned int) buffer;
        usart->US_RCR = size;
        usart->US_PTCR = AT91C_PDC_RXTEN;

        return 1;
    }
    // Check if the second PDC bank is free
    else if (usart->US_RNCR == 0) {

        usart->US_RNPR = (unsigned int) buffer;
        usart->US_RNCR = size;

        return 1;
    }
    else {

        return 0;
    }
}

//------------------------------------------------------------------------------
/// Returns 1 if some data has been received and can be read from an USART;
/// otherwise returns 0.
/// \param usart  Pointer to an AT91S_USART instance.
//------------------------------------------------------------------------------
unsigned char USART_IsDataAvailable(AT91S_USART *usart)
{
    if ((usart->US_CSR & AT91C_US_RXRDY) != 0) {

        return 1;
    }
    else {

        return 0;
    }
}

//------------------------------------------------------------------------------
// Clear USART data buffer
//------------------------------------------------------------------------------

void USART_ClearDataBuffer(AT91S_USART *usart, int timeOut)
{
	do {

		USART_Read( usart, timeOut );

	} while(USART_IsDataAvailable(usart));
}

//------------------------------------------------------------------------------
/// Sends one packet of data through the specified USART peripheral. This
/// function operates synchronously, so it only returns when the data has been
/// actually sent.
/// \param usart  Pointer to an USART peripheral.
/// \param data  Data to send including 9nth bit and sync field if necessary (in
///              the same format as the US_THR register in the datasheet).
/// \param timeOut  Time out value (0 = no timeout).
//------------------------------------------------------------------------------
void USART_PutChar( AT91S_USART *usart, unsigned char c)
{
    // Wait for the transmitter to be ready  
    while ((usart->US_CSR & AT91C_US_TXEMPTY) == 0);

    // Send character    
    usart->US_THR = c;
    
    // Wait for the transfer to complete    
    while ((usart->US_CSR & AT91C_US_TXEMPTY) == 0);    
}

//------------------------------------------------------------------------------
/// Return 1 if a character can be read in USART
//------------------------------------------------------------------------------
unsigned int USART_IsRxReady(AT91S_USART *usart)
{
    return (usart->US_CSR & AT91C_US_RXRDY);
}

//------------------------------------------------------------------------------
/// Reads and returns a character from the USART.
/// \note This function is synchronous (i.e. uses polling).
/// \return Character received.
//------------------------------------------------------------------------------
unsigned char USART_GetChar(AT91S_USART *usart)
{
    while ((usart->US_CSR & AT91C_US_RXRDY) == 0);
    return usart->US_RHR;
}
