
#ifndef _SUL_AVR_H_
#define _SUL_AVR_H_

#ifndef _SUL_BASE_H_
#include "..\base_class\sul_base.h"
#endif
/*
//! ������ ������ ������������� ���
struct vector {

u8	cmd;				//!< ��� ������� ���������� ���
u8 count : 8;			//!< ������� ������ ������
u8  : 7;				//!< ����������������
u8 flag : 1;			//!< ���� ����� (������ 1)

u8  : 3;				//!< ����������������
u8 mode : 3;			//!< ���� ������ ���
u8	: 2;				//!< ����������������
u8  : 8;				//!< ����������������	
u16 dX;					//!< ���������� ���������� ���� �� �
u16 dY;					//!< ���������� ���������� ���� �� Y
u8  : 8;				//!< ����������������
u8 wide : 1;			//!< ��� ���� (�������)
u8  : 3;				//!< ����������������
u8 narrow : 1;			//!< ��� ���� (�����)
u8 zone : 3;			//!< ����� ������� ����
};
*/
#pragma pack(1)
//! ������ ������ ������������� ���
struct ctrl_vector {

	u8	cmd;				//!< ��� ������� ���������� ���
	u16	count;				//!< ��� ������� ���������� ���
	u16 mode;				//!< ���� ������ ���
	u16 dX;					//!< ���������� ���������� ���� �� �
	u16 dY;					//!< ���������� ���������� ���� �� Y
	u16 zone;				//!< ����� ������� ����
};

//! ���� ������ ��� ���������� ������� ����� � ��� ���.
enum sul_command {

	CMD_RECIEVE_VECTOR		= 0x01, //!< ������� ����������� ������
	CMD_TEST_EXCHANGE		= 0x07, //!< �������� ������ � ������� �����
	CMD_FLASH_CLEAR			= 0x10, //!< �������� FLASH � �����
	CMD_BLOCK_LOADED		= 0x11, //!< ������� ����������� ������
	CMD_INIT_MODULES		= 0x12, //!< ������������������� ������ ����
	CMD_CTRL_FLASH			= 0x13, //!< �������� ����������� ����� ������ �� FLASH
	CMD_CTRL_CALC			= 0x14, //!< ����������������� ����������� ������� ����
	CMD_CTRL_CHAN			= 0x15, //!< ����������������� ������
	CMD_CTRL_POWER_OFF		= 0x16, //!< ��������� ������� ������� ����
	CMD_CTRL_POWER_ON		= 0x17, //!< �������� ������� ������� ����
	CMD_CTRL_SUPPLY			= 0x18, //!< ����������������� ���������� ������� ������� ����
	CMD_RETURN_DATA16		= 0x20, //!< ������� 16 ���� ������
	CMD_RETURN_DATA128_0            = 0x21, //!< ������� 128 ���� ������ (������ �����)
	CMD_RETURN_DATA128_1	        = 0x22, //!< ������� 128 ���� ������ (������ �����)
	CMD_RETURN_DATA32		= 0x23, //!< ������� 32 ����� ������
	CMD_PREPARE_INFO		= 0x24, //!< ����������� ���������� � ��������� �����

	CMD_SET_RAM_DATA		= 0x25, //!< ������� ������ F0 � ������ RAM
	CMD_GET_RAM_DATA		= 0x26, //!< �������� ������ F0 �� ������ RAM
	CMD_SET_CHANNEL		        = 0x27, //!< �������� ���������� F0 ��� ������
	CMD_GET_CHANNEL		        = 0x28, //!< �������� ���������� F0 ��� ������
	CMD_GET_RAM_CRC		        = 0x29, //!< �������� CRC RAM

	CMD_CLEAR_EEPROM_DATA	        = 0x30, //!< �������� ������ EEPROM
	CMD_RESERVED			= 0x31, //!< ����������������� ��� �������
	CMD_SET_DEVICE_INFO		= 0x32, //!< ������� ���������� � ��������� �����
	CMD_GET_DEVICE_INFO		= 0x33, //!< �������� ���������� � ��������� �����

