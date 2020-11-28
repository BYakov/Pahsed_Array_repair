
#ifndef _SUL_BASE_H_
#define _SUL_BASE_H_

#ifndef _MESSAGE_H_
#include "message.h"
#endif

#ifndef _FLASH_CONFIG_H_
#include "flash_config.h"
#endif

#ifndef _RAM_CONFIG_H_
#include "ram_config.h"
#endif

#ifndef _FI0_CONFIG_H_
#include "fi0_config.h"
#endif

#ifndef _DEVICE_H_
#include "device.h"
#endif

//-------------------------------------------------------------------------

#include <vector>

//-------------------------------------------------------------------------

using namespace std;

//-------------------------------------------------------------------------

//! ��� ���� ���.
enum ray_type {
        RAY_NARROW,     //!< ����� ���
        RAY_WIDE,       //!< ������� ���
};

//-------------------------------------------------------------------------

//! ����� ������ ���.
enum sul_mode {
        mode_or = 0x1,	//!< �������� ����� ������
        mode_fk = 0x2,  //!< ����� ��������������� ��������
        mode_rk = 0x4,  //!< ����� ������������� ��������
};

//-------------------------------------------------------------------------

//! ��������� ���.
struct sul_state {
        int exch_err;  //!< ���������� ������ � ������
        int calc_err;  //!< ���������� ������ ������������
        int chan_err;  //!< ���������� ����������� �������

};

//-------------------------------------------------------------------------

//! ��������� ����� ��������� ������ ����������
enum channel_state {
        channel_operational = 0x0,    //!< ����� ��������
        channel_short_circuit = 0x1,  //!< ����� ���������� (�������� ���������)
        channel_open_fault = 0x2,     //!< ����� ���������� (����� ����������)
        channel_calc_operational = 0x4,     //!< ����� ���������� (������ �����������)
        channel_calc_fault = 0x8,     //!< ����� ���������� (������ �����������)
        channel_unconnected = 0x10,    //!< ����� ���������� (������ �����������)
        channel_untested = 0xff,      //!< ����� �� ������������
};

//-------------------------------------------------------------------------

//! ��������� ������������� � ������� ������������ �������
struct phase_shifter {
        unsigned char   line;               //!< ����� �������
        unsigned char   x;                  //!< ���������� X
        unsigned char   y;                  //!< ���������� Y
        unsigned short  channel_number;     //!< ����� ������
        unsigned char   abonent;            //!< ����� (�����) �������� ������� ��������� ��������������
        unsigned char   connector;          //!< ����� ����������� � ������� ��������� �������������
        unsigned char   state;              //!< ��������� ������
        unsigned char   chan_code;          //!< ��� ��� �������� ������
        unsigned char   calc_code;          //!< ��� ��� �������� �����������
        unsigned char   fi0_code;           //!< ��� ��� �������� �����������
        unsigned char   phase_code;         //!< ��� ���� � ������ ��� �������
        unsigned char   pulse_code;         //!< ��� �������� � ������ ��� ��������� ����
};

//-------------------------------------------------------------------------

//! ��������� ������ ��� ���������� ��������������� � ������������ �������
struct module {
        unsigned char  address;             //!< ����� ������ ��� ������ � ������� ���
        unsigned short device_eeprom_cs;    //!< ����������� ����� ������ EEPROM ������
        unsigned short device_ram_cs;       //!< ����������� ����� ������ RAM ������
        unsigned short config_eeprom_cs;    //!< ����������� ����� ������ ������������ EEPROM ������
        unsigned short config_ram_cs;       //!< ����������� ����� ������ ������������ RAM ������
};

//-------------------------------------------------------------------------

//!  ����� ���������� ���.
/*!
����� �������� �� ��������������� ��������� � ������� ���.
*/
class sul_base : public flash, public ram
{

private:
        //! ����������� �� ���������
        sul_base();

        fi0 *fi;

        //! ���������� ���������� ��������� ������� ��� �� ����� ������������
        int detect_sul_params();


protected:
        //! ����� ������ ���
        sul_mode mode;

        //! ���������� ��������� ����� � ���
        device	*dev;

        //! ���������� ������� ������������ � ������� ���
        int	connected_channels;

        //! ���������� ������� ������������ � ������ ����������� ��������
        int	pins_on_abonent_connector;

        //! ���������� ��������� � ������� ���
        int	number_of_abonents;

        //! ���������� ������� ������������� ����� ���������
        int	number_of_channels;

        //! ��������� ������ � �������
        int     number_of_lines;

        //! ������ �������� ����������� ������ ��� �������� �������
        int	channel_low_level;

        //! ������� �������� ����������� ������ ��� �������� �������
        int	channel_top_level;

        //! ������� �������� ����������� ������ ��� �������� �������
        int	channel_mid_level;

        //! ������� � �������
        vector<int> lines;

        //! ������������� � �������
        vector<struct phase_shifter> shifters;

        //! �������� ���������� ���������������
        vector<struct module> abonents;

