
#ifndef _USART_H_
#define _USART_H_

extern void USART_Configure(
    AT91S_USART *usart,
    unsigned int mode,
    unsigned int baudrate,
    unsigned int masterClock);

extern void USART_SetTransmitterEnabled(AT91S_USART *usart, unsigned char enabled);

extern void USART_SetReceiverEnabled(AT91S_USART *usart, unsigned char enabled);

extern void USART_ResetReceiver(AT91S_USART *usart);

extern void USART_Write(
    AT91S_USART *usart, 
    unsigned short data, 
    volatile unsigned int timeOut);

extern unsigned char USART_WriteBuffer(
    AT91S_USART *usart,
    void *buffer,
    unsigned int size);

extern unsigned short USART_Read(
    AT91S_USART *usart, 
    volatile unsigned int timeOut);

extern unsigned char USART_ReadBuffer(
    AT91S_USART *usart,
    void *buffer,
    unsigned int size);

extern unsigned char USART_IsDataAvailable(AT91S_USART *usart);

extern void USART_ClearDataBuffer(AT91S_USART *usart, int timeOut);

extern void USART_SetIrdaFilter(AT91S_USART *pUsart, unsigned char filter);

extern void USART_PutChar(AT91S_USART *usart, unsigned char c);

extern unsigned int USART_IsRxReady(AT91S_USART *usart);

extern unsigned char USART_GetChar(AT91S_USART *usart);

//-----------------------------------------------------------------------------

#endif //#ifndef _USART_H_

