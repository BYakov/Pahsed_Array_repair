
#ifndef _RAM_CONFIG_H_
#define _RAM_CONFIG_H_

//------------------------------------------------------------------------------

class ram : public space {

private:
        ram();

        unsigned char  	        *tuned_data;  //!< ���������������� ������������ ��� ������������ ��������� ���

protected:

        const struct space_info& ram_file_info();
        int ram_reconfig(const char *config);
        int ram_reconfig(const char *config, int block_count = 0);
        const unsigned char *ram_data_block(int zone,int block);

public:
        ram(const char *ram);
        virtual ~ram();

        const char *ram_config_file();

        int ram_block_size() { return info.block_size; }
        int ram_block_count() { return info.blocks_in_zone; }
        int ram_zone_count() { return info.zones ; }

        //! ������������� �������� �������� RAM.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param offset - �������� � ����� (����� ��������)
        \param data - ������� ������
        */
        int sul_ram_set_element(int zone, int block, int offset, u8& data);

        //! ���������� �������� �������� RAM.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param offset - �������� � ����� (����� ��������)
        \param *data - ������� ������
        */
        int sul_ram_get_element(int zone, int block, int offset, u8& data);

        //! ��������� ��������� ������� RAM.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param type - ��� ����������
        \param pattern - ������ ��� ����������
        */
        int sul_ram_fill(int zone, int block, space_fill_type type = FILL_RANDOM, u8 pattern = 0);

        //! �������� ����������� ����� �� ������������ ������������
        /*!
        \param devn - ����� �������� ��� ���������� �������. 0 - ����� �� ���� ���������
        */
        virtual  u16 sul_ram_space_crc(int devn = 0);

        //! �������� ���������������� ���������� �� FLASH ��� ���� ���������
        /*!
        �������� ���������� �� ����� ������������ �� FLASH ����������
        \param file - ��� ����� ������������
        \param devn - ����� ��������. 0 - ��� ���� ���������.
        */
        virtual int sul_ram_load(const char *file = NULL, int devn = 0) = 0;

        //! �������� �������������� ������������ ������� �� �����.
        /*!
        ������� ������� ������ ������������, �������
        � ��������� ����� ���������������� ������������
        �� ������ ����� config.
        \param config - ��� ������ ����� ������������
        */
        virtual int sul_ram_reconfig(const char *config);

        //! ��������� ���������������� ���������� �� RAM � ����
        /*!
        �������� ���������� �� ����� ������������ �� FLASH ����������
        \param file - ��� ����� ������������
        */
        virtual  int sul_ram_save(const char *file = NULL) = 0;

        //! ������� ���������������� ���������� RAM
        /*!
        \param devn - ����� �������� ��� ���������� �������. 0 - ��� ���� ���������
        */
        virtual  int sul_ram_erase(int devn = 0) = 0;

        //! �������� ����������� ����� ���������� �� RAM
        /*!
        \param devn - ����� �������� ��� ���������� �������. 0 - ����� �� ���� ���������
        */
        virtual  u16 sul_ram_crc(int devn = 0) = 0;
};

//------------------------------------------------------------------------------

#endif //_RAM_CONFIG_H_
