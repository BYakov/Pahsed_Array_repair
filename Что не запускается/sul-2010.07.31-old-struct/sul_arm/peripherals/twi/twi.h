
#ifndef _TWI_H_
#define _TWI_H_

// Missing AT91C_TWI_TXRDY definition.
#ifndef AT91C_TWI_TXRDY
    #define AT91C_TWI_TXRDY   AT91C_TWI_TXRDY_MASTER
#endif

// Missing AT91C_TWI_TXCOMP definition.
#ifndef AT91C_TWI_TXCOMP
    #define AT91C_TWI_TXCOMP  AT91C_TWI_TXCOMP_MASTER
#endif

/// Returns 1 if the TXRDY bit (ready to transmit data) is set in the given
/// status register value.
#define TWI_STATUS_TXRDY(status) ((status & AT91C_TWI_TXRDY) == AT91C_TWI_TXRDY)

/// Returns 1 if the RXRDY bit (ready to receive data) is set in the given
/// status register value.
#define TWI_STATUS_RXRDY(status) ((status & AT91C_TWI_RXRDY) == AT91C_TWI_RXRDY)

/// Returns 1 if the TXCOMP bit (transfer complete) is set in the given
/// status register value.
#define TWI_STATUS_TXCOMP(status) ((status & AT91C_TWI_TXCOMP) == AT91C_TWI_TXCOMP)

extern void TWI_ConfigureMaster(AT91S_TWI *pTwi, unsigned int twck, unsigned int mck);

#ifdef AT91C_TWI_SVEN  // TWI slave
extern void TWI_ConfigureSlave(AT91S_TWI *pTwi, unsigned char slaveAddress);
#endif

extern void TWI_Stop(AT91S_TWI *pTwi);

extern void TWI_StartRead(
    AT91S_TWI *pTwi,
    unsigned char address,
    unsigned int iaddress,
    unsigned char isize);

extern unsigned char TWI_ReadByte(AT91S_TWI *pTwi);

extern void TWI_WriteByte(AT91S_TWI *pTwi, unsigned char byte);

extern void TWI_StartWrite(
    AT91S_TWI *pTwi,
    unsigned char address,
    unsigned int iaddress,
    unsigned char isize,
    unsigned char byte);

extern unsigned char TWI_ByteReceived(AT91S_TWI *pTwi);

extern unsigned char TWI_ByteSent(AT91S_TWI *pTwi);

extern unsigned char TWI_TransferComplete(AT91S_TWI *pTwi);

extern void TWI_EnableIt(AT91S_TWI *pTwi, unsigned int sources);

extern void TWI_DisableIt(AT91S_TWI *pTwi, unsigned int sources);

extern unsigned int TWI_GetStatus(AT91S_TWI *pTwi);

extern unsigned int TWI_GetMaskedStatus(AT91S_TWI *pTwi);

extern void TWI_SendSTOPCondition(AT91S_TWI *pTwi);

#endif //#ifndef TWI_H
