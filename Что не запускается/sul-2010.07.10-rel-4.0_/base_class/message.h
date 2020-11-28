
#ifndef _MESSAGE_H_
#define _MESSAGE_H_




//! Интерфейс сообщений.
/*!
Реализует вывод пользовательских и системных сообщений об
ошибках в программе.
*/

class message {

private:

	//! Флаг разрешения сообщений
	bool msg_off;

public:

	//! Конструктор класса сообщений
	message();

	//! Деструктор класса сообщений
	virtual ~message();

	//! Включить вывод сообщений
	void message_on(void) { msg_off = false; }

	//! Отключить вывод сообщений
	void message_off(void) { msg_off = true; }

	//! Выводит системное сообщение об ошибке.
	/*!
	\param error - код системной ошибки.
	*/
	void msg( int error );

	//! Выводит пользовательское сообщение.
	/*!
	\param msg_buf - пользовательское сообщение.
	*/
        void msg( const char *msg_buf );
};

#endif //_MESSAGE_H_
