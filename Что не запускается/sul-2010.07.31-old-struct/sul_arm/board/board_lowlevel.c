
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _BOARD_MEMORIES_H_
	#include "board_memories.h"
#endif

#ifndef _BOARD_LOWLEVEL_H_
	#include "board_lowlevel.h"
#endif

//------------------------------------------------------------------------------
//         Local definitions
//------------------------------------------------------------------------------

// Settings at 96/96MHz

#define AT91C_CKGR_MUL_SHIFT        16
#define AT91C_CKGR_STMODE_SHIFT     14
#define AT91C_CKGR_PLLCOUNT_SHIFT   8
#define AT91C_CKGR_DIV_SHIFT        0

#define BOARD_PLLR 				((1 << 29) | \
								(0x7  << AT91C_CKGR_MUL_SHIFT) | \
								(0x0  << AT91C_CKGR_STMODE_SHIFT) | \
								(0x3f << AT91C_CKGR_PLLCOUNT_SHIFT) | \
								(0x1  << AT91C_CKGR_DIV_SHIFT))							

// Selected clock from PLLA source ( 0x0 | 0x2 )
#define BOARD_MCKR 				(AT91C_PMC_PRES_CLK | AT91C_PMC_CSS_PLLA_CLK)
//#define BOARD_MCKR 				(AT91C_PMC_PRES_CLK_2 | AT91C_PMC_CSS_PLLA_CLK)

#define BOARD_OSCOUNT         	(AT91C_CKGR_MOSCXTST & (0x3F << 8))

// Define clock timeout
#define CLOCK_TIMEOUT           0xffffffff

// External crystal oscillator
#define EXTERNAL_FREQ           12000000

// Main RC generator frequency
#define MOSCRCF_4MHZ           	(0 << 4)
#define MOSCRCF_8MHZ           	(1 << 4)
#define MOSCRCF_12MHZ           (2 << 4)

//------------------------------------------------------------------------------
/// After POR, at91sam3u device is running on 4MHz internal RC
/// At the end of the LowLevelInit procedure MCK = 96MHz PLLA = 96 CPU = 96MHz
/// Performs the low-level initialization of the chip. This includes EFC, master
/// clock, IRQ & watchdog configuration.
//------------------------------------------------------------------------------

