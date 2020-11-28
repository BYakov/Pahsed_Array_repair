#ifndef _SUL_DATA_TYPES_H_
#define _SUL_DATA_TYPES_H_

//------------------------------------------------------------------------------

#define MAX_DEVICE_NUMBER  8

#define SUL_NUM_PAGE	   11
#define SUL_PAGE_SIZE 	   0x4000
#define SUL_BLOCK_NUM 	   0x10
#define SUL_BLOCK_SIZE 	   0x80

#define SUL_NUM_ZONE	   11
#define SUL_NUM_LOCAL 	   13
#define SUL_NUM_BOARD 	   8
#define SUL_NUM_MODULE 	   8


#define ENABLE_DEVICE 	   1

#define DISABLE_DEVICE 	   0


//------------------------------------------------------------------------------

#define LOGMSG(fd, fmt, args) fprintf((fd), (fmt), ##args)
//------------------------------------------------------------------------------

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

//------------------------------------------------------------------------------

typedef struct _sul_msg_head {

	u16 hdr[31];

} sul_msg_head;

//------------------------------------------------------------------------------

typedef struct _msg_queue {

	u16 val[5];

} msg_queue;

//------------------------------------------------------------------------------

typedef struct _sul_data_block {

	int zn, lkn, bn;
	u16 data[40];

} sul_data_block;

//------------------------------------------------------------------------------

typedef struct _device_table {

	u8 enable;

} device_table;

//------------------------------------------------------------------------------

#endif //_SUL_DATA_TYPES_H_
