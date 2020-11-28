
#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifndef _MESSAGE_H_
#include "message.h"
#endif

#include <windows.h>
#include <winioctl.h>

//-----------------------------------------------------------------------------
//! Константы кодов ошибок
enum error_code {
	status_ok				= 0x0,	//<! ошибок нет
	error_device_handle		= 0x1,	//<! ошибка открытия файла устройства
	error_event_handle		= 0x2,	//<! ошибка открытия события
	error_wait_timeout		= 0x3,	//<! таймаут ожидания события
	error_ioctl_request		= 0x4,	//<! ошибка обращения к драйверу устройства
	error_event_busy		= 0x5,	//<! событие уже используется
	error_event_index		= 0x6,	//<! недопустимый индекс события 
	error_not_implemented	= 0x7,	//<! функция не реализована
};

//! Количество событий которых может ожидать пользовательская программа.
#define		EVENT_NUMBER	8

//! Интерфейс устройства.
/*!
Предоставляет абстрактный интерфейс к устройствам ввода-вывода.
*/

class device 
{

private:

	//! Конструктор класса по умолчанию.
	device();

	//! Имя устройства
	char *dev_name;

	//! Дескриптор файла устройства
	void *fd;

	//! Дескрипторы событий
	void *event[EVENT_NUMBER];

	bool opened;
	bool mapped;

protected:

	//! Вывод диагностических сообщений
	message log;
	//! Проверяет дескриптор события
	bool is_event(int idx=0);
	//! Создает разделяемое событие
	bool create_event(const char *name, int idx = 0);
	//! Возвращает дескриптор устройства
	void *get_handle() { return fd; }
	//! Возвращает имя устройства
	const char *name() { return dev_name; }
	//! Возвращает дескриптор события
	void *get_event(int idx=0) { return (idx < EVENT_NUMBER ? event[idx] : NULL); }

public:

	//! Конструктор класса устройства.
	/*!
	\param name имя устройства.
	\param flags - дополнительные флаги открытия устройства.
	*/
	device(const char *name, int flags = 0);

	//! Деструктор класса устройства.
	virtual ~device();

	//! Проверяет открыто устройство или нет
	bool is_open();

	//! Чтение данных из устройства ("сырое").
	/*!
	\param data - указатель на пользовательский буфер размером size.
	\param size - количество байт для чтения из устройства.
	\param timeout - таймаут операции.
	*/
	virtual int read_raw(void *data, int size, int timeout=0);

	//! Запись данных в устройство ("сырая").
	/*!
	\param data - указатель на пользовательский буфер размером size.
	\param size - количество байт для записи в устройство.
	\param timeout - таймаут операции.
	*/
	virtual int write_raw(void *data, int size, int timeout=0);

	//! Чтение из устройства.
	/*!
	\param data - указатель на пользовательский буфер размером size.
	\param size - количество байт для чтения из устройства.
	\param timeout - таймаут операции.
	*/
	virtual int read_data(void *data, int size, int timeout=0) = 0;

	//! Запись данных в устройство.
	/*!
	\param data - указатель на пользовательский буфер размером size.
	\param size - количество байт для записи в устройство.
	\param timeout - таймаут операции.
	*/
	virtual int write_data(const void *data, int size, int timeout=0) = 0;

	//! Чтение регистра устройства.
	/*!
	\param reg - указатель на пользовательский буфер размером size.
	\param val - прочитанное значение регистра.
	\param timeout - таймаут операции.
	*/
	virtual int read_register(unsigned reg, unsigned long &val, int timeout=0) = 0;

	//! Запись регистра устройства.
	/*!
	\param reg - указатель на пользовательский буфер размером size.
	\param val - записываемое значение регистра.
	\param timeout - таймаут операции.
	*/
	virtual int write_register(unsigned reg, unsigned long &val, int timeout=0) = 0;

	//! Чтение памяти из устройства.
	/*!
	\param mem - адрес ячейки памяти.
	\param val - прочитанное значение из памяти.
	\param timeout - таймаут операции.
	*/
	virtual int read_memory(unsigned mem, unsigned long &val, int timeout=0) = 0;

	//! Запись в память устройства.
	/*!
	\param mem - указатель на пользовательский буфер размером size.
	\param val - записываемое в память значение.
	\param timeout - таймаут операции.
	*/
	virtual int write_memory(unsigned mem, unsigned long &val, int timeout=0) = 0;

	//! Чтение регистра конфигурационного пространства устройства.
	/*!
	\param offset - смещение регистра в конфигурационном пространстве.
	\param val - считываемое значение.
	\param timeout - таймаут операции.
	*/
	virtual int read_config(unsigned offset, unsigned long &val, int timeout=0) = 0;

	//! Запись регистра конфигурационного пространства устройства.
	/*!
	\param offset - смещение регистра в конфигурационном пространстве.
	\param val - записываемое значение.
	\param timeout - таймаут операции.
	*/
	virtual int write_config(unsigned offset, unsigned long &val, int timeout=0) = 0;

	//! Зарегистрировать именованое событие ввода/вывода устройства
	/*!
	\param name - имя разделяемого события.
	\param idx - номер разделяемого события.
	*/
	virtual int register_event( char *name, int idx = 0 ) = 0;

	//! Ожидать событие ввода/вывода устройства
	/*!
	\param timeout - время ожидания (мс).
	\param idx - номер разделяемого события.
	*/
	virtual int wait_event( int timeout, int idx = 0 );

	//! Отобразить пространство ввода/вывода устройства в адресное пространство процесса
	/*!
	\param timeout - время ожидания (мс).
	\param idx - номер разделяемого события.
	*/
	virtual int map_memory() = 0;

	//! Снять отображение пространства ввода/вывода устройства в адресное пространство процесса
	/*!
	\param timeout - время ожидания (мс).
	\param idx - номер разделяемого события.
	*/
	virtual int unmap_memory() = 0;

        //! Сбросить устройство
        virtual int reset() = 0;
};

#endif //_DEVICE_H_
