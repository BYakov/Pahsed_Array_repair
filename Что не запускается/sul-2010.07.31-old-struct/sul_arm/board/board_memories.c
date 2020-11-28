
#include <board.h>

//------------------------------------------------------------------------------
/// Dummy function to initialize and configure the SDRAM
//------------------------------------------------------------------------------
void BOARD_ConfigureSdram(unsigned char busWidth)
{
}

//------------------------------------------------------------------------------
/// Configures the EBI for NandFlash access. Pins must be configured after or
/// before calling this function.
//------------------------------------------------------------------------------
void BOARD_ConfigureNandFlash(unsigned char busWidth)
{
#if defined(CHIP_NAND_CTRL)
    AT91PS_HSMC4 pHSMC4 = AT91C_BASE_HSMC4;    
#endif
    AT91PS_HSMC4_CS pSMC = AT91C_BASE_HSMC4_CS1;

    // Open EBI clock
    AT91C_BASE_PMC->PMC_PCER = (1<< AT91C_ID_HSMC4);
 
#if defined(CHIP_NAND_CTRL)
    // Enable the Nand Flash Controller
    pHSMC4 ->HSMC4_CTRL = AT91C_HSMC4_NFCEN;
#endif
    
    pSMC->HSMC4_SETUP = 0
                    | ((0 <<  0) & AT91C_HSMC4_NWE_SETUP)
                    | ((1 <<  8) & AT91C_HSMC4_NCS_WR_SETUP)
                    | ((0 << 16) & AT91C_HSMC4_NRD_SETUP)
                    | ((1 << 24) & AT91C_HSMC4_NCS_RD_SETUP);

    pSMC->HSMC4_PULSE = 0
                    | ((2 <<  0) & AT91C_HSMC4_NWE_PULSE)
                    | ((3 <<  8) & AT91C_HSMC4_NCS_WR_PULSE)
                    | ((3 << 16) & AT91C_HSMC4_NRD_PULSE)
                    | ((4 << 24) & AT91C_HSMC4_NCS_RD_PULSE);

    pSMC->HSMC4_CYCLE = 0
                  | ((4 <<  0) & AT91C_HSMC4_NWE_CYCLE)
                  | ((7 << 16) & AT91C_HSMC4_NRD_CYCLE);

    pSMC->HSMC4_TIMINGS = 0
                    | ((1 <<  0) & AT91C_HSMC4_TCLR) // CLE to REN
                    | ((2 <<  4) & AT91C_HSMC4_TADL) // ALE to Data
                    | ((1 <<  8) & AT91C_HSMC4_TAR)  // ALE to REN
                    | ((1 << 16) & AT91C_HSMC4_TRR)  // Ready to REN
                    | ((2 << 24) & AT91C_HSMC4_TWB)  // WEN to REN
                    | (7<<28)
                    |(AT91C_HSMC4_NFSEL)              // Nand Flash Timing
                    ;
    
        
    if (busWidth == 8) {
        pSMC->HSMC4_MODE = AT91C_HSMC4_DBW_WIDTH_EIGTH_BITS | AT91C_HSMC4_READ_MODE | AT91C_HSMC4_WRITE_MODE;
    }
    else if (busWidth == 16) {
        pSMC->HSMC4_MODE = AT91C_HSMC4_DBW_WIDTH_SIXTEEN_BITS | AT91C_HSMC4_READ_MODE | AT91C_HSMC4_WRITE_MODE;
    }
}

//------------------------------------------------------------------------------
/// Function to initialize and configure the PSRAM
//------------------------------------------------------------------------------
void BOARD_ConfigurePsram(void) 
{
    const Pin pinPsram[] = {BOARD_PSRAM_PINS};
    unsigned int tmp;

    // Open EBI clock
    AT91C_BASE_PMC->PMC_PCER = (1<< AT91C_ID_HSMC4);

    // Configure I/O
    PIO_Configure(pinPsram, PIO_LISTSIZE(pinPsram));

    // Setup the PSRAM (HSMC4_EBI.CS0, 0x60000000 ~ 0x60FFFFFF)
    AT91C_BASE_HSMC4_CS0->HSMC4_SETUP = 0
                        | ((1 <<  0) & AT91C_HSMC4_NWE_SETUP)
                        | ((1 <<  8) & AT91C_HSMC4_NCS_WR_SETUP)
                        | ((1 << 16) & AT91C_HSMC4_NRD_SETUP)
                        | ((1 << 24) & AT91C_HSMC4_NCS_RD_SETUP)
                        ;
    AT91C_BASE_HSMC4_CS0->HSMC4_PULSE = 0
                        | ((5 <<  0) & AT91C_HSMC4_NWE_PULSE)
                        | ((5 <<  8) & AT91C_HSMC4_NCS_WR_PULSE)
                        | ((5 << 16) & AT91C_HSMC4_NRD_PULSE)
                        | ((5 << 24) & AT91C_HSMC4_NCS_RD_PULSE)
                        ;
    AT91C_BASE_HSMC4_CS0->HSMC4_CYCLE = 0
                        | ((6 <<  0) & AT91C_HSMC4_NWE_CYCLE)
                        | ((6 << 16) & AT91C_HSMC4_NRD_CYCLE)
                        ;

    tmp = AT91C_BASE_HSMC4_CS0->HSMC4_TIMINGS
        & (AT91C_HSMC4_OCMSEN | AT91C_HSMC4_RBNSEL | AT91C_HSMC4_NFSEL);
    AT91C_BASE_HSMC4_CS0->HSMC4_TIMINGS = tmp
                        | ((0 <<  0) & AT91C_HSMC4_TCLR) // CLE to REN
                        | ((0 <<  4) & AT91C_HSMC4_TADL) // ALE to Data
                        | ((0 <<  8) & AT91C_HSMC4_TAR)  // ALE to REN
                        | ((0 << 16) & AT91C_HSMC4_TRR)  // Ready to REN
                        | ((0 << 24) & AT91C_HSMC4_TWB)  // WEN to REN
                        ;
    tmp = AT91C_BASE_HSMC4_CS0->HSMC4_MODE & ~(AT91C_HSMC4_DBW);
    AT91C_BASE_HSMC4_CS0->HSMC4_MODE = tmp
                        | (AT91C_HSMC4_READ_MODE)
                        | (AT91C_HSMC4_WRITE_MODE)
                        | (AT91C_HSMC4_DBW_WIDTH_SIXTEEN_BITS)
                        //| (AT91C_HSMC4_PMEN)
                        ;
}

