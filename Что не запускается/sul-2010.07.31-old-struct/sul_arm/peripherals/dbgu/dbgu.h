//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
/// 
/// This module provides definitions and functions for using the Debug Unit
/// (DBGU).
///
/// It also overloads the fputc(), fputs() & putchar() functions so the printf()
/// method outputs its data on the DBGU. This behavior can be suppressed by
/// defining NOFPUT during compilation.
///
/// !Usage
/// 
/// -# Enable the DBGU pins (see pio & board.h).
/// -# Configure the DBGU using DBGU_Configure with the desired operating mode.
/// -# Send characters using DBGU_PutChar() or the printf() method.
/// -# Receive characters using DBGU_GetChar().
///
/// \note Unless specified, all the functions defined here operate synchronously;
/// i.e. they all wait the data is sent/received before returning.
//------------------------------------------------------------------------------

#ifndef DBGU_H
#define DBGU_H

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------
 
/// Standard operating mode (asynchronous, 8bit, no parity, 1 stop bit)
#define DBGU_STANDARD           AT91C_US_PAR_NONE

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void DBGU_Configure(
    unsigned int mode,
    unsigned int baudrate,
    unsigned int mck);

extern unsigned char DBGU_GetChar(void);

extern void DBGU_PutChar(unsigned char c);

extern unsigned int DBGU_IsRxReady(void);

#endif //#ifndef DBGU_H

