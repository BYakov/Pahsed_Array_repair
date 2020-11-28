
#ifndef _SUL_MDO_CMD_H_
#define _SUL_MDO_CMD_H_

#pragma pack(1)

//! Сигнатура заголовка передаваемого или принимаемого пакета
enum header_signature {
        host_signature      = 0xAA, //!< Код сигнатуры (начало сообщения HOST -> TARGET)
        target_signature    = 0xBB, //!< Код сигнатуры (начало сообщения HOST <- TARGET)
//	main_signature      = 0xCC, //!< Код сигнатуры (начало сообщения HOST -> TARGET)
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//! Заголовок пакета данных основного режима
struct main_header {
        unsigned char sign;     //!< Сигнатура заголовка
        unsigned char addr;     //!< Адрес абонента для получения пакета и код команды
};

//! Данные пакета основного режима
struct main_data {
        unsigned short x;     //!< Координата Х
        unsigned short y;     //!< Координата Y
        unsigned char cmd;    //!< Командное слово (биты 0..3 - номер зоны, 4..7 - резерв)
};

//! Окончание пакета данных основного режима
struct main_tail {
        unsigned char mcrc;     //!< Контрольная сумма пакета основного режима
};

//! Пакет основного режима
struct main_packet {
        struct main_header      mhdr;   //!< Заголовок пакета основного режима
        struct main_data        mdata;  //!< Данные пакета основного режима
        struct main_tail        mtail;  //!< Окончание пакета основного режима
};

//!Коды номеров зон основного режима
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

//!заголовок пакета (HOST -> TARGET) данных отладочного режима
struct host_dbg_header {
        unsigned char sign;     //!< Сигнатура заголовка (host_signature)
        signed   char addr;     //!< Адрес абонента для получения пакета
        unsigned char code;     //!< Код команды
        unsigned char size;     //!< Размер данных пакета
        unsigned char dcrc;     //!< Контрольная сумма данных пакета
        unsigned char bnum;     //!< Номер блока данных инициализации или контроля
        unsigned char txrx;     //!< Флаг приема/передачи (0: H->T, 1: H<-T)
        unsigned char hcrc;     //!< Контрольная сумма заголовка
};

//! Значения флага host_dbg_header::txrx
enum trans_type {
        to_empty = 0,               //!< Неопределенное значение
        to_target = 1,              //!< H -> T + DATA
        to_host = 2,                //!< H <- T + DATA
        to_target_cmd = 3,          //!< H <- T + NO DATA
};

//!заголовок пакета (HOST <- TARGET) данных отладочного режима
struct target_dbg_header {
        unsigned char sign;     //!< Сигнатура заголовка (target_signature)
        signed   char addr;     //!< Адрес абонента для получения пакета
        unsigned char code;     //!< Код команды
        unsigned char crc;      //!< Контрольная сумма заголовка/данных пакета
};

//! Сформированный пакет (основной или отладочный)
struct packet {
        unsigned char *paddr;       //!< Адрес сформированного пакета
        unsigned long  length;      //!< Длина пакета в байтах
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//! Коды команд отладочного режима
enum sul_mdo_cmd {

	//команды настройки модуля
	host_eeprom_data = 0x01,      //!< H->T EEPROM: bnum = N, size = 128
	host_ram_data,                //!< H->T RAM: bnum = N, size = 128
	host_scale,		      //!< H->T size = 2 Установить установить коэффициент масштаба
	target_scale_return,          //!< H<-T size = 2 Вернуть коэффициент масштаба

        //команды инициализации модуля
        target_eeprom_to_plm,         //!< Переписать данные EEPROM -> PLM
        target_ram_to_plm,            //!< Переписать данные RAM -> PLM
        target_eeprom_clear,          //!< Очистить EEPROM: bnum = N, dummy size = 128
        target_ram_clear,             //!< Очистить RAM: bnum = N, dummy size = 128

        //команды контроля данных инициализации
        target_eeprom_data,           //!< H <- T EEPROM: bnum = N, size = 128
        target_ram_data,              //!< H <- T RAM: bnum = N, size = 128
        target_eeprom_crc,            //!< H <- T EEPROM: bnum = N, size = 2
        target_ram_crc,               //!< H <- T RAM: bnum = N, size = 2

        //команды контроля импульсов намагничивания
        target_ctrl_impulse,          //!< Выполнить контроль импульсов намагничивания bnum = 0 size = 0
        target_impulse_return,        //!< Вернуть результат контроля импульсов size = 128

        //команды контроля каналов модуля
        target_ctrl_channel,          //!< Выполнить контроль каналов bnum = 0 size = 0
        target_channel_return,        //!< Вернуть результат контроля каналов size = 128

        //команды контроля вычислителей модуля
        target_ctrl_calc,             //!< Выполнить контроль вычислителей bnum = 0 size = 0
        target_calc_return,           //!< Вернуть результат контроля вычислителей size = 128

        //команды проверки обмена c модулем
        host_to_target,               //!< Передать блок данных абоненту size = N
        target_to_host,               //!< Вернуть блок данных хосту size = N

        //дополнительные команды
        target_address,                //!< Вернуть адрес абонента хосту size = 1
	target_reset,                  //!< Сброс модуля в исходное состояние
};

#pragma pack()

/*
  Комментарии к командам:

  Порядок обмена информацией

  1) Host выдает командный блок абоненту

        H -> T (host_dbg_header)

  2) В зависимости от кода команды получаем следующую ситуацию

    a)  H -> T (data block)
        T -> H (target_dbg_header with data crc)

    b)  H <- T (data block)

  host_eeprom_data - запись блока данных в EEPROM абонента. Приэтом, в качестве
  номера блока данных указывается текущий номер сегмента (зоны) из конфигурационного
  пространства. номера сегментов идут от 0 до space_info::zones.

  target_eeprom_crc - посчитать и вернуть КС данных EEPROM. При этом в качестве bn указывается
  количество блоков по 128 байт, которые необходимо включить в расчет. Блоки считаются от
  0 до space_info::zones.

  target_eeprom_clear - стереть EEPROM. При этом в качестве bn указывается
  количество блоков по 128 байт, которые необходимо включить в расчет. Блоки считаются от
  0 до space_info::zones.
*/

#endif //_SUL_MDO_CMD_H_
