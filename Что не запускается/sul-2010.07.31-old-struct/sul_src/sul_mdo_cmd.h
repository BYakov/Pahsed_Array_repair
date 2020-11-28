
#ifndef _SUL_MDO_CMD_H_
#define _SUL_MDO_CMD_H_

#pragma pack(1)

//! ��������� ��������� ������������� ��� ������������ ������
enum header_signature {
        host_signature      = 0xAA, //!< ��� ��������� (������ ��������� HOST -> TARGET)
        target_signature    = 0xBB, //!< ��� ��������� (������ ��������� HOST <- TARGET)
//	main_signature      = 0xCC, //!< ��� ��������� (������ ��������� HOST -> TARGET)
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//! ��������� ������ ������ ��������� ������
struct main_header {
        unsigned char sign;     //!< ��������� ���������
        unsigned char addr;     //!< ����� �������� ��� ��������� ������ � ��� �������
};

//! ������ ������ ��������� ������
struct main_data {
        unsigned short x;     //!< ���������� �
        unsigned short y;     //!< ���������� Y
        unsigned char cmd;    //!< ��������� ����� (���� 0..3 - ����� ����, 4..7 - ������)
};

//! ��������� ������ ������ ��������� ������
struct main_tail {
        unsigned char mcrc;     //!< ����������� ����� ������ ��������� ������
};

//! ����� ��������� ������
struct main_packet {
        struct main_header      mhdr;   //!< ��������� ������ ��������� ������
        struct main_data        mdata;  //!< ������ ������ ��������� ������
        struct main_tail        mtail;  //!< ��������� ������ ��������� ������
};

//!���� ������� ��� ��������� ������
enum sul_mdo_zones {
        zone0 = 0x0,
        zone1,
        zone2,
        zone3,
        zone4,
        zone5,
        zone6,
        zone7,
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//!��������� ������ (HOST -> TARGET) ������ ����������� ������
struct host_dbg_header {
        unsigned char sign;     //!< ��������� ��������� (host_signature)
        signed   char addr;     //!< ����� �������� ��� ��������� ������
        unsigned char code;     //!< ��� �������
        unsigned char size;     //!< ������ ������ ������
        unsigned char dcrc;     //!< ����������� ����� ������ ������
        unsigned char bnum;     //!< ����� ����� ������ ������������� ��� ��������
        unsigned char txrx;     //!< ���� ������/�������� (0: H->T, 1: H<-T)
        unsigned char hcrc;     //!< ����������� ����� ���������
};

//! �������� ����� host_dbg_header::txrx
enum trans_type {
        to_empty = 0,               //!< �������������� ��������
        to_target = 1,              //!< H -> T + DATA
        to_host = 2,                //!< H <- T + DATA
        to_target_cmd = 3,          //!< H <- T + NO DATA
};

//!��������� ������ (HOST <- TARGET) ������ ����������� ������
struct target_dbg_header {
        unsigned char sign;     //!< ��������� ��������� (target_signature)
        signed   char addr;     //!< ����� �������� ��� ��������� ������
        unsigned char code;     //!< ��� �������
        unsigned char crc;      //!< ����������� ����� ���������/������ ������
};

//! �������������� ����� (�������� ��� ����������)
struct packet {
        unsigned char *paddr;       //!< ����� ��������������� ������
        unsigned long  length;      //!< ����� ������ � ������
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//! ���� ������ ����������� ������
enum sul_mdo_cmd {

	//������� ��������� ������
	host_eeprom_data = 0x01,      //!< H->T EEPROM: bnum = N, size = 128
	host_ram_data,                //!< H->T RAM: bnum = N, size = 128
	host_scale,		      //!< H->T size = 2 ���������� ���������� ����������� ��������
	target_scale_return,          //!< H<-T size = 2 ������� ����������� ��������

        //������� ������������� ������
        target_eeprom_to_plm,         //!< ���������� ������ EEPROM -> PLM
        target_ram_to_plm,            //!< ���������� ������ RAM -> PLM
        target_eeprom_clear,          //!< �������� EEPROM: bnum = N, dummy size = 128
        target_ram_clear,             //!< �������� RAM: bnum = N, dummy size = 128

        //������� �������� ������ �������������
        target_eeprom_data,           //!< H <- T EEPROM: bnum = N, size = 128
        target_ram_data,              //!< H <- T RAM: bnum = N, size = 128
        target_eeprom_crc,            //!< H <- T EEPROM: bnum = N, size = 2
        target_ram_crc,               //!< H <- T RAM: bnum = N, size = 2

        //������� �������� ��������� ��������������
        target_ctrl_impulse,          //!< ��������� �������� ��������� �������������� bnum = 0 size = 0
        target_impulse_return,        //!< ������� ��������� �������� ��������� size = 128

        //������� �������� ������� ������
        target_ctrl_channel,          //!< ��������� �������� ������� bnum = 0 size = 0
        target_channel_return,        //!< ������� ��������� �������� ������� size = 128

        //������� �������� ������������ ������
        target_ctrl_calc,             //!< ��������� �������� ������������ bnum = 0 size = 0
        target_calc_return,           //!< ������� ��������� �������� ������������ size = 128

        //������� �������� ������ c �������
        host_to_target,               //!< �������� ���� ������ �������� size = N
        target_to_host,               //!< ������� ���� ������ ����� size = N

        //�������������� �������
        target_address,                //!< ������� ����� �������� ����� size = 1
	target_reset,                  //!< ����� ������ � �������� ���������
};

#pragma pack()

/*
  ����������� � ��������:

  ������� ������ �����������

  1) Host ������ ��������� ���� ��������

        H -> T (host_dbg_header)

  2) � ����������� �� ���� ������� �������� ��������� ��������

    a)  H -> T (data block)
        T -> H (target_dbg_header with data crc)

    b)  H <- T (data block)

  host_eeprom_data - ������ ����� ������ � EEPROM ��������. �������, � ��������
  ������ ����� ������ ����������� ������� ����� �������� (����) �� �����������������
  ������������. ������ ��������� ���� �� 0 �� space_info::zones.

  target_eeprom_crc - ��������� � ������� �� ������ EEPROM. ��� ���� � �������� bn �����������
  ���������� ������ �� 128 ����, ������� ���������� �������� � ������. ����� ��������� ��
  0 �� space_info::zones.

  target_eeprom_clear - ������� EEPROM. ��� ���� � �������� bn �����������
  ���������� ������ �� 128 ����, ������� ���������� �������� � ������. ����� ��������� ��
  0 �� space_info::zones.
*/

#endif //_SUL_MDO_CMD_H_
