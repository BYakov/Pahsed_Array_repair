

#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef __CM3_CORE_H__
	#include <core_cm3.h>
#endif

#ifndef _SYSTICK_H_
	#include "systick.h"
#endif

//------------------------------------------------------------------------------
/// Configures the SysTick in .
/// \param countEnable  Enable SysTick counting.
/// \param reloadValue  Value used for tick counter to reload.
/// \param handler      Interrupt handler function, 0 to disable interrupt.
//------------------------------------------------------------------------------
void SysTick_Configure(unsigned char countEnable,
                       unsigned int reloadValue,
                       void( *handler )( void ))
{
    unsigned int intEnable = handler ? AT91C_NVIC_STICKINT : 0;

    // Disable the SysTick & using core source
    AT91C_BASE_NVIC->NVIC_STICKCSR = AT91C_NVIC_STICKCLKSOURCE;

    // Reset the current value
    AT91C_BASE_NVIC->NVIC_STICKCVR &= ~AT91C_NVIC_STICKCURRENT;

    // Setup the reload value
    AT91C_BASE_NVIC->NVIC_STICKRVR = reloadValue;

    // Enable the SysTick
    AT91C_BASE_NVIC->NVIC_STICKCSR =  AT91C_NVIC_STICKCLKSOURCE
                                    | AT91C_NVIC_STICKENABLE
                                    | intEnable;

}
