
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

//! Тип луча СУЛ.
enum ray_type {
        RAY_NARROW,     //!< Узкий луч
        RAY_WIDE,       //!< Широкий луч
};

//-------------------------------------------------------------------------

//! Режим работы СУЛ.
enum sul_mode {
        mode_or = 0x1,	//!< Основной режим работы
        mode_fk = 0x2,  //!< Режим функционального контроля
        mode_rk = 0x4,  //!< Режим регламентного контроля
};

//-------------------------------------------------------------------------

//! Состояние СУЛ.
struct sul_state {
        int exch_err;  //!< Количество ошибок в обмене
        int calc_err;  //!< Количество ошибок вычислителей
        int chan_err;  //!< Количество несиправных каналов

};

//-------------------------------------------------------------------------

//! описывает флаги состояния канала управления
enum channel_state {
        channel_operational = 0x0,    //!< Канал исправен
        channel_short_circuit = 0x1,  //!< Канал неисправен (короткое замыкание)
        channel_open_fault = 0x2,     //!< Канал неисправен (обрыв соединения)
        channel_calc_operational = 0x4,     //!< Канал неисправен (ошибка вычислителя)
        channel_calc_fault = 0x8,     //!< Канал неисправен (ошибка вычислителя)
        channel_unconnected = 0x10,    //!< Канал неисправен (ошибка вычислителя)
        channel_untested = 0xff,      //!< Канал не тестировался
};

//-------------------------------------------------------------------------

//! описывает фазовращатель в составе фазированной решетки
struct phase_shifter {
        unsigned char   line;               //!< номер линейки
        unsigned char   x;                  //!< координата X
        unsigned char   y;                  //!< координата Y
        unsigned short  channel_number;     //!< номер канала
        unsigned char   abonent;            //!< номер (адрес) абонента который управляет фазовращателем
        unsigned char   connector;          //!< номер соединителя к которму подключен фазовращатель
        unsigned char   state;              //!< состояние канала
        unsigned char   chan_code;          //!< код при контроле канала
        unsigned char   calc_code;          //!< код при контроле вычислителя
        unsigned char   fi0_code;           //!< код при контроле вычислителя
        unsigned char   phase_code;         //!< код фазы в канале при расчете
        unsigned char   pulse_code;         //!< код импульса в канале при установке луча
};

//-------------------------------------------------------------------------

//! описывает модуль для управления фазовращателями в фазированной решетке
struct module {
        unsigned char  address;             //!< адрес модуля для обмена в системе СУЛ
        unsigned short device_eeprom_cs;    //!< контрольная сумма данных EEPROM модуля
        unsigned short device_ram_cs;       //!< контрольная сумма данных RAM модуля
        unsigned short config_eeprom_cs;    //!< контрольная сумма данных конфигурации EEPROM модуля
        unsigned short config_ram_cs;       //!< контрольная сумма данных конфигурации RAM модуля
};

//-------------------------------------------------------------------------

//!  Класс интерфейса СУЛ.
/*!
Класс отвечает за унифицированный интерфейс к системе СУЛ.
*/
class sul_base : public flash, public ram
{

private:
        //! Конструктор по умолчанию
        sul_base();

        fi0 *fi;

        //! Определяет постоянные параметры системы СУЛ из файла конфигурации
        int detect_sul_params();


protected:
        //! Режим работы СУЛ
        sul_mode mode;

        //! Аппаратный интерфейс связи с СУЛ
        device	*dev;

        //! Количество каналов подключенных к системе СУЛ
        int	connected_channels;

        //! Количество каналов подключенных к одному соединителю абонента
        int	pins_on_abonent_connector;

        //! Количество абонентов в системе СУЛ
        int	number_of_abonents;

        //! Количество каналов обслуживаемых одним абонентом
        int	number_of_channels;

        //! Количесво линеек в решетке
        int     number_of_lines;

        //! Нижнее значение допустимого порога при контроле каналов
        int	channel_low_level;

        //! Верхнее значение допустимого порога при контроле каналов
        int	channel_top_level;

        //! Среднее значение допустимого порога при контроле каналов
        int	channel_mid_level;

        //! Линейки в антенне
        vector<int> lines;

        //! Фазовращатели в антенне
        vector<struct phase_shifter> shifters;

        //! Абоненты управления фазовращателями
        vector<struct module> abonents;

        //! Общее состояние системы СУЛ
        struct  sul_state g_state;

        //! Создает массив описывающий линейки в фазированной антенной решетке
        int alloc_phase_shifters();

public:

        //! Выдает информацию о фазовращателе пономеру
        int sul_phase_shifter_info(unsigned int N, struct phase_shifter& shifter);

