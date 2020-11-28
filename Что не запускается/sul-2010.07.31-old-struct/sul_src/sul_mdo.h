
#ifndef _SUL_MDO_H_
#define _SUL_MDO_H_

#ifndef _SUL_BASE_H_
#include "..\base_class\sul_base.h"
#endif
#ifndef PACKET485_H
#include "packet485.h"
#endif

//---------------------------------------------------------------------------

#define MAX_ABONENT_NUMBER      5

//---------------------------------------------------------------------------
//!  ����� ��������� ��������� � ��� ���.
/*!
�������� �� �������������� � ��� ���. ��������� ��� ������������ �������,
������������ � ������ sul_base.
*/
class sul_mdo : public sul_base
{

private:
        //! ������������� ������� ��� ������ � ��� ���
        packet485	*packet;

        //! ���������� ������ �������� �� ������ ����� ��� ��������
        /*!
        \param addr - ����� �������� � �������
        */
        unsigned char bn_to_addr(unsigned bn);

        //! ���������� ������ �������� �� ��� ������
        /*!
        \param addr - ����� �������� � �������
        */
        unsigned char address(unsigned addr);

        //! �������� �� ������� � �������
        /*!
        \param addr - ����� �������� � �������
        */
        bool is_online(unsigned addr);

        //! ������� �� ���� ���� �������� ������� � �������
        bool is_any();

        //! ��������� ������ �������� ���������
        int detect();

        //! ��������� ������ �������� ���������
        void info();

        //! ���������� ���� ������ � EEPROM ��������
        /*!
        \param zone - ����� ���� ������
        \param block - ����� ����� ������ (����� ������ ��������)
        */
        int write_eeprom_block(int zone, int block);

        //! ������ ���� ������ �� EEPROM ��������
        /*!
        \param zone - ����� ���� ������
        \param block - ����� ����� ������ (����� ������ ��������)
        */
        int read_eeprom_block(int zone, int block, unsigned char *buffer, int size);

        //! �������� ���� ������ RAM ��������
        /*!
        \param zone - ����� ���� ������
        \param block - ����� ����� ������ (����� ������ ��������)
        */
        int write_ram_block(int zone, int block);

        //! ������ ���� ������ �� RAM ��������
        /*!
        \param zone - ����� ���� ������
        \param block - ����� ����� ������ (����� ������ ��������)
        */
        int read_ram_block(int zone, int block, unsigned char *buffer, int size);

        //! ����������� �� ���������
        sul_mdo();

public:
        //! ����������� ������ ��� ���
        /*!
        \param hw - ���������� ��� ������ � ��� ���
        \param sul_mdo_config - ��� ����� ������������ ���
        \param ram_mdo_config - ��� ����� ������������ RAM
        */
        sul_mdo( device *hw,
                const char *sul_mdo_config,
                const char *ram_mdo_config,
                int modules = 0,
                int channels = 0 );

        //! ����������
        virtual ~sul_mdo();

        //------------------------------------------------------------------------------
        //      ����� ��������� ���
        //------------------------------------------------------------------------------
        virtual int sul_init(int addr = 0);
        virtual int sul_reset(int addr = 0);
        virtual int sul_test(int addr = 0);
        virtual int sul_test_channels(int addr=0);
        virtual int sul_test_calculators(int addr=0);
        virtual int sul_test_pulses(int addr=0);
        virtual int sul_beam_position(u16 x=0, u16 y=0, u8 zone=0, ray_type type=RAY_NARROW);
        virtual struct sul_state sul_state(int addr=0);
        virtual int sul_set_scale(int addr=0, unsigned char scale = 1,
                                  unsigned char reset_duration = 25,
                                  unsigned char pause_duration = 20 );
        virtual unsigned char sul_get_scale(int addr);
        //------------------------------------------------------------------------------
        //      ������ � FLASH
        //------------------------------------------------------------------------------
        virtual int sul_flash_load(const char *file = NULL, int addr = 0);
        virtual int sul_flash_save(const char *file = NULL);
        virtual int sul_flash_erase(int addr = 0);
        virtual u16 sul_flash_crc(int addr = 0);
        //------------------------------------------------------------------------------
        //      ������ � RAM
        //------------------------------------------------------------------------------
        virtual int sul_ram_load(const char *file = NULL, int addr = 0);
        virtual int sul_ram_save(const char *file = NULL);
        virtual int sul_ram_erase(int addr = 0);
        virtual u16 sul_ram_crc(int addr = 0);
        //------------------------------------------------------------------------------
        //------------------------------------------------------------------------------
};

/////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------

#endif //_SUL_MDO_H_
