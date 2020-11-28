
#ifndef _BOARD_H_
#define _BOARD_H_

//------------------------------------------------------------------------------
//         	Headers
//------------------------------------------------------------------------------

#if defined(at91sam3u4)
    #include "chip.h"
    #include "AT91SAM3U4.h"
#else
    #error Board does not support the specified chip.
#endif

#ifndef IRQ_H
	#include "irq.h"
#endif

#ifndef _EXCEPTIONS_H_
	#include "exceptions.h"
#endif
#ifndef _EXCHANGE_H_
	#include "exchange.h"
#endif 
#ifndef _LED_H_
	#include "led.h"
#endif
#ifndef _SSC_H_
	#include "ssc.h"
#endif
#ifndef _USART_H_
	#include "usart.h"
#endif
#ifndef PMC_H
	#include "pmc.h"
#endif
#ifndef PIO_H
	#include "pio.h"
#endif
#ifndef _SMC_H_
	#include "smc.h"
#endif
#ifndef _DBGU_H_
	#include "dbgu.h"
#endif

/// Name of the board.
#define BOARD_NAME "SUL64"
/// Board definition.
#define at91sam3uek

//------------------------------------------------------------------------------
/// Frequency of the board main oscillator.
#define BOARD_MAINOSC           12000000
#define BOARD_MCK				96000000

//-----------------------------------------------------------------------------------------------
// ADC_AD0 pin definition.
#define PIN_ADC0_AD0 {1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
// ADC_AD1 pin definition.
#define PIN_ADC0_AD1 {1 << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
// ADC_AD2 pin definition.
#define PIN_ADC0_AD2 {1 << 3, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}
// ADC_AD3 pin definition.
#define PIN_ADC0_AD3 {1 << 4, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_DEFAULT}
// ADC_AD4 pin definition.
#define PIN_ADC0_AD4 {1 << 15, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
// ADC_AD5 pin definition.
#define PIN_ADC0_AD5 {1 << 16, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
// ADC_AD6 pin definition.
#define PIN_ADC0_AD6 {1 << 17, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}
// ADC_AD7 pin definition.
#define PIN_ADC0_AD7 {1 << 18, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_DEFAULT}

// Pins ADC
#define PINS_ADC PIN_ADC0_AD0, PIN_ADC0_AD1, PIN_ADC0_AD2, PIN_ADC0_AD3, PIN_ADC0_AD4, PIN_ADC0_AD5, PIN_ADC0_AD6, PIN_ADC0_AD7

//-----------------------------------------------------------------------------------------------
// TWI pins definition.
#define PIN_TWI_TWD0    	{0x1 << 9,  AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK0    	{0x1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWD1    	{0x1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_TWI_TWCK1    	{0x1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// LED pin definitions
#define PIN_LED_RED    		{0x1UL << 0, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_LED_GREEN  		{0x1UL << 1, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// SSC pin definitions
#define PIN_SSC_RD    		{0x1UL << 27, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_RF    		{0x1UL << 31, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_RK    		{0x1UL << 29, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_TD    		{0x1UL << 26, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_TF    		{0x1UL << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_SSC_TK    		{0x1UL << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// USART0
#define PIN_USART0_RXD    	{0x1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_TXD    	{0x1 << 18, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_CTS    	{0x1 << 8, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_RTS    	{0x1 << 7, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART0_SCK    	{0x1 << 17, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// USART1
#define PIN_USART1_RXD    	{0x1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_TXD    	{0x1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART1_CTS    	{0x1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_RTS    	{0x1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART1_SCK    	{0x1 << 24, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// USART2 pin definitions

#define PIN_USART2_RXD    	{0x1 << 23, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART2_TXD    	{0x1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_USART2_CTS    	{0x1 << 22, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART2_RTS    	{0x1 << 21, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART2_SCK    	{0x1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// USART3 pin definitions
#define PIN_USART3_RXD    	{0x1 << 13, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART3_TXD    	{0x1 << 12, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART3_CTS    	{0x1 << 10, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART3_RTS    	{0x1 << 11, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_USART3_SCK    	{0x1 << 19, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}

//-----------------------------------------------------------------------------------------------
// HSMC pin definitions

#define PIN_HSMC_ADDR0		{0x1 << 7, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_HSMC_ADDR1		{0x1 << 8, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_HSMC_ADDR2		{0x1 << 0, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR3		{0x1 << 1, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR4		{0x1 << 2, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR5		{0x1 << 3, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR6		{0x1 << 4, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR7		{0x1 << 5, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR8		{0x1 << 6, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_ADDR9		{0x1 << 7, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}