        //! ����� ��������� ������� ���
        struct  sul_state g_state;

        //! ������� ������ ����������� ������� � ������������ �������� �������
        int alloc_phase_shifters();

public:

        //! ������ ���������� � ������������� ��������
        int sul_phase_shifter_info(unsigned int N, struct phase_shifter& shifter);

        //! ������ ���������� � ������������� �� �����������
        int sul_phase_shifter_info(unsigned char X, unsigned char Y, struct phase_shifter& shifter);

        //! ����������� �������� ������ ���
        /*!
        ����������� �������� ������ ���
        \param sul_config - ��� ����� ������������
        \param ram_config - ��� ����� ������������
        */
        sul_base(const char *sul_config, const char *ram_config, int modules, int channels);

        //! ����������� �������� ������ ���
        virtual ~sul_base();

        //! ���������� ���������� ��� ������ � ���
        /*!
        \param hw - ������ ���������� ������ � ���
        */
        virtual void sul_connect_device(device *hw);

        //! ���������� ����� ������ ���
        /*!
        ���������� ����� ������ ���
        \param m - ��������� ������ ������
        \sa sul_mode
        */
        virtual void sul_set_mode( sul_mode m );

        //! ������������������� ���
        /*!
        \param addr - ����� �������� ��� ���������� �������. addr = 0 ���� ���������
        */
        virtual int  sul_init(int addr=0) = 0;

        //! �������� ���
        /*!
        \param addr - ����� �������� ��� ���������� �������. addr = 0 ���� ���������
        */
        virtual int  sul_reset(int addr=0) = 0;

        //! �������� ����������� ������������ ������� ���
        /*!
        \param addr - ����� �������� ��� ���������� �������. addr = 0 - ��
        */
        virtual int sul_test(int addr=0) = 0;

        //! ���������� ������� �������� ��� ���� ������� ���
        /*!
        \param addr - ����� ������� ��������. addr = 0 - ����� ����� �������
        */
        virtual int sul_total_channels(int addr=0);

        //! ���������� ������ ������� ���
        virtual int sul_total_lines();

        //! ���������� ��������� ������� ���
        virtual int sul_total_abonents();

        //! ���������� �������� ��������� ������� ���
        virtual int sul_active_abonents();

        //! ����� �������� ������� ���
        virtual int sul_abonent_address(unsigned index);

        //! ��������� ������� ������� ��� �������� �������
        /*!
        \param value - �������� ����
        */
        virtual void sul_set_top_level(int value);

        //! ��������� ������ ������� ��� �������� �������
        /*!
        \param value - �������� ����
        */
        virtual void sul_set_low_level(int value);

        //! �������� ������������ ������� �������� ������� ��� (��������� � ����� ������������)
        /*!
        \param addr - ����� �������� ��� ���������� �������.
        \param buffer - ����� ��� ������ ���������� � ��������� �������.
        */
        virtual int sul_test_channels(int addr=0) = 0;

        //! �������� ������������ ������������ �������� ������� ���
        /*!
        \param addr - ����� �������� ��� ���������� �������.
        \param buffer - ����� ��� ������ ���������� � ��������� ������������.
        */
        virtual int sul_test_calculators(int addr=0) = 0;

        //! �������� ������������ ��������� ��������� ���� ���
        /*!
        \param addr - ����� �������� ��� ���������� �������.
        \param buffer - ����� ��� ������ ���������� � ��������� ����� ���������.
        */
        virtual int sul_test_pulses(int addr=0) = 0;

        //! ������ ��������� �������� ��� ���� ������� ���
        /*!
        \param addr - ����� �������� ��� ���������� �������. addr = 0 ���� ���������
        */
        virtual struct sul_state sul_state(int addr=0) = 0;

        //! ���������� ���
        /*!
        ������������� ��������� ���� ��� � ���������� x, y, � ������
        ����� ���� ��� ������ ������������� ���������.
        \param x - ���������� �� ��� X
        \param y - ���������� �� ��� Y
        \param zone - ����� ���� � �������������� ���������
        \param type - ��� ���� (����� ���, ������� ���)
        \sa ray_type
        */
        virtual int sul_beam_position(u16 x=0, u16 y=0, u8 zone=0, ray_type type=RAY_NARROW) = 0;

        //! ���������� ���������� ����������� � ������������ ������� ������ ��� ��������
        /*!
        \param addr - ����� �������� ��� ���������� �������.
        \param scale - ����������� (scale != 0)
        \param reset_duration - ������������ ������ � �������������
        \param pause_duration - ������������ ����� ����� ������ � �������������
        */
        virtual int sul_set_scale(int addr=0, unsigned char scale = 1,
                                  unsigned char reset_duration = 25,
                                  unsigned char pause_duration = 20 ) = 0;

        //! ��������� ���������� ����������� ��������
        /*!
        \param addr - ����� �������� ��� ���������� �������.
        */
        virtual unsigned char sul_get_scale(int addr) = 0;
};

/////////////////////////////////////////////////////////////////////

#endif //_SUL_BASE_H_
