
#ifndef _SYSTICK_H_
#define _SYSTICK_H_



//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

/// Vendor define it's own SysTickConfig function
#define __Vendor_SysTickConfig     1

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void SysTick_Configure(unsigned char countEnable,
                           unsigned int reloadValue,
                           void( *handler )( void ));

#endif //#ifndef SYSTICK_H