        //! Выдает информацию о фазовращателе по координатам
        int sul_phase_shifter_info(unsigned char X, unsigned char Y, struct phase_shifter& shifter);

        //! Конструктор базового класса СУЛ
        /*!
        Конструктор базового класса СУЛ
        \param sul_config - имя файла конфигурации
        \param ram_config - имя файла конфигурации
        */
        sul_base(const char *sul_config, const char *ram_config, int modules, int channels);

        //! Конструктор базового класса СУЛ
        virtual ~sul_base();

        //! Подключает устройство для обмена с СУЛ
        /*!
        \param hw - объект устройства обмена с СУЛ
        */
        virtual void sul_connect_device(device *hw);

        //! Установить режим работы СУЛ
        /*!
        Установить режим работы СУЛ
        \param m - константа режима работы
        \sa sul_mode
        */
        virtual void sul_set_mode( sul_mode m );

        //! Проинициализировать СУЛ
        /*!
        \param addr - адрес абонента для выполнения команды. addr = 0 всем абонентам
        */
        virtual int  sul_init(int addr=0) = 0;

        //! Сбросить СУЛ
        /*!
        \param addr - номер абонента для выполнения команды. addr = 0 всем абонентам
        */
        virtual int  sul_reset(int addr=0) = 0;

        //! Провести комплексное тестирование системы СУЛ
        /*!
        \param addr - номер абонента для выполнения команды. addr = 0 - вс
        */
        virtual int sul_test(int addr=0) = 0;

        //! Количество каналов абонента или всей системы СУЛ
        /*!
        \param addr - число каналов абонента. addr = 0 - общее число каналов
        */
        virtual int sul_total_channels(int addr=0);

        //! Количество линеек системы СУЛ
        virtual int sul_total_lines();

        //! Количество абонентов системы СУЛ
        virtual int sul_total_abonents();

        //! Количество активных абонентов системы СУЛ
        virtual int sul_active_abonents();

        //! Адрес абонента системы СУЛ
        virtual int sul_abonent_address(unsigned index);

        //! Установка верхней границы при контроле каналов
        /*!
        \param value - значение кода
        */
        virtual void sul_set_top_level(int value);

        //! Установка нижней границы при контроле каналов
        /*!
        \param value - значение кода
        */
        virtual void sul_set_low_level(int value);

        //! Провести тестирование каналов абонента системы СУЛ (результат в буфер пользователя)
        /*!
        \param addr - номер абонента для выполнения команды.
        \param buffer - буфер для записи информации о состоянии каналов.
        */
        virtual int sul_test_channels(int addr=0) = 0;

        //! Провести тестирование вычислителей абонента системы СУЛ
        /*!
        \param addr - номер абонента для выполнения команды.
        \param buffer - буфер для записи информации о состоянии вычислителей.
        */
        virtual int sul_test_calculators(int addr=0) = 0;

        //! Провести тестирование импульсов установки луча СУЛ
        /*!
        \param addr - номер абонента для выполнения команды.
        \param buffer - буфер для записи информации о состоянии кодов импульсов.
        */
        virtual int sul_test_pulses(int addr=0) = 0;

        //! Выдать состояние абонента или всей системы СУЛ
        /*!
        \param addr - номер абонента для выполнения команды. addr = 0 всем абонентам
        */
        virtual struct sul_state sul_state(int addr=0) = 0;

        //! Установить луч
        /*!
        Устанавливает положение луча СУЛ в координаты x, y, и задает
        номер зоны для выбора коэффициентов корректур.
        \param x - координата по оси X
        \param y - координата по оси Y
        \param zone - номер зоны с коэффициентами корректур
        \param type - тип луча (узкий луч, широкий луч)
        \sa ray_type
        */
        virtual int sul_beam_position(u16 x=0, u16 y=0, u8 zone=0, ray_type type=RAY_NARROW) = 0;

        //! Установить масштабный коэффициент и длительность сигнала сброса для абонента
        /*!
        \param addr - номер абонента для выполнения команды.
        \param scale - коэффициент (scale != 0)
        \param reset_duration - длительность сброса в микросекундах
        \param pause_duration - длительность паузы после сброса в микросекундах
        */
        virtual int sul_set_scale(int addr=0, unsigned char scale = 1,
                                  unsigned char reset_duration = 25,
                                  unsigned char pause_duration = 20 ) = 0;

        //! Прочитать масштабный коэффициент абонента
        /*!
        \param addr - номер абонента для выполнения команды.
        */
        virtual unsigned char sul_get_scale(int addr) = 0;
};

/////////////////////////////////////////////////////////////////////

#endif //_SUL_BASE_H_
