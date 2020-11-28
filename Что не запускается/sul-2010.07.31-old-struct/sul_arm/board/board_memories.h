
#ifndef _BOARD_MEMORIES_H_
#define _BOARD_MEMORIES_H_

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

extern void BOARD_ConfigureSdram(unsigned char busWidth);

extern void BOARD_ConfigureNandFlash(unsigned char busWidth);

extern void BOARD_ConfigurePsram(void);

#endif //#ifndef _BOARD_MEMORIES_H_

