
#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <windows.h>

#ifndef _DEVICE_H_
#include "..\base_class\device.h"
#endif

//!  Класс реализует интерфейс обмена по последовательному каналу COM (serial port)
/*!
Отвечает за обмен информацией по последовательному каналу.
*/

enum serial_speed {

	SPEED_57600 = 57600,
	SPEED_115200 = 115200,
	SPEED_230400 = 2304000,        
	SPEED_460800 = 460800,
	SPEED_921600 = 921600,
	SPEED_UNKNOWN = 0,
};

class serial: public device 
{

private:
	serial();

	DCB		dcb;
	COMMTIMEOUTS	timeout;
	COMMCONFIG	config;
	int		oflag;
	int		read_timeout;
	int		write_timeout;

	int set_speed(serial_speed speed);
	serial_speed get_speed();
	int get_dialog(void);
	int device_ctrl(int cmd, void *data);
	int device_close();
	int device_open();

public:
	serial(const char *name, int flag = 0);
	virtual ~serial();

	int read_data(void *data, int size, int timeout=0);
	int write_data(const void *data, int size, int timeout=0);
	int read_raw( void *data, int size, int timeout=0 );
	int write_raw( void *data, int size, int timeout=0 );
	int read_register(unsigned reg, unsigned long &val, int timeout=0){return -error_not_implemented;}
	int write_register(unsigned reg, unsigned long &val, int timeout=0){return -error_not_implemented;}
	int read_memory(unsigned mem, unsigned long &val, int timeout=0){return -error_not_implemented;}
	int write_memory(unsigned mem, unsigned long &val, int timeout=0){return -error_not_implemented;}
	int read_config(unsigned offset, unsigned long &val, int timeout=0){return -error_not_implemented;}
	int write_config(unsigned offset, unsigned long &val, int timeout=0){return -error_not_implemented;}
	int register_event( char *name, int idx=0 ){return -error_not_implemented;}
	int wait_event( int timeout, int idx=0 ){return -error_not_implemented;}
	int map_memory(){return -error_not_implemented;}
	int unmap_memory(){return -error_not_implemented;}
        int reset();
};

//
// Команды управления устройствами
//

enum serial_cmd {
	COM_SET_SPEED = 0,
	COM_GET_SPEED = 1,
	COM_GET_DIALOG = 2,
};

#endif //_SERIAL_H_