void LowLevelInit(void)
{		
    unsigned int timeout = 0;

    // Set 3 WS for Embedded Flash Access (Wait states: FWS+1)
    AT91C_BASE_EFC0->EFC_FMR = AT91C_EFC_FWS_2WS;
    AT91C_BASE_EFC1->EFC_FMR = AT91C_EFC_FWS_2WS;

    // Watchdog initialization (disable WDT)
    AT91C_BASE_WDTC->WDTC_WDMR = AT91C_WDTC_WDDIS;

    // Initialize main oscillator
    if(!(AT91C_BASE_PMC->PMC_MOR & AT91C_CKGR_MOSCSEL))
    {
		// generator will be active after 15.75 ms (BOARD_OSCOUNT * 0.25)
        AT91C_BASE_PMC->PMC_MOR = (0x37 << 16) | BOARD_OSCOUNT | AT91C_CKGR_MOSCRCEN | AT91C_CKGR_MOSCXTEN | MOSCRCF_4MHZ;
        timeout = 0;
		// wait Main XTAL Oscillator Status or timeout
        while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCXTS) && (timeout++ < CLOCK_TIMEOUT));
    }

    // Switch to main oscillator frequency (set MOSCSEL in PMC_MOR)
    AT91C_BASE_PMC->PMC_MOR = (0x37 << 16) | BOARD_OSCOUNT | AT91C_CKGR_MOSCRCEN | AT91C_CKGR_MOSCXTEN | MOSCRCF_4MHZ | AT91C_CKGR_MOSCSEL;
    timeout = 0;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MOSCSELS) && (timeout++ < CLOCK_TIMEOUT));

	// Set master clock source on Main clock in PMC_MCKR (set CSS in PMC_MCKR)
    AT91C_BASE_PMC->PMC_MCKR = (AT91C_BASE_PMC->PMC_MCKR & ~AT91C_PMC_CSS) | AT91C_PMC_CSS_MAIN_CLK;
    timeout = 0;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) && (timeout++ < CLOCK_TIMEOUT));

    // Initialize PLLA: DIVA=1, PLLACOUNT=63, STMODE=0, MULA=7
    AT91C_BASE_PMC->PMC_PLLAR = BOARD_PLLR;
    timeout = 0;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKA) && (timeout++ < CLOCK_TIMEOUT));

	// Initialize UTMI for USB usage
    //AT91C_BASE_CKGR->CKGR_UCKR |= (AT91C_CKGR_UPLLCOUNT & (3 << 20)) | AT91C_CKGR_UPLLEN;
    //timeout = 0;
    //while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKU) && (timeout++ < CLOCK_TIMEOUT));

    // Switch to fast clock (step 1. Program PRES, see doc6430.pdf page 484)
    AT91C_BASE_PMC->PMC_MCKR = (BOARD_MCKR & ~AT91C_PMC_CSS) | AT91C_PMC_CSS_MAIN_CLK;
    timeout = 0;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) && (timeout++ < CLOCK_TIMEOUT));

	// Switch to fast clock (step 2. Program CSS, see doc6430.pdf page 484)
    AT91C_BASE_PMC->PMC_MCKR = BOARD_MCKR;
    timeout = 0;
    while (!(AT91C_BASE_PMC->PMC_SR & AT91C_PMC_MCKRDY) && (timeout++ < CLOCK_TIMEOUT));

    // Optimize CPU setting for speed
    SetDefaultMaster(1);
}

//------------------------------------------------------------------------------
/// Enable or disable default master access
/// \param enalbe 1 enable defaultMaster settings, 0 disable it.
//------------------------------------------------------------------------------
void SetDefaultMaster(unsigned char enable)
{
    AT91PS_HMATRIX2 pMatrix = AT91C_BASE_MATRIX;

    // Set default master
    if (enable == 1) {

        // Set default master: SRAM0 -> Cortex-M3 System
        pMatrix->HMATRIX2_SCFG0 |= AT91C_MATRIX_FIXED_DEFMSTR_SCFG0_ARMS |
                                   AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR;
        
        // Set default master: SRAM1 -> Cortex-M3 System
        pMatrix->HMATRIX2_SCFG1 |= AT91C_MATRIX_FIXED_DEFMSTR_SCFG1_ARMS |
                                   AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR;

        // Set default master: Internal flash0 -> Cortex-M3 Instruction/Data
        pMatrix->HMATRIX2_SCFG3 |= AT91C_MATRIX_FIXED_DEFMSTR_SCFG3_ARMC |
                                   AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR;
    } else {

        // Clear default master: SRAM0 -> Cortex-M3 System
        pMatrix->HMATRIX2_SCFG0 &= (~AT91C_MATRIX_DEFMSTR_TYPE);
        
        // Clear default master: SRAM1 -> Cortex-M3 System
        pMatrix->HMATRIX2_SCFG1 &= (~AT91C_MATRIX_DEFMSTR_TYPE);

        // Clear default master: Internal flash0 -> Cortex-M3 Instruction/Data
        pMatrix->HMATRIX2_SCFG3 &= (~AT91C_MATRIX_DEFMSTR_TYPE);
    }
}

//------------------------------------------------------------------------------
// Set flash wait state					
//------------------------------------------------------------------------------
void SetFlashWaitState(unsigned char ws)
{
    // Set Wait State for Embedded Flash Access
	AT91C_BASE_EFC0->EFC_FMR = ((ws << 8) & AT91C_EFC_FWS);
	AT91C_BASE_EFC1->EFC_FMR = ((ws << 8) & AT91C_EFC_FWS);
}

