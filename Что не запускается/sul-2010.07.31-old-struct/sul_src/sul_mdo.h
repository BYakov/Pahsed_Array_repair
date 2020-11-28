
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
//!  Класс реализует интерфейс к СУЛ МДО.
/*!
Отвечает за взаимодействие с СУЛ МДО. Реализует все интерфейсные функции,
определенные в классе sul_base.
*/
class sul_mdo : public sul_base
{

private:
        //! Формирователь пакетов для обмена с СУЛ МДО
        packet485	*packet;

        //! Возвращает адресс абонента по номеру блока для загрузки
        /*!
        \param addr - номер абонента в массиве
        */
        unsigned char bn_to_addr(unsigned bn);

        //! Возвращает адресс абонента по его номеру
        /*!
        \param addr - номер абонента в массиве
        */
        unsigned char address(unsigned addr);

        //! Доступен ли абонент в системе
        /*!
        \param addr - адрес абонента в массиве
        */
        bool is_online(unsigned addr);

        //! Имеется ли хоть один активный абонент в системе
        bool is_any();

        //! Формирует массив активных абонентов
        int detect();

        //! Формирует массив активных абонентов
        void info();

        //! Записывает блок данных в EEPROM абонента
        /*!
        \param zone - номер зоны данных
        \param block - номер блока данных (равен номеру абонента)
        */
        int write_eeprom_block(int zone, int block);

        //! Читает блок данных из EEPROM абонента
        /*!
        \param zone - номер зоны данных
        \param block - номер блока данных (равен номеру абонента)
        */
        int read_eeprom_block(int zone, int block, unsigned char *buffer, int size);

        //! Записать блок данных RAM абоненту
        /*!
        \param zone - номер зоны данных
        \param block - номер блока данных (равен номеру абонента)
        */
        int write_ram_block(int zone, int block);

        //! Читает блок данных из RAM абонента
        /*!
        \param zone - номер зоны данных
        \param block - номер блока данных (равен номеру абонента)
        */
        int read_ram_block(int zone, int block, unsigned char *buffer, int size);

        //! Конструктор по умолчанию
        sul_mdo();

public:
        //! Конструктор класса СУЛ АВР
        /*!
        \param hw - устройство для обмена с СУЛ МДО
        \param sul_mdo_config - имя файла конфигурации СУЛ
        \param ram_mdo_config - имя файла конфигурации RAM
        */
        sul_mdo( device *hw,
                const char *sul_mdo_config,
                const char *ram_mdo_config,
                int modules = 0,
                int channels = 0 );

        //! Деструктор
        virtual ~sul_mdo();

        //------------------------------------------------------------------------------
        //      Общие параметры СУЛ
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
        //      Работа с FLASH
        //------------------------------------------------------------------------------
        virtual int sul_flash_load(const char *file = NULL, int addr = 0);
        virtual int sul_flash_save(const char *file = NULL);
        virtual int sul_flash_erase(int addr = 0);
        virtual u16 sul_flash_crc(int addr = 0);
        //------------------------------------------------------------------------------
        //      Работа с RAM
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
