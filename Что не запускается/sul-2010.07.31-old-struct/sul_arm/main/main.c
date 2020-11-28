
#if defined(cortexm3)
	#include <stdio.h>
#endif

#ifndef _BOARD_H_
	#include <board.h>
#endif

#ifndef _SYSTICK_H_
	#include <systick.h>
#endif

#ifndef _ADC12_H_
	#include <adc12.h>
#endif

#ifndef _DISPATCH_H_
	#include "dispatch.h"
#endif

#ifndef _USB_H_
	#include "usb.h"
#endif

#ifndef _TC_H_
	#include "tc.h"
#endif

//------------------------------------------------------------------------------

struct dma_token 	TOKEN  = {0};
struct adc_param 	param  = {0};
struct adc_result 	result = {0};
struct adc_buffer 	adata  = {0};

unsigned char 		USART_BUFFER[USART_BUFFER_SIZE] = {0};
unsigned char 		conversionDone;
unsigned short 		ADC_BUFFER[ADC_BUFFER_SIZE] = {0};
unsigned short 		BufferIndex;

//---------------------------------------------------------------------------------------

#define ADC_CHANNEL_BNC  	ADC12_CHANNEL_3
#define ADC_CHANNEL_X  		ADC12_CHANNEL_2
#define ADC_CHANNEL_Y  		ADC12_CHANNEL_6
#define ADC_CHANNEL_Z  		ADC12_CHANNEL_7

unsigned char channels[] = {ADC_CHANNEL_BNC, ADC_CHANNEL_X, ADC_CHANNEL_Y, ADC_CHANNEL_Z};

#define BOARD_ADC_FREQ 1000000
#define ADC_VREF       3300  // 3.3 * 1000

//---------------------------------------------------------------------------------------

unsigned short ConvHex2mV( unsigned short valueToConvert );
void ADC12_Start(void);
unsigned short ADC12_Samples(void);

//---------------------------------------------------------------------------------------
/// Convert a digital value in milivolt
/// \param valueToconvert Value to convert in milivolt
//---------------------------------------------------------------------------------------


/////////////////////////////////////////

//------------------------------------------------------------------------------
/// Configure Timer Counter 0 to generate an interrupt every 250ms.
//------------------------------------------------------------------------------
void ConfigureTc(void)
{
    unsigned int div;
    unsigned int tcclks;

    // Enable peripheral clock
    AT91C_BASE_PMC->PMC_PCER = 1 << AT91C_ID_TC0;

    // Configure TC for a 1MHz frequency and trigger on RC compare
    TC_FindMckDivisor(400000, BOARD_MCK, &div, &tcclks);
    TC_Configure(AT91C_BASE_TC0, tcclks | AT91C_TC_CPCTRG);
    AT91C_BASE_TC0->TC_RC = (BOARD_MCK / div) / 400000; // timerFreq / desiredFreq

    // Configure and enable interrupt on RC compare
    IRQ_ConfigureIT(AT91C_ID_TC0, 0, TC0_IrqHandler);	    
    AT91C_BASE_TC0->TC_IER = AT91C_TC_CPCS;
    IRQ_EnableIT(AT91C_ID_TC0);

    TC_Start(AT91C_BASE_TC0);
}
/////////////////////////////////////////

