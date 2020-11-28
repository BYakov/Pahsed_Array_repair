
#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _EXCEPTIONS_H_
	#include "exceptions.h"
#endif

//------------------------------------------------------------------------------
// Default irq handler
//------------------------------------------------------------------------------
void IrqHandlerNotUsed(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Provide weak aliases for each Exception handler to the IrqHandlerNotUsed. 
// As they are weak aliases, any function with the same name will override 
// this definition.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// System interrupt
//------------------------------------------------------------------------------
WEAK void NMI_Handler(void)
{   
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void HardFault_Handler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void MemManage_Handler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void BusFault_Handler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void UsageFault_Handler(void)
{
  	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void SVC_Handler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void DebugMon_Handler(void)
{
  	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
WEAK void PendSV_Handler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// for Cortex M3
//------------------------------------------------------------------------------
//unsigned int 		jiffies = 0;
//------------------------------------------------------------------------------
WEAK void SysTick_Handler(void)
{
//	unsigned char val = 0;

	//++jiffies;

	//if(!(jiffies%100)) {
/*
		SMC_Write(2, 0x78, 0);
		SMC_Write(2, 0x70, 0x41);
		SMC_Write(2, 0x0,  0x20);
		SMC_Write(2, 0x4,  0x1);
		SMC_Write(2, 0x8,  0x2);
		SMC_Write(2, 0x74, 0x1);
*/
/*
		SMC_Write(2, 0x48, 0);
		SMC_Write(2, 0x40, 0x41);
		SMC_Write(2, 0x0,  0x20);
		SMC_Write(2, 0x4,  0x1);
		SMC_Write(2, 0x8,  0x2);
		SMC_Write(2, 0x44, 0x1);
*/
/*		
		SMC_Write(2, 0x42, 0);
		SMC_Write(2, 0x40, 0x41);
		SMC_Write(2, 0x0,  0x20);
		SMC_Write(2, 0x1,  0x1);
		SMC_Write(2, 0x2,  0x2);
		SMC_Write(2, 0x41, 0x1);
*/
	//SMC_Write(usart_tx_base, 0x20);
	//SMC_Write(usart_tx_base+1, 3);
	//SMC_Write(usart_tx_base+2, 1);
	
		//SMC_Write(usart_command, 0x1);
		//val = SMC_Read();
		//if(val == )
		//LED_all_toggle();
	//}
}

//------------------------------------------------------------------------------
// External interrupt
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// for SAM7/9
//------------------------------------------------------------------------------
void SYS_IrqHandler( void )
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// SUPPLY CONTROLLER
//------------------------------------------------------------------------------
WEAK void SUPC_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// RESET CONTROLLER
//------------------------------------------------------------------------------
WEAK void RSTC_IrqHandler(void)
{
  	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// REAL TIME CLOCK
//------------------------------------------------------------------------------
WEAK void RTC_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// REAL TIME TIMER
//------------------------------------------------------------------------------
WEAK void RTT_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// WATCHDOG TIMER
//------------------------------------------------------------------------------
WEAK void WDT_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// PMC
//------------------------------------------------------------------------------
WEAK void PMC_IrqHandler(void)
{
  	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// EFC0
//------------------------------------------------------------------------------
WEAK void EFC0_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// EFC1
//------------------------------------------------------------------------------
WEAK void EFC1_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}
//------------------------------------------------------------------------------
// DBGU
//------------------------------------------------------------------------------
WEAK void DBGU_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// HSMC4
//------------------------------------------------------------------------------
WEAK void HSMC4_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Parallel IO Controller A
//------------------------------------------------------------------------------
WEAK void PIOA_IrqHandler(void)
{
  	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Parallel IO Controller B
//------------------------------------------------------------------------------
WEAK void PIOB_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Parallel IO Controller C
//------------------------------------------------------------------------------
WEAK void PIOC_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// USART 0
//------------------------------------------------------------------------------
WEAK void USART0_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------

volatile unsigned char 	usart_flag = 0;

//------------------------------------------------------------------------------

void wait_usart_irq_flag(void)
{
	while(!usart_flag);
}

//------------------------------------------------------------------------------

void set_usart_irq_flag(void)
{
	usart_flag = 1;
}

//------------------------------------------------------------------------------

void reset_usart_irq_flag(void)
{
	usart_flag = 0;
}

//------------------------------------------------------------------------------
// USART 1
//------------------------------------------------------------------------------

WEAK void USART1_IrqTokenHandler(void)
{
    if (AT91C_BASE_US1->US_CSR & AT91C_US_RXBUFF) {

		// Disable DMA transaction
		USART_ReadBuffer(AT91C_BASE_US1, 0, 0);

		if(check_dma_token(&TOKEN) < 0) {
				USART_ClearDataBuffer(AT91C_BASE_US1, 10);
				AT91C_BASE_US1->US_IER = AT91C_US_RXBUFF;
				USART_ReadBuffer(AT91C_BASE_US1, &TOKEN, sizeof(struct dma_token));
				LED_toggle(LED_RED);
				return;
		}

		if((TOKEN.size == 0) && (TOKEN.dcrc == 0)) {
			USART_ClearDataBuffer(AT91C_BASE_US1, 10);
			AT91C_BASE_US1->US_IER = AT91C_US_RXBUFF;
			USART_ReadBuffer(AT91C_BASE_US1, &TOKEN, sizeof(struct dma_token));
			// Set USART data flag
			set_usart_irq_flag();
			return;
		}

		// Install new interrupt handler
		IRQ_ConfigureIT(AT91C_ID_US1, 0, USART1_IrqDataHandler);
		IRQ_EnableIT(AT91C_ID_US1);

		// Enable and init next DMA data transaction
		USART_ReadBuffer(AT91C_BASE_US1, &USART_BUFFER[0], TOKEN.size);

		// Enable interrupt set and service current command
		AT91C_BASE_US1->US_IER = AT91C_US_RXBUFF;
    }
}

//------------------------------------------------------------------------------

WEAK void USART1_IrqDataHandler(void)
{
    if (AT91C_BASE_US1->US_CSR & AT91C_US_RXBUFF) {

		// Disable DMA transaction
		USART_ReadBuffer(AT91C_BASE_US1, 0, 0);

		// Install new interrupt handler
		IRQ_ConfigureIT(AT91C_ID_US1, 0, USART1_IrqTokenHandler);
		IRQ_EnableIT(AT91C_ID_US1);

		// Enable and init next DMA token transaction
		USART_ReadBuffer(AT91C_BASE_US1, &TOKEN, sizeof(struct dma_token));

		//Enable interrupt set and service current command		
		AT91C_BASE_US1->US_IER = AT91C_US_RXBUFF;

		if(check_dma_transactions(&TOKEN, &USART_BUFFER[0], TOKEN.size) < 0) {
			USART_ClearDataBuffer(AT91C_BASE_US1, 10);
			return;
		}

		// Set USART data flag
		set_usart_irq_flag();
    }
}

//------------------------------------------------------------------------------
// USART 2
//------------------------------------------------------------------------------

WEAK void USART2_IrqHandler(void)
{
   	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// USART 3
//------------------------------------------------------------------------------

WEAK void USART3_IrqHandler(void)
{
    if (AT91C_BASE_US3->US_CSR & AT91C_US_TXBUFE) {
		AT91C_BASE_US3->US_PTCR = AT91C_PDC_TXTDIS;
    }
}

//------------------------------------------------------------------------------
// Multimedia Card Interface
//------------------------------------------------------------------------------
WEAK void MCI0_IrqHandler(void)
{
    LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// TWI 0
//------------------------------------------------------------------------------
WEAK void TWI0_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// TWI 1
//------------------------------------------------------------------------------
WEAK void TWI1_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Serial Peripheral Interface 0
//------------------------------------------------------------------------------
WEAK void SPI0_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Serial Synchronous Controller 0
//------------------------------------------------------------------------------
WEAK void SSC0_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Timer Counter 0
//------------------------------------------------------------------------------
WEAK void TC0_IrqHandler(void)
{
    volatile unsigned int dummy;

    // Clear status bit to acknowledge interrupt
    dummy = AT91C_BASE_TC0->TC_SR;

    // Toggle LED state
    LED_all_toggle();
}

//------------------------------------------------------------------------------
// Timer Counter 1
//------------------------------------------------------------------------------
WEAK void TC1_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// Timer Counter 2
//------------------------------------------------------------------------------
WEAK void TC2_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// PWM Controller
//------------------------------------------------------------------------------
WEAK void PWM_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// ADC controller0
//------------------------------------------------------------------------------
/*
WEAK void ADCC0_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}
*/
//------------------------------------------------------------------------------
// ADC controller1
//------------------------------------------------------------------------------
WEAK void ADCC1_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// HDMA
//------------------------------------------------------------------------------
WEAK void HDMA_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}

//------------------------------------------------------------------------------
// USB Device High Speed UDP_HS
//------------------------------------------------------------------------------
WEAK void UDPD_IrqHandler(void)
{
	LED_toggle(LED_RED);
    while(1);
}
