
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

//------------------------------------------------------------------------------
//         Types
//------------------------------------------------------------------------------

/// Function prototype for exception table items - interrupt handler.
//typedef void( *IrqHandler )( void );
typedef void( *IntFunc )( void );

/// Weak attribute

#if defined   ( __CC_ARM   )
    #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ )
    #define WEAK __weak
#elif defined (  __GNUC__  )
    #define WEAK __attribute__ ((weak))
#endif

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Exception Handlers
//------------------------------------------------------------------------------

extern WEAK void NMI_Handler( void );
extern WEAK void HardFault_Handler( void );
extern WEAK void MemManage_Handler( void );
extern WEAK void BusFault_Handler( void );
extern WEAK void UsageFault_Handler( void );
extern WEAK void SVC_Handler( void );
extern WEAK void DebugMon_Handler( void );
extern WEAK void PendSV_Handler( void );
extern WEAK void SysTick_Handler( void );
void IrqHandlerNotUsed(void);


// System Controller
extern void SYS_IrqHandler(void);
// SUPPLY CONTROLLER
extern WEAK void SUPC_IrqHandler(void);
// RESET CONTROLLER
extern WEAK void RSTC_IrqHandler(void);
// REAL TIME CLOCK
extern WEAK void RTC_IrqHandler(void);
// REAL TIME TIMER
extern WEAK void RTT_IrqHandler(void);
// WATCHDOG TIMER
extern WEAK void WDT_IrqHandler(void);
// PMC
extern WEAK void PMC_IrqHandler(void);
// EFC0
extern WEAK void EFC0_IrqHandler(void);
// EFC1
extern WEAK void EFC1_IrqHandler(void);
// DBGU
extern WEAK void DBGU_IrqHandler(void);
// HSMC4
extern WEAK void HSMC4_IrqHandler(void);
// Parallel IO Controller A
extern WEAK void PIOA_IrqHandler(void);
// Parallel IO Controller B
extern WEAK void PIOB_IrqHandler(void);
// Parallel IO Controller C
extern WEAK void PIOC_IrqHandler(void);
// USART 0
extern WEAK void USART0_IrqHandler(void);
// USART 1
extern WEAK void USART1_IrqTokenHandler(void);
extern WEAK void USART1_IrqDataHandler(void);
// USART 2
extern WEAK void USART2_IrqHandler(void);
// USART 3
extern WEAK void USART3_IrqHandler(void);
// Multimedia Card Interface
extern WEAK void MCI0_IrqHandler(void);
// TWI 0
extern WEAK void TWI0_IrqHandler(void);
// TWI 1
extern WEAK void TWI1_IrqHandler(void);
// Serial Peripheral Interface 0
extern WEAK void SPI0_IrqHandler(void);
// Serial Synchronous Controller 0
extern WEAK void SSC0_IrqHandler(void);
// Timer Counter 0
extern WEAK void TC0_IrqHandler(void);
// Timer Counter 1
extern WEAK void TC1_IrqHandler(void);
// Timer Counter 2
extern WEAK void TC2_IrqHandler(void);
// PWM Controller
extern WEAK void PWM_IrqHandler(void);
// ADC controller0
extern WEAK void ADCC0_IrqHandler(void);
// ADC controller1
extern WEAK void ADCC1_IrqHandler(void);
// HDMA
extern WEAK void HDMA_IrqHandler(void);
// USB Device High Speed UDP_HS
extern WEAK void UDPD_IrqHandler(void);

//-----------------------------------------------------------------------------
void wait_usart_irq_flag(void);
void set_usart_irq_flag(void);
void reset_usart_irq_flag(void);
//-----------------------------------------------------------------------------

#endif //_EXCEPTIONS_H_
