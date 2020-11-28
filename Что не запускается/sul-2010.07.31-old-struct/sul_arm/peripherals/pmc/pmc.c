
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _PMC_H_
	#include "pmc.h"
#endif

#ifdef CP15_PRESENT
	#include <cp15/cp15.h>
#endif

#define MASK_STATUS 0x3FFFFFFC

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

#if defined(at91sam7l64) || defined(at91sam7l128)
//------------------------------------------------------------------------------
/// Sets the fast wake-up inputs that can get the device out of Wait mode.
/// \param inputs  Fast wake-up inputs to enable.
//------------------------------------------------------------------------------
void PMC_SetFastWakeUpInputs(unsigned int inputs)
{
    SANITY_CHECK((inputs & ~0xFF) == 0);
    AT91C_BASE_PMC->PMC_FSMR = inputs;
}

#if !defined(__ICCARM__)
__attribute__ ((section (".ramfunc"))) // GCC
#endif
//------------------------------------------------------------------------------
/// Disables the main oscillator, making the device enter Wait mode.
//------------------------------------------------------------------------------
void PMC_DisableMainOscillatorForWaitMode(void)
{
    AT91C_BASE_PMC->PMC_MOR = 0x37 << 16;
    while ((AT91C_BASE_PMC->PMC_MOR & AT91C_PMC_MAINSELS) != AT91C_PMC_MAINSELS);
}

#endif

#if defined(at91sam7l)
//------------------------------------------------------------------------------
/// Disables the main oscillator when NOT running on it.
//------------------------------------------------------------------------------
void PMC_DisableMainOscillator(void)
{
    AT91C_BASE_PMC->PMC_MOR = 0x37 << 16;
    while ((AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MAINSELS) == AT91C_PMC_MAINSELS);
}
#endif

//------------------------------------------------------------------------------
/// Disables the processor clock
//------------------------------------------------------------------------------
void PMC_DisableProcessorClock(void)
{    
    AT91C_BASE_PMC->PMC_SCDR = AT91C_PMC_PCK;   
    while ((AT91C_BASE_PMC->PMC_SCSR & AT91C_PMC_PCK) != AT91C_PMC_PCK); 
}

//------------------------------------------------------------------------------
/// Enables the clock of a peripheral. The peripheral ID (AT91C_ID_xxx) is used
/// to identify which peripheral is targetted.
/// Note that the ID must NOT be shifted (i.e. 1 << AT91C_ID_xxx).
/// \param id  Peripheral ID (AT91C_ID_xxx).
//------------------------------------------------------------------------------
void PMC_EnablePeripheral(unsigned int id)
{
    if ((AT91C_BASE_PMC->PMC_PCSR & (1 << id)) == (1 << id)) {

        //TRACE_INFO("PMC_EnablePeripheral: clock of peripheral"
        //           " %u is already enabled\n\r",
        //           id);
    }
    else {

        AT91C_BASE_PMC->PMC_PCER = 1 << id;
    }
}

//------------------------------------------------------------------------------
/// Disables the clock of a peripheral. The peripheral ID (AT91C_ID_xxx) is used
/// to identify which peripheral is targetted.
/// Note that the ID must NOT be shifted (i.e. 1 << AT91C_ID_xxx).
/// \param id  Peripheral ID (AT91C_ID_xxx).
//------------------------------------------------------------------------------
void PMC_DisablePeripheral(unsigned int id)
{
    //SANITY_CHECK(id < 32);

    if ((AT91C_BASE_PMC->PMC_PCSR & (1 << id)) != (1 << id)) {

        //TRACE_INFO("PMC_DisablePeripheral: clock of peripheral"
        //           " %u is not enabled\n\r",
        //           id);
    }
    else {

        AT91C_BASE_PMC->PMC_PCDR = 1 << id;
    }
}

//------------------------------------------------------------------------------
/// Enable all the periph clock via PMC
/// (Becareful of the last 2 bits, it is not periph clock)
//------------------------------------------------------------------------------
void PMC_EnableAllPeripherals(void)
{
    AT91C_BASE_PMC->PMC_PCER = MASK_STATUS;
    while( (AT91C_BASE_PMC->PMC_PCSR & MASK_STATUS) != MASK_STATUS);
    //TRACE_INFO("Enable all periph clocks\n\r"); 
}

//------------------------------------------------------------------------------
/// Disable all the periph clock via PMC
/// (Becareful of the last 2 bits, it is not periph clock)
//------------------------------------------------------------------------------
void PMC_DisableAllPeripherals(void)
{
    AT91C_BASE_PMC->PMC_PCDR = MASK_STATUS;
    while((AT91C_BASE_PMC->PMC_PCSR & MASK_STATUS) != 0);
    //TRACE_INFO("Disable all periph clocks\n\r");
}

//-----------------------------------------------------------------------------
/// Get Periph Status
//-----------------------------------------------------------------------------
unsigned int PMC_IsAllPeriphEnabled(void)
{
    return (AT91C_BASE_PMC->PMC_PCSR == MASK_STATUS);
}

//-----------------------------------------------------------------------------
/// Get Periph Status
//-----------------------------------------------------------------------------
unsigned int PMC_IsPeriphEnabled(unsigned int id)
{
    return (AT91C_BASE_PMC->PMC_PCSR & (1 << id));  
}
//------------------------------------------------------------------------------
/// Put the CPU in Idle Mode for lower consumption
//------------------------------------------------------------------------------
void PMC_CPUInIdleMode(void)
{
#ifndef CP15_PRESENT	
    PMC_DisableProcessorClock();
#else
    AT91C_BASE_PMC->PMC_SCDR = AT91C_PMC_PCK; 
    CP15_WaitForInterrupt();
#endif
}


