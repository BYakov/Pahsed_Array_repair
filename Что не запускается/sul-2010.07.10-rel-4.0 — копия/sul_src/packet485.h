#ifndef PACKET485_H
#define PACKET485_H

#ifndef _DEVICE_H_
#include "..\base_class\device.h"
#endif

#ifndef _SUL_MDO_CMD_H_
#include "sul_mdo_cmd.h"
#endif

//!Класс для работы с пакетами данных по интерфейсу RS485 
class packet485
{
private:

	struct packet       p;    //!< Сформированный пакет
	device              *hw;  //!< Интерфейс для передачи пакета

	packet485();              //!< Конструктор класса

	//! Освобождает ранее созданный пакет
	void free_packet485();

	//! Передает пакет основного режима
	int send_main_packet();

	//! Передает пакет основного режима
	int send_dbg_packet();

	//! Принимает отладочный пакет
	/*!
	\param buffer - адрес пользовательского буфера для приема данных.
	*/
	int receive_dbg_packet(void *buffer);

        //! Сравнивает переданный абоненту и принятый от абонента заголовок.
        /*!
        \param h - заголовок переданный абоненту.
        \param h - заголовок принятый от абонента.
        \param data_crc_flag - проверят контрольную сумму данных, а не заголовка.
        */
        bool headers_ok(struct host_dbg_header *h, struct target_dbg_header *t);

	//! Формирует задержку на обработку команды абонентом
	void target_processing_delay(int code);

public:
	packet485(device *dev);    //!< Конструктор класса
	virtual ~packet485();               //!< Деструктор класса


	/*!
	\param addr - адрес абонента для получения пакета.
	\param cmd - код команды пакета.
	\param bn - номер блока данных.
	\param *data - данные для пакета.
	\param data_size - размер блока данных в пакете.
	*/
	void create_packet485( unsigned char addr,
			      unsigned char cmd,
			      unsigned char bn,
			      void *data,
			      unsigned char data_size );

	/*!
	\param addr - адрес абонента для получения пакета.
	\param cmd - код команды пакета.
	\param bn - номер блока данных.
	\param *data - данные для пакета.
	\param data_size - размер блока данных в пакете.
	*/
	struct host_dbg_header create_dbg_header(  unsigned char addr,
						    unsigned char cmd,
						    unsigned char bn,
						    void *data,
						    unsigned char data_size );

	//! Освобождает ранее созданный пакет
	/*!
	\param x - координата X.
	\param y - координата Y.
	\param cmd - код команды пакета.
	*/
	void create_packet485( unsigned short x = 0,
			       unsigned short y = 0,
			       unsigned char cmd = 0 );

	//! Передает / принимает пакет отладочного режима
	/*!
	\param addr - адрес абонента для получения пакета.
	\param cmd - код команды пакета.
	\param bn - номер блока данных.
	\param *data - данные для пакета.
	\param data_size - размер блока данных в пакете.
	*/
	int request( unsigned char addr,
		unsigned char cmd,
		unsigned char bn,
		void *data,
		unsigned char data_size );


	//! Передает пакет основного режима
	/*!
	\param x - координата X.
	\param y - координата Y.
	\param cmd - код команды пакета.
	*/
	int request( unsigned short x = 0,
		unsigned short y = 0,
		unsigned char cmd = 0 );

	//! Подсчитывает контрольную сумму данных пакета
	unsigned char data_crc();

	//! Подсчитывает контрольную сумму блока данных
	/*!
	\param data - адрес блока данных.
	\param size - размер блока данных.
	*/
	unsigned char data_crc(unsigned char *data, int size);

	//! Подсчитывает контрольную сумму заголовка пакета
	unsigned char header_crc();

	//! Подсчитывает контрольную сумму заголовка пакета
	/*!
	\param h - заголовок пользователя.
	*/
	unsigned char header_crc(struct host_dbg_header *h);

	//! Подсчитывает контрольную сумму основного пакета
	unsigned char main_crc();

	//! Подключает новый интерфейс канала обмена
	/*!
	\param dev - указатель на объект класса интерфейса.
	*/
	void reconnect_device(device *dev);

	//! Возвращает структуру сформированного пакета
	const struct packet get_packet();

	/*!
	\param cmd - определяет по коду команды размер данных.
	\param user_size - размер данных пользователя.
	*/
	unsigned char cmd_to_size( unsigned char cmd,
		unsigned char user_size = 0 );

	/*!
	\param cmd - определяет по коду команды тип тразакции.
	*/
	trans_type cmd_to_type( unsigned char cmd );

        //! Сбросить файловые буферы приема и передачи
        int flush_buffers();
};

#endif // PACKET485_H
