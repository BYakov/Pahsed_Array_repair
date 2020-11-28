
#ifndef _FLASH_CONFIG_H_
#define _FLASH_CONFIG_H_

#ifndef _SUL_CONFIG_H_
    #include "sul_config.h"
#endif

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

class flash : public space {

private:
        flash();

protected:

        //! ���������� ���������� � ��������� ����������������� ������������ FLASH.
        const struct space_info& flash_file_info();

        //! �������� ���� ������ �� ����������������� ������������ FLASH
        /*!
        \param zone - ����� �������� (������� � ����) �� �������� ������� ���� .
        \param block - ����� ����� ������������ ������ ��������.
        */
        const unsigned char *flash_data_block(int zone,int block);

public:

        flash(const char *file, int modules, int channels);
        virtual ~flash();

        //! ���������� ��� ����������������� ����� FLASH.
        const char *flash_config_file();

        //! ���������� ������ ����� ������ FLASH.
        int flash_block_size() { return info.block_size ; }

        //! ���������� ���������� ������ ������ FLASH � ����� ��������.
        int flash_block_count() { return info.blocks_in_zone ; }

        //! ���������� ���������� ��������� ������ FLASH � ������������.
        int flash_zone_count() { return info.zones ; }

        //! ������������� �������� �������� FLASH.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param offset - �������� � ����� (����� ��������)
        \param data - ������� ������
        */
        int sul_flash_set_element(int zone, int block, int offset, u8& data);

        //! ���������� �������� �������� FLASH.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param offset - �������� � ����� (����� ��������)
        \param *data - ������� ������
        */
        int sul_flash_get_element(int zone, int block, int offset, u8& data);

        //! ��������� ��������� ������� FLASH.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param type - ��� ����������
        \param pattern - ������ ��� ����������
        */
        int sul_flash_fill(int zone, int block, space_fill_type type = FILL_RANDOM, u8 pattern = 0);

        //! �������� ����������� ����� �� ������������ ������������
        /*!
        \param devn - ����� �������� ��� ���������� �������. 0 - ����� �� ���� ���������
        */
        u16 sul_flash_space_crc(int devn = 0);

        //! �������� ���������������� ���������� �� FLASH ��� ���� ���������
        /*!
        �������� ���������� �� ����� ������������ �� FLASH ����������
        \param file - ��� ����� ������������
        \param devn - ����� ��������. 0 - ��� ���� ���������.
        */
        virtual  int sul_flash_load(const char *file = NULL, int devn = 0) = 0;

        //! �������� �������������� ������������ ������� �� �����.
        /*!
        ������� ������� ������ ������������, �������
        � ��������� ����� ���������������� ������������
        �� ������ ����� config.
        \param config - ��� ������ ����� ������������
        */
        virtual int sul_flash_reconfig(const char *config);

        //! ��������� ���������������� ���������� �� FLASH � ����
        /*!
        �������� ���������� �� ����� ������������ �� FLASH ����������
        \param file - ��� ����� ������������
        */
        virtual  int sul_flash_save(const char *file = NULL) = 0;

        //! ������� ���������������� ���������� FLASH
        /*!
        \param devn - ����� �������� ��� ���������� �������. 0 - ��� ���� ���������
        */
        virtual  int sul_flash_erase(int devn = 0) = 0;

        //! �������� ����������� ����� ���������� �� FLASH
        /*!
        \param devn - ����� �������� ��� ���������� �������. 0 - ����� �� ���� ���������
        */
        virtual  u16 sul_flash_crc(int devn = 0) = 0;
};

//------------------------------------------------------------------------------

#endif //_FLASH_CONFIG_H_