int main(void)
{
	int i=0; 

	memset(&USART_BUFFER[0],0,sizeof(USART_BUFFER));
	memset(&TOKEN,0,sizeof(USART_BUFFER));

	init_board();
							 
	LED_all_toggle();

	//ConfigureTc();

	//while(1);

	//TOKEN.code = start_adc;
	//TOKEN.code = get_adc_result;

	//dispatch dma_token message
	while(1) {

		wait_usart_irq_flag();

		//procrssing token message here...
		switch(TOKEN.code) {

			case set_adc_param : {
				memcpy(&param, &USART_BUFFER[0], sizeof(struct adc_param));
				LED_all_toggle();  
			} break;

			case start_adc : {
				for(i=0; i<param.buffer_size; i++) {
					ADC12_Start();
				}
				LED_all_toggle();
			} break;

			case get_adc_result : {
				result.mean = 12345678;
				result.rms = 87654321;
				USART_WriteBuffer( AT91C_BASE_US1, &result.mean, sizeof(struct adc_result));
				LED_all_toggle();
			} break;

			case get_adc_buffer : {
				adata.buffer_size = TOKEN.data;
				USART_WriteBuffer( AT91C_BASE_US1, &ADC_BUFFER[0], adata.buffer_size);
				LED_all_toggle();
			} break;

			case usart_debug_msg: {
				LED_all_toggle();
			} break;
		}

		//=======================
		
		reset_usart_irq_flag();
	};
}

//-----------------------------------------------------------------------------

void ConfigureUsart(unsigned int speed)
{
    unsigned int mode =   AT91C_US_CLKS_CLOCK
                        | AT91C_US_CHRL_8_BITS
                        | AT91C_US_PAR_NONE
                        | AT91C_US_NBSTOP_1_BIT//;//AT91C_US_NBSTOP_2_BIT //AT91C_US_NBSTOP_15_BIT
                        | AT91C_US_USMODE_RS485;

    // Configure the USART in the desired mode and speed bauds
	USART_Configure(AT91C_BASE_US1, mode, speed, 96000000);

    // Configure the RXBUFF interrupt
	IRQ_ConfigureIT(AT91C_ID_US1, 0, USART1_IrqTokenHandler);
    IRQ_EnableIT(AT91C_ID_US1);

    // Enable receiver & transmitter
    USART_SetTransmitterEnabled(AT91C_BASE_US1, 1);
    USART_SetReceiverEnabled(AT91C_BASE_US1, 1);
}

//-----------------------------------------------------------------------------

const Pin pins[] = {

	// USART1 pin definitions
	PIN_USART1_RXD,
	PIN_USART1_TXD,
	PIN_USART1_CTS,
	PIN_USART1_RTS,
	PIN_USART1_SCK,

	// LED pin definitions
	PIN_LED_RED,
	PIN_LED_GREEN,

	// ADC pins
	PIN_ADC0_AD0,
	PIN_ADC0_AD1,
	PIN_ADC0_AD2,
	PIN_ADC0_AD3,
	PIN_ADC0_AD4,
	PIN_ADC0_AD5,
	PIN_ADC0_AD6,
	PIN_ADC0_AD7,
};

//------------------------------------------------------------------------------
/// Interrupt handler for the ADC. Signals that the conversion is finished by
/// setting a flag variable.
//------------------------------------------------------------------------------

void ADC12_Start(void)
{
		unsigned short advalue = 0;

	    ADC12_EnableIt(AT91C_BASE_ADC12B, (1<<ADC_CHANNEL_BNC));

	    ADC12_StartConversion(AT91C_BASE_ADC12B);
	
	    while( conversionDone != (1<<ADC_CHANNEL_BNC));
	
	    advalue = ADC12_GetConvertedData(AT91C_BASE_ADC12B, ADC_CHANNEL_BNC);

		//advalue = ConvHex2mV( advalue );

		ADC_BUFFER[BufferIndex] = advalue;

		BufferIndex++;

		if(BufferIndex >= ADC_BUFFER_SIZE) {
			BufferIndex = 0;			
		}
}

//------------------------------------------------------------------------------

unsigned short ADC12_Samples(void)
{
	return 0;
}

//------------------------------------------------------------------------------

void ADCC0_IrqHandler(void)
{
    unsigned int status = 0;

    status = ADC12_GetStatus(AT91C_BASE_ADC12B);

	if (ADC12_IsChannelInterruptStatusSet(status, ADC_CHANNEL_BNC)) {
	
		ADC12_DisableIt(AT91C_BASE_ADC12B, (1 << ADC_CHANNEL_BNC));
		conversionDone |= (1 << ADC_CHANNEL_BNC);
	}
}

//------------------------------------------------------------------------------

