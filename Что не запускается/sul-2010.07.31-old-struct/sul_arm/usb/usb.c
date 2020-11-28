

#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _USB_H_
	#include "usb.h"
#endif

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

void USB_DisableClock(void)
{
	// Disable clock
    AT91C_BASE_PMC->PMC_PCDR = (1 << AT91C_ID_UDPHS);
    // 480MHZ
    AT91C_BASE_CKGR->CKGR_UCKR &= ~AT91C_CKGR_UPLLEN;
}

//---------------------------------------------------------------------------------------

void USB_EnableClock(void)
{
	//Enable USB clock
    AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_UDPHS);
    // Enable 480MHZ
    AT91C_BASE_CKGR->CKGR_UCKR |= ((0xf << 20) & (3 << 20)) | AT91C_CKGR_UPLLEN;
    // Wait until UTMI PLL is locked
    while ((AT91C_BASE_PMC->PMC_SR & AT91C_PMC_LOCKU) == 0);
}

//---------------------------------------------------------------------------------------

void USB_Init(void)
{
	int i = 0;
	//int err = 3;

	USB_EnableClock();

    // Configure the pull-up on D+ and disconnect it
    AT91C_BASE_UDPHS->UDPHS_CTRL |= AT91C_UDPHS_DETACH; 	// detach
    AT91C_BASE_UDPHS->UDPHS_CTRL |= AT91C_UDPHS_PULLD_DIS; 	// Disable Pull Down

    // Reset and enable IP UDPHS
    AT91C_BASE_UDPHS->UDPHS_CTRL &= ~AT91C_UDPHS_EN_UDPHS;
    AT91C_BASE_UDPHS->UDPHS_CTRL |= AT91C_UDPHS_EN_UDPHS;

    // Initialization of DMA
    for( i=1; i<=((AT91C_BASE_UDPHS->UDPHS_IPFEATURES & AT91C_UDPHS_DMA_CHANNEL_NBR)>>4); i++ ) {

        // RESET endpoint canal DMA:
        // DMA stop channel command
        AT91C_BASE_UDPHS->UDPHS_DMA[i].UDPHS_DMACONTROL = 0;  // STOP command

        // Disable endpoint
        AT91C_BASE_UDPHS->UDPHS_EPT[i].UDPHS_EPTCTLDIS = AT91C_UDPHS_SHRT_PCKT
                                                       | AT91C_UDPHS_BUSY_BANK
                                                       | AT91C_UDPHS_NAK_OUT
                                                       | AT91C_UDPHS_NAK_IN
                                                       | AT91C_UDPHS_STALL_SNT
                                                       | AT91C_UDPHS_RX_SETUP
                                                       | AT91C_UDPHS_TX_PK_RDY
                                                       | AT91C_UDPHS_TX_COMPLT
                                                       | AT91C_UDPHS_RX_BK_RDY
                                                       | AT91C_UDPHS_ERR_OVFLW
                                                       | AT91C_UDPHS_MDATA_RX
                                                       | AT91C_UDPHS_DATAX_RX
                                                       | AT91C_UDPHS_NYET_DIS
                                                       | AT91C_UDPHS_INTDIS_DMA
                                                       | AT91C_UDPHS_AUTO_VALID
                                                       | AT91C_UDPHS_EPT_DISABL;

        // Clear status endpoint
        AT91C_BASE_UDPHS->UDPHS_EPT[i].UDPHS_EPTCLRSTA = AT91C_UDPHS_TOGGLESQ
                                                       | AT91C_UDPHS_FRCESTALL
                                                       | AT91C_UDPHS_RX_BK_RDY
                                                       | AT91C_UDPHS_TX_COMPLT
                                                       | AT91C_UDPHS_RX_SETUP
                                                       | AT91C_UDPHS_STALL_SNT
                                                       | AT91C_UDPHS_NAK_IN
                                                       | AT91C_UDPHS_NAK_OUT;

        // Reset endpoint config
        AT91C_BASE_UDPHS->UDPHS_EPT[i].UDPHS_EPTCTLENB = 0;

        // Reset DMA channel (Buff count and Control field)
        AT91C_BASE_UDPHS->UDPHS_DMA[i].UDPHS_DMACONTROL = AT91C_UDPHS_LDNXT_DSC;  // NON STOP command

        // Reset DMA channel 0 (STOP)
        AT91C_BASE_UDPHS->UDPHS_DMA[i].UDPHS_DMACONTROL = 0;  // STOP command

        // Clear DMA channel status (read the register for clear it)
        AT91C_BASE_UDPHS->UDPHS_DMA[i].UDPHS_DMASTATUS = AT91C_BASE_UDPHS->UDPHS_DMA[i].UDPHS_DMASTATUS;

    }
	
    AT91C_BASE_UDPHS->UDPHS_TST = AT91C_UDPHS_SPEED_CFG_FS;
    AT91C_BASE_UDPHS->UDPHS_IEN = 0;
    AT91C_BASE_UDPHS->UDPHS_CLRINT = AT91C_UDPHS_UPSTR_RES
                                   | AT91C_UDPHS_ENDOFRSM
                                   | AT91C_UDPHS_WAKE_UP
                                   | AT91C_UDPHS_ENDRESET
                                   | AT91C_UDPHS_IEN_SOF
                                   | AT91C_UDPHS_MICRO_SOF
                                   | AT91C_UDPHS_DET_SUSPD;
    
    // Disable interrupts
    AT91C_BASE_UDPHS->UDPHS_IEN = AT91C_UDPHS_ENDOFRSM
                                | AT91C_UDPHS_WAKE_UP
                                | AT91C_UDPHS_DET_SUSPD;

	// Disable clock
	//USB_DisableClock();

    // Configure and enable the UDPHS interrupt
    IRQ_ConfigureIT(AT91C_ID_UDPHS, 0, UDPD_IrqHandler);//, UDPD_IrqHandler);
    IRQ_EnableIT(AT91C_ID_UDPHS);

	// Control endpoint
	AT91C_BASE_UDPHS->UDPHS_EPT[0].UDPHS_EPTCFG = 	AT91C_UDPHS_EPT_SIZE_64 | 
													AT91C_UDPHS_EPT_TYPE_CTL_EPT | 
													AT91C_UDPHS_BK_NUMBER_1;
	// Bulk OUT endpoint
	AT91C_BASE_UDPHS->UDPHS_EPT[1].UDPHS_EPTCFG = 	AT91C_UDPHS_EPT_SIZE_256 | 
													AT91C_UDPHS_EPT_DIR_OUT | 
													AT91C_UDPHS_EPT_TYPE_BUL_EPT | 
													AT91C_UDPHS_BK_NUMBER_2;

	// Bulk OUT endpoint
	AT91C_BASE_UDPHS->UDPHS_EPT[2].UDPHS_EPTCFG = 	AT91C_UDPHS_EPT_SIZE_256 | 
													AT91C_UDPHS_EPT_DIR_IN | 
													AT91C_UDPHS_EPT_TYPE_BUL_EPT | 
													AT91C_UDPHS_BK_NUMBER_2;
	for(i=0; i<3; i++) {
		unsigned int status = AT91C_BASE_UDPHS->UDPHS_EPT[i].UDPHS_EPTCFG;
		if(status & AT91C_UDPHS_EPT_MAPD) {
			status = 0;
		}
	}

	AT91C_BASE_UDPHS->UDPHS_EPT[0].UDPHS_EPTCTLENB |= AT91C_UDPHS_EPT_ENABL;
	AT91C_BASE_UDPHS->UDPHS_EPT[1].UDPHS_EPTCTLENB |= AT91C_UDPHS_EPT_ENABL | AT91C_UDPHS_AUTO_VALID;
	AT91C_BASE_UDPHS->UDPHS_EPT[2].UDPHS_EPTCTLENB |= AT91C_UDPHS_EPT_ENABL | AT91C_UDPHS_AUTO_VALID;
}

//---------------------------------------------------------------------------------------
