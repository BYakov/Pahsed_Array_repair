
#ifndef _TC_H_
#define _TC_H_

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void TC_Configure(AT91S_TC *pTc, unsigned int mode);

extern void TC_Start(AT91S_TC *pTc);

extern void TC_Stop(AT91S_TC *pTc);

extern unsigned char TC_FindMckDivisor(
    unsigned int freq,
    unsigned int mck,
    unsigned int *div,
    unsigned int *tcclks);

#endif //#ifndef _TC_H_

