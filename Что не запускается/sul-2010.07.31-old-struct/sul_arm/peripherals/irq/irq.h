
#ifndef _IRQ_H_
#define _IRQ_H_

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#ifndef _BOARD_H_
	#include <board.h>
#endif

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void IRQ_ConfigureIT(unsigned int source,
                            unsigned int mode,         // mode for AIC, priority for NVIC
                            void( *handler )( void )); // ISR

extern void IRQ_EnableIT(unsigned int source);

extern void IRQ_DisableIT(unsigned int source);

#endif //#ifndef _IRQ_H_

