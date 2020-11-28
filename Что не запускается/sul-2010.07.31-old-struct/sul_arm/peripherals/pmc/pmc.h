
#ifndef _PMC_H_
#define _PMC_H_

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

#if defined(at91sam7l64) || defined(at91sam7l128)
extern void PMC_SetFastWakeUpInputs(unsigned int inputs);
extern void PMC_DisableMainOscillator(void);
extern
#ifdef __ICCARM__
__ramfunc
#endif //__ICCARM__
void PMC_DisableMainOscillatorForWaitMode(void);
#endif // at91sam7l64 at91sam7l128

extern void PMC_DisableProcessorClock(void);
extern void PMC_EnablePeripheral(unsigned int id);
extern void PMC_DisablePeripheral(unsigned int id);
extern void PMC_CPUInIdleMode(void);


extern void PMC_EnableAllPeripherals(void);

extern void PMC_DisableAllPeripherals(void);

extern unsigned int PMC_IsAllPeriphEnabled(void);

extern unsigned int PMC_IsPeriphEnabled(unsigned int id);

#endif //_PMC_H_

