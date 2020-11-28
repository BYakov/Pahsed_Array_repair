
#ifndef _BOARD_LOWLEVEL_H_
#define _BOARD_LOWLEVEL_H_

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
extern void LowLevelInit(void);
extern void SetDefaultMaster(unsigned char enable);
extern void SetFlashWaitState(unsigned char ws);

#endif // BOARD_LOWLEVEL_H