	CMD_INIT_MODULES_RAM            = 0x40, //!< ������������������� ������ ������� �� RAM

	CMD_M0LKB_READY			= 0x55, //!< ������ ���������� � ���������� �����
	CMD_M0LKB_REQUEST		= 0xAA, //!< ������ ������� �������
	CMD_EMPTY_COMMAND		= 0x0,  //!< ������ ������� (��� �������������)

};

//! ����������� ��������� ������������� ���
/*!
��������� ������������ ��� ��� �����������
������������� �������� ���������� �� ��������� �� ������� HOST.
*/
struct sul_message {

	u8				cmd;		//!< ��� ������� ���������� ���
	u8				data[128];	//!< ������ � ������� ��� ������� �������

	//! ����������� �� ���������
	sul_message()
	{
		cmd = CMD_EMPTY_COMMAND;
	}
};

#pragma pack()
///////////////////////////////////////////////////////////////////////////////

//!  ����� ��������� ��������� � ��� ���.
/*!
�������� �� �������������� � ��� ���. ��������� ��� ������������ �������,
������������ � ������ sul_base.
*/
class sul_avr : public sul_base
{

private:
	//! ������� ������� ������
	u8 count;

	//! ����������� �� ���������
	sul_avr();

	//! �������� ���� ������ FLASH �� ����������������� ������������ � ���
	/*!
	\param zone - ����� ���� (������� � ����) �� ������� ����� ������� ����.
	\param block - ����� ����� (������� � ����) ������������ ������ ����.
	*/
	int send_flash_block(int zone, int block);

	//! �������� ���� ������ RAM �� ����������������� ������������ � ���
	/*!
	\param zone - ����� ���� (������� � ����) �� ������� ����� ������� ����.
	\param block - ����� ����� (������� � ����) ������������ ������ ����.
	*/
	int send_ram_block(int zone, int block);

	//! �������� ��������� ����� ��� ��� ������ ������
	/*!
	\param cmd - ��� �������.
	\param timeout - ������� ��������
	*/
	int send_cmd(sul_command cmd, int timeout);

	//! ��������� ������������ ��������� ��� ����� ������
	/*!
	\param size - ���������� ���������� ���� (������� ���������).
	\param timeout - ������� �������� (������� �� ���������� �������).
	*/
	int checkback(int size, int timeout);

	//! ��������� ������������ ����������� ��� �������
	/*!
	\param cmd ��� ���������� ����� �������.
	\param timeout - ������� �������� (������� �� ���������� �������).
	*/
	int checkback(sul_command cmd, int timeout);

public:
	//! ����������� ������ ��� ���
	/*!
	\param hw - ���������� ��� ������ � ��� ���
	\param sul_config - ��� ����� ������������ ���
	\param ram_config - ��� ����� ������������ RAM
	*/
	sul_avr( device *hw,
		const char *sul_config,
		const char *ram_config );

	//! ����������
	virtual ~sul_avr();
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	int sul_init(int devn=0);
	int sul_reset(int devn=0);
	int sul_channels(int devn=0);
	int sul_test(int devn=0);
	int sul_test(int devn, unsigned char *buffer, int size);
	int sul_beam_position(u16 x=0, u16 y=0, u8 zone=0, ray_type type=RAY_NARROW);
	struct sul_state sul_state(int devn=0);
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
        virtual int sul_flash_load(const char *file = NULL, int devn = 0);
	virtual int sul_flash_save(const char *file = NULL);
	virtual int sul_flash_erase(int devn = 0);
	virtual u16 sul_flash_crc(int devn = 0);
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
        virtual int sul_ram_load(const char *file = NULL, int devn = 0);
	virtual int sul_ram_save(const char *file = NULL);
	virtual int sul_ram_erase(int devn = 0);
	virtual u16 sul_ram_crc(int devn = 0);
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
};

/////////////////////////////////////////////////////////////////////


#endif //_SUL_AVR_H_
