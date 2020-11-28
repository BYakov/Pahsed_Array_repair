//------------------------------------------------------------------------------

#ifndef _ADC12_H_
#define _ADC12_H_

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

#define ADC12_CHANNEL_0 0
#define ADC12_CHANNEL_1 1
#define ADC12_CHANNEL_2 2
#define ADC12_CHANNEL_3 3
#define ADC12_CHANNEL_4 4
#define ADC12_CHANNEL_5 5
#define ADC12_CHANNEL_6 6
#define ADC12_CHANNEL_7 7

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

extern void ADC12_Initialize (AT91S_ADC12B *pAdc,
                     unsigned char idAdc,
                     unsigned char trgEn,
                     unsigned char trgSel,
                     unsigned char sleepMode,
                     unsigned char resolution,        
                     unsigned int mckClock,
                     unsigned int adcClock,
                     unsigned int startupTime,
                     unsigned int sampleAndHoldTime);
extern unsigned short ADC12_GetConvertedData(AT91S_ADC12B *pAdc, int channel);
extern unsigned int ADC12_IsInterruptMasked(AT91S_ADC12B *pAdc, unsigned int flag);
extern unsigned int ADC12_IsStatusSet(AT91S_ADC12B *pAdc, unsigned int flag);
extern unsigned char ADC12_IsChannelInterruptStatusSet(unsigned int adc_sr, unsigned int channel);
extern void ADC12_CfgModeReg(AT91S_ADC12B *pAdc, unsigned int mode);
extern unsigned int ADC12_GetModeReg(AT91S_ADC12B *pAdc);
extern void ADC12_StartConversion(AT91S_ADC12B *pAdc);
extern void ADC12_SoftReset(AT91S_ADC12B *pAdc);
extern void ADC12_EnableChannel(AT91S_ADC12B *pAdc, unsigned int channel);
extern void ADC12_DisableChannel(AT91S_ADC12B *pAdc, unsigned int channel);
extern void ADC12_EnableIt(AT91S_ADC12B *pAdc, unsigned int mode);
void ADC12_DisableIt(AT91S_ADC12B *pAdc, unsigned int mode);    
extern void ADC12_EnableDataReadyIt(AT91S_ADC12B *pAdc);
extern unsigned int ADC12_GetStatus(AT91S_ADC12B *pAdc);
extern unsigned int ADC12_GetChannelStatus(AT91S_ADC12B *pAdc);
extern unsigned int ADC12_GetInterruptMaskStatus(AT91S_ADC12B *pAdc);
extern unsigned int ADC12_GetLastConvertedData(AT91S_ADC12B *pAdc);
extern void ADC12_CfgAnalogCtrlReg(AT91S_ADC12B *pAdc, unsigned int mode);     
extern void ADC12_CfgExtModeReg(AT91S_ADC12B *pAdc, unsigned int extmode);
extern unsigned int ADC12_GetAnalogCtrlReg(AT91S_ADC12B *pAdc);

//-----------------------------------------------------------------------------


#endif //#ifndef _ADC12_H_
