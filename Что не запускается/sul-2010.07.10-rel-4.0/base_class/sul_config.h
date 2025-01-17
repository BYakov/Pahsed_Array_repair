
#ifndef _SUL_CONFIG_H_
#define _SUL_CONFIG_H_

#ifndef _MESSAGE_H_
#include "message.h"
#endif

//------------------------------------------------------------------------------

//! ��� ���������� ����������������� ������������
enum space_fill_type {
        FILL_RANDOM,            //!< ��������� �.�. �� ������������ ������
        FILL_PATTERN,           //!< ��������� ��������� ���������
};

//------------------------------------------------------------------------------

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned long	u32;

//------------------------------------------------------------------------------

//! ���������� � ��������� ����� ������������ ���
/*!

������ ������ �������� ������ (����) ������������ ����������� �������� [...]
����� ������ ������ ��������, ��� ������� �� ���������, ����������
���� �� ����� ������ �������. ����� ������ ����� ���������� ����
�� ����� ���������. ����� ����� ������ ���������� ����� �������� ��� �������� ����
���� ������ ������������. ����� �������� ������������ ���������� �����������
�������� ������ � �� ������� �� ��� ������. � ������� ����������� ���������, ��
������ ����� ������ ����� ���������� ����� ��������.

���� ������������ ����� ��������� ���������:

;               - �����������

[ZONE 0]        - ������� ����� ���� ������ (���������, ��������� � �. �.)

0..127 ����     - ���� ������ ��� �������� 0

0..127 ����     - ���� ������ ��� �������� 1

0..127 ����     - ���� ������ ��� �������� 2

...

0..127 ����     - ���� ������ ��� �������� N-1

[ZONE 1]

[ZONE 2]

[ZONE 3]

...

[ZONE M-1]
*/
struct space_info {

        int		zones;			//!< ���������� ��� � ����� ������������
        int		zone_size;		//!< ������ ���� (� ������)
        int		blocks;			//!< ���������� ����������� ������ � ������� � ����� ������������
        int		block_size;		//!< ������ ����� � ������� � ����� ������������ (� ������)
        int		channels;		//!< �������� ���������� ������� ������������� ����� ���������
        int		total_size;		//!< ����� ������ ����������������� ������������ ��� (� ������)
        int		total_blocks;	        //!< ����� ���������� ������ � ���������������� ������������ ���
        int		blocks_in_zone;	        //!< ���������� ������ � ����� ���� (��������� � ����������� ���������)

        unsigned short  checksum;		//!< ����������� ����� ���� ������ ������������
};

//------------------------------------------------------------------------------

//! ����� ������������ ������������ ���.
/*!
����� �������� �� ������ � ������� ������������ ���. (RAM, FLASH, EEPROM � ��.)
�� ����� ������������ ���������� ���������� ����������������� ������������ ���.
��� ����������� ������ ��� ���������� ������������ �����������
������������� � ������� space_detect_params(). �� ���� ������������ �������������
������������ �����������:

- ����� � ������� ��������� ���� �� ����� ������ �������/��������;
- ������ � ����� ��������� ���������;
- ; �����������
- [ ����������� ������ ������ �������� (����)

\sa space_detect_params()
*/
class space
{

private:

        //! ����������� �� ���������
        space();

        char		        *file_name;		//!< ��� ����� ������������
        unsigned char  	        *space_data;		//!< ���������������� ������������ ���
        unsigned char  	        *user_block;	        //!< �������� ������ ����������������� �����
        bool                     configured;            //!< ���� ������������

        //! ������� �������������� ���������� ����� ������������
        /*!
        ������� ������ ���� ������������ � ����������� ���������� ��������
        ��������� ������ ������:
        - zones;
        - zone_size;
        - blocks;
        - block_size;
        - total_size;
        - total_blocks;
        - blocks_in_zone
        */
        int space_autodetect_params();

        //! ������� ���������������� ������������ ���
        /*!
        ������� ���������������� ������������ ��� �� ����
        ���������� �� ��������� cfg_info, ������� �����������
        �������� space_detect_params().
        \sa int space_detect_params(void);
        \sa space_info;
        */
        int space_create_memory();

        //! ��������� ��������� ���������������� ������������ ���
        /*!
        \sa int space_create_memory(void);
        */
        int space_fill_memory();

        //! �������� ������ ����� ������ ��� ��������� ���� ����������������� ������������ ���
        /*!
        \param zone - ����� ���� (������� � ����).
        */
        int space_clear_zone(int zone);

protected:

        message                 log;		//!< ����� ���������
        struct space_info       info;		//!< �������� ����������� ���������� � ����� ������������

        //! ����������� ������ ������������ ���
        /*!
        \param config - ��� ����� ������������ ���.
        */
        space(const char *config);

        //! ���������� ������ ������������ ���
        virtual ~space();

        //! �������� ����� ������������ ���
        bool space_configured(){ return configured; }

        //! �������� �������������� ������������ � �������.
        /*!
        ������� ������� ������ ������������, �������
        � ��������� ����� ���������������� ������������
        �� ������ ����� config.
        \param config - ��� ������ ����� ������������
        */
        int space_reconfig_memory(const char *config);

        //! �������� ���������������� ������������ ��� � ����.
        /*!
        ������� ���������� ���������������� ������������ ���
        � �������� ���������������� ����.
        \param config - ��� ������ ����� ������������ ���
        */
        int space_save_memory(const char *config = NULL);

        //! ���������� ����������� ����� ����������������� ������������ ��� ��������
        /*!
        \param devn - ����� �������� ��� �������� ���������� ���������
        ����������� �����. devn - �������� ����� ����������� ������ ����� ������.
        ���� devn = 0 - �� ������������ ����������� ����� ����� ������������.
        */
        unsigned short space_data_crc(int devn = 0);

        //! �������� ���� ������ �� ����������������� ������������ ���
        /*!
        \param zone - ����� �������� (������� � ����) �� �������� ������� ���� .
        \param block - ����� ����� ������������ ������ ��������.
        */
        const unsigned char* space_data_block(int zone,int block);

        //! ���������� ���������� � ���������������� ������������ ���.
        const struct space_info& space_info(void) {return info;}

        //! ���������� ��� ����������������� ����� ���.
        const char *space_config_file() {return file_name;}

        //! ������������� �������� �������� � ���������������� ������������.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� ����� ������������ ��������
        \param offset - �������� � �����
        \param data - ������� ������
        */
        int space_set_element(int zone, int block, int offset, u8& data);

        //! ���������� �������� �������� � ���������������� ������������.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� ����� ������������ ��������
        \param offset - �������� � �����
        \param data - ������� ������
        */
        int space_get_element(int zone, int block, int offset, u8& data);

        //! ��������� ��������� ������� ��������� ���� ������������.
        /*!
        \param zone - ����� �������� (������� � ����)
        \param block - ����� �����, ������������ ������ ��������
        \param type - ��� ����������
        \param pattern - ������ ��� ����������
        */
        int space_fill(int zone, int block, space_fill_type type, u8 pattern);
};

//------------------------------------------------------------------------------

#endif //_SUL_CONFIG_H_