void init_board(void)
{
	PIO_Configure(pins, PIO_LISTSIZE(pins));
 
    PMC_EnablePeripheral(AT91C_ID_US1);
	ConfigureUsart(115200); //ok
	
	PMC_EnablePeripheral(AT91C_ID_PIOB);
	LED_Configure();

	USART_ReadBuffer(AT91C_BASE_US1, &TOKEN, sizeof(struct dma_token));
	AT91C_BASE_US1->US_IER = AT91C_US_RXBUFF;

	//==========
    ADC12_Initialize( AT91C_BASE_ADC12B,
                    AT91C_ID_ADC12B,
                    AT91C_ADC_TRGEN_DIS,
                    0,
                    AT91C_ADC_SLEEP_NORMAL_MODE,
                    AT91C_ADC_LOWRES_12_BIT,
                    96000000,
                    BOARD_ADC_FREQ,
                    10,
                    1200);

    ADC12_EnableChannel(AT91C_BASE_ADC12B, ADC_CHANNEL_BNC);

    IRQ_ConfigureIT(AT91C_ID_ADC12B, 0, ADCC0_IrqHandler);
    IRQ_EnableIT(AT91C_ID_ADC12B);
	//==========

	// 1-ms system tick
	//SysTick_Configure(3, 96000, SysTick_Handler);
}

//-----------------------------------------------------------------------------

void ADC12_Tune(unsigned char gain, unsigned char cur, unsigned int diff, unsigned int offset)
{
		//=======================
		// set gain
		//gain = 0;
		//gain = 0x1;
		//gain = 0x2;
		//gain = 0x3;				
		//gain |= (((unsigned int)ADC12_GetAnalogCtrlReg(AT91C_BASE_ADC12B)) & 0x300c0);
		//Change GAIN field of ADC_ACR of ADC 12 bit
		//ADC12_CfgAnalogCtrlReg(AT91C_BASE_ADC12B, gain);
	
		//set bias current control
		//cur = 0;
		//cur = 0x40;
		//cur = 0x80;
		//cur = 0xC0;
		//Change GAIN field of ADC_ACR of ADC 12 bit
		//cur |= (((unsigned int)ADC12_GetAnalogCtrlReg(AT91C_BASE_ADC12B)) & 0x30003);
		//ADC12_CfgAnalogCtrlReg(AT91C_BASE_ADC12B, cur);
	
		//set Differential Mode
		//note: in SAM3UE-EK REV 1, only single end is connected. No available input on EK board for Fully Differential Mode 
		//diff = 0;
		//diff = 0x10000;
		//Change GAIN field of ADC_ACR of ADC 12 bit
		//diff |= (((unsigned int)ADC12_GetAnalogCtrlReg(AT91C_BASE_ADC12B)) & 0x200c3);
		//ADC12_CfgAnalogCtrlReg(AT91C_BASE_ADC12B, diff);
	
		//set offset
		//offset = 0;
		//offset = 0x20000;
		//Change GAIN field of ADC_ACR of ADC 12 bit
		//offset |= (((unsigned int)ADC12_GetAnalogCtrlReg(AT91C_BASE_ADC12B)) & 0x100c3);
		//ADC12_CfgAnalogCtrlReg(AT91C_BASE_ADC12B, offset);
}

//------------------------------------------------------------------------------

void memcpy(void *dst, void *src, unsigned size)
{
	int i=0;
	for(i=0;i<size;i++) {
		*((unsigned char*)dst+i) = *((unsigned char*)src+i);
	}
}

//------------------------------------------------------------------------------

void memset(void *dst, unsigned char data, unsigned size)
{
	int i=0;
	for(i=0;i<size;i++) {
		*((unsigned char*)dst+i) = data;
	}
}

//------------------------------------------------------------------------------

unsigned short ConvHex2mV( unsigned short valueToConvert )
{
    return( (ADC_VREF * valueToConvert)/0xFFF);
}

//---------------------------------------------------------------------------------------

