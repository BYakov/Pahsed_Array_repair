
#include <stdio.h>

#ifndef _BOARD_H_
	#include <board.h>
#endif
#include "exceptions.h"
#include "board_lowlevel.h"

//------------------------------------------------------------------------------
//         Types
//------------------------------------------------------------------------------
typedef union { IntFunc __fun; void * __ptr; } IrqVector;

//------------------------------------------------------------------------------
//         ProtoTypes
//------------------------------------------------------------------------------
extern int Image$$ARM_LIB_STACK$$ZI$$Limit;
extern int Image$$Vector_region$$Base;
extern int Image$$Vector_region$$Limit;
extern int Image$$Relocate_region$$Base;
//extern int Image$$Relocate_region$$Limit;

//extern int Image$$Fixed_region$$Base;
//extern int Image$$Fixed_region$$Limit;

extern void __main(void);
void resetHandler( void );

//------------------------------------------------------------------------------
//         Variables
//------------------------------------------------------------------------------

#pragma arm section rodata="vectors"
const IrqVector __vector_table[] =
{
    (IntFunc)&Image$$ARM_LIB_STACK$$ZI$$Limit,
    resetHandler,

    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,             // Reserved
    SVC_Handler,
    DebugMon_Handler,
    0,                      // Reserved
    PendSV_Handler,
    SysTick_Handler,

    // Configurable interrupts
    SUPC_IrqHandler,    // 0  SUPPLY CONTROLLER
    RSTC_IrqHandler,    // 1  RESET CONTROLLER
    RTC_IrqHandler,     // 2  REAL TIME CLOCK
    RTT_IrqHandler,     // 3  REAL TIME TIMER
    WDT_IrqHandler,     // 4  WATCHDOG TIMER
    PMC_IrqHandler,     // 5  PMC
    EFC0_IrqHandler,    // 6  EFC0
    EFC1_IrqHandler,    // 7  EFC1
    DBGU_IrqHandler,    // 8  DBGU
    HSMC4_IrqHandler,   // 9  HSMC4
    PIOA_IrqHandler,    // 10 Parallel IO Controller A
    PIOB_IrqHandler,    // 11 Parallel IO Controller B
    PIOC_IrqHandler,    // 12 Parallel IO Controller C
    USART0_IrqHandler,  // 13 USART 0
    USART1_IrqTokenHandler,  // 14 USART 1
	USART2_IrqHandler,  // 15 USART 2
    USART3_IrqHandler,  // 16 USART 3
    MCI0_IrqHandler,    // 17 Multimedia Card Interface
    TWI0_IrqHandler,    // 18 TWI 0
    TWI1_IrqHandler,    // 19 TWI 1
    SPI0_IrqHandler,    // 20 Serial Peripheral Interface
    SSC0_IrqHandler,    // 21 Serial Synchronous Controller 0
    TC0_IrqHandler,     // 22 Timer Counter 0
    TC1_IrqHandler,     // 23 Timer Counter 1
    TC2_IrqHandler,     // 24 Timer Counter 2
    PWM_IrqHandler,     // 25 Pulse Width Modulation Controller
    ADCC0_IrqHandler,   // 26 ADC controller0
    ADCC1_IrqHandler,   // 27 ADC controller1
    HDMA_IrqHandler,    // 28 HDMA
    UDPD_IrqHandler,   // 29 USB Device High Speed UDP_HS
    IrqHandlerNotUsed   // 30 not used
};
#pragma arm section

//------------------------------------------------------------------------------
/// This is the code that gets called on processor reset. To initialize the
/// device.
//------------------------------------------------------------------------------

void resetHandler( void )
{
    unsigned int *pSrc = (unsigned int *)&Image$$Vector_region$$Base;
    unsigned int *pVec = (unsigned int *)0x20000000;
	unsigned int Size = ((unsigned int*)&Image$$Vector_region$$Limit - (unsigned int *)&Image$$Vector_region$$Base);
	unsigned int i = 0;

	// Copy vector table in the SRAM0
	if(pSrc != pVec) {
		for(i=0; i<Size/4; i++)
			pVec[i] = pSrc[i];
	}

	LowLevelInit();

	// Copy vector table in the SRAM0
	if(pSrc != pVec) {
		AT91C_BASE_NVIC->NVIC_VTOFFR = ((unsigned int)(pVec)) | (0x0 << 7);
	} else {
		AT91C_BASE_NVIC->NVIC_VTOFFR = ((unsigned int)(pSrc)) | (0x0 << 7);
	}

    __main();
}

//------------------------------------------------------------------------------

unsigned int *GetExceptionTable(void)
{
	//return (unsigned int *)&Image$$Vector_region$$Base;
	return (unsigned int *)0x20000000;
}