#define PIN_HSMC_DATA00		{0x1 << 9,  AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA01		{0x1 << 10, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA02		{0x1 << 11, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA03		{0x1 << 12, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA04		{0x1 << 13, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA05		{0x1 << 14, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA06		{0x1 << 15, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA07		{0x1 << 16, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA08		{0x1 << 25, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA09		{0x1 << 26, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA10		{0x1 << 27, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA11		{0x1 << 28, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA12		{0x1 << 29, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA13		{0x1 << 30, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA14		{0x1UL << 31, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_DATA15		{0x1 << 6,  AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}

#define PIN_HSMC_NRD		{0x1 << 19, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}		
#define PIN_HSMC_NWE		{0x1 << 23, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
#define PIN_HSMC_NCS2		{0x1 << 16, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}		

//-----------------------------------------------------------------------------------------------

#define USART_BUFFER_SIZE	0x80
#define ADC_BUFFER_SIZE		0x1000

//-----------------------------------------------------------------------------------------------

extern struct dma_token 	TOKEN;
extern unsigned char 		USART_BUFFER[USART_BUFFER_SIZE];
extern unsigned short 		ADC_BUFFER[ADC_BUFFER_SIZE];
extern unsigned int			USART_IRQ_COUNTER;

//-----------------------------------------------------------------------------------------------

/// Interrupt source
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  AT91SAM3U4 specific Interrupt Numbers *********************************************************/
 IROn_SUPC                = AT91C_ID_SUPC , // SUPPLY CONTROLLER
 IROn_RSTC                = AT91C_ID_RSTC , // RESET CONTROLLER
 IROn_RTC                 = AT91C_ID_RTC  , // REAL TIME CLOCK
 IROn_RTT                 = AT91C_ID_RTT  , // REAL TIME TIMER
 IROn_WDG                 = AT91C_ID_WDG  , // WATCHDOG TIMER
 IROn_PMC                 = AT91C_ID_PMC  , // PMC
 IROn_EFC0                = AT91C_ID_EFC0 , // EFC0
 IROn_EFC1                = AT91C_ID_EFC1 , // EFC1
 IROn_DBGU                = AT91C_ID_DBGU , // DBGU
 IROn_HSMC4               = AT91C_ID_HSMC4, // HSMC4
 IROn_PIOA                = AT91C_ID_PIOA , // Parallel IO Controller A
 IROn_PIOB                = AT91C_ID_PIOB , // Parallel IO Controller B
 IROn_PIOC                = AT91C_ID_PIOC , // Parallel IO Controller C
 IROn_US0                 = AT91C_ID_US0  , // USART 0
 IROn_US1                 = AT91C_ID_US1  , // USART 1
 IROn_US2                 = AT91C_ID_US2  , // USART 2
 IROn_US3                 = AT91C_ID_US3  , // USART 3
 IROn_MCI0                = AT91C_ID_MCI0 , // Multimedia Card Interface
 IROn_TWI0                = AT91C_ID_TWI0 , // TWI 0
 IROn_TWI1                = AT91C_ID_TWI1 , // TWI 1
 IROn_SPI0                = AT91C_ID_SPI0 , // Serial Peripheral Interface
 IROn_SSC0                = AT91C_ID_SSC0 , // Serial Synchronous Controller 0
 IROn_TC0                 = AT91C_ID_TC0  , // Timer Counter 0
 IROn_TC1                 = AT91C_ID_TC1  , // Timer Counter 1
 IROn_TC2                 = AT91C_ID_TC2  , // Timer Counter 2
 IROn_PWMC                = AT91C_ID_PWMC , // Pulse Width Modulation Controller
 IROn_ADCC0               = AT91C_ID_ADC12B, // ADC controller0
 IROn_ADCC1               = AT91C_ID_ADC, // ADC controller1
 IROn_HDMA                = AT91C_ID_HDMA , // HDMA
 IROn_UDPHS               = AT91C_ID_UDPHS // USB Device High Speed
} IRQn_Type;  

//-----------------------------------------------------------------------------

void init_board(void);
unsigned int *GetExceptionTable(void);
void memcpy(void *dst, void *src, unsigned size);
void memset(void *dst, unsigned char data, unsigned size);

//-----------------------------------------------------------------------------

#endif //#ifndef _BOARD_H_

