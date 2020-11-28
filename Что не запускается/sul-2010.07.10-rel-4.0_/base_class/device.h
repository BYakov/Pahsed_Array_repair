
#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifndef _MESSAGE_H_
#include "message.h"
#endif

#include <windows.h>
#include <winioctl.h>

//-----------------------------------------------------------------------------
//! ��������� ����� ������
enum error_code {
	status_ok				= 0x0,	//<! ������ ���
	error_device_handle		= 0x1,	//<! ������ �������� ����� ����������
	error_event_handle		= 0x2,	//<! ������ �������� �������
	error_wait_timeout		= 0x3,	//<! ������� �������� �������
	error_ioctl_request		= 0x4,	//<! ������ ��������� � �������� ����������
	error_event_busy		= 0x5,	//<! ������� ��� ������������
	error_event_index		= 0x6,	//<! ������������ ������ ������� 
	error_not_implemented	= 0x7,	//<! ������� �� �����������
};

//! ���������� ������� ������� ����� ������� ���������������� ���������.
#define		EVENT_NUMBER	8

//! ��������� ����������.
/*!
������������� ����������� ��������� � ����������� �����-������.
*/

class device 
{

private:

	//! ����������� ������ �� ���������.
	device();

	//! ��� ����������
	char *dev_name;

	//! ���������� ����� ����������
	void *fd;

	//! ����������� �������
	void *event[EVENT_NUMBER];

	bool opened;
	bool mapped;

protected:

	//! ����� ��������������� ���������
	message log;
	//! ��������� ���������� �������
	bool is_event(int idx=0);
	//! ������� ����������� �������
	bool create_event(const char *name, int idx = 0);
	//! ���������� ���������� ����������
	void *get_handle() { return fd; }
	//! ���������� ��� ����������
	const char *name() { return dev_name; }
	//! ���������� ���������� �������
	void *get_event(int idx=0) { return (idx < EVENT_NUMBER ? event[idx] : NULL); }

public:

	//! ����������� ������ ����������.
	/*!
	\param name ��� ����������.
	\param flags - �������������� ����� �������� ����������.
	*/
	device(const char *name, int flags = 0);

	//! ���������� ������ ����������.
	virtual ~device();

	//! ��������� ������� ���������� ��� ���
	bool is_open();

	//! ������ ������ �� ���������� ("�����").
	/*!
	\param data - ��������� �� ���������������� ����� �������� size.
	\param size - ���������� ���� ��� ������ �� ����������.
	\param timeout - ������� ��������.
	*/
	virtual int read_raw(void *data, int size, int timeout=0);

	//! ������ ������ � ���������� ("�����").
	/*!
	\param data - ��������� �� ���������������� ����� �������� size.
	\param size - ���������� ���� ��� ������ � ����������.
	\param timeout - ������� ��������.
	*/
	virtual int write_raw(void *data, int size, int timeout=0);

	//! ������ �� ����������.
	/*!
	\param data - ��������� �� ���������������� ����� �������� size.
	\param size - ���������� ���� ��� ������ �� ����������.
	\param timeout - ������� ��������.
	*/
	virtual int read_data(void *data, int size, int timeout=0) = 0;

	//! ������ ������ � ����������.
	/*!
	\param data - ��������� �� ���������������� ����� �������� size.
	\param size - ���������� ���� ��� ������ � ����������.
	\param timeout - ������� ��������.
	*/
	virtual int write_data(const void *data, int size, int timeout=0) = 0;

	//! ������ �������� ����������.
	/*!
	\param reg - ��������� �� ���������������� ����� �������� size.
	\param val - ����������� �������� ��������.
	\param timeout - ������� ��������.
	*/
	virtual int read_register(unsigned reg, unsigned long &val, int timeout=0) = 0;

	//! ������ �������� ����������.
	/*!
	\param reg - ��������� �� ���������������� ����� �������� size.
	\param val - ������������ �������� ��������.
	\param timeout - ������� ��������.
	*/
	virtual int write_register(unsigned reg, unsigned long &val, int timeout=0) = 0;

	//! ������ ������ �� ����������.
	/*!
	\param mem - ����� ������ ������.
	\param val - ����������� �������� �� ������.
	\param timeout - ������� ��������.
	*/
	virtual int read_memory(unsigned mem, unsigned long &val, int timeout=0) = 0;

	//! ������ � ������ ����������.
	/*!
	\param mem - ��������� �� ���������������� ����� �������� size.
	\param val - ������������ � ������ ��������.
	\param timeout - ������� ��������.
	*/
	virtual int write_memory(unsigned mem, unsigned long &val, int timeout=0) = 0;

	//! ������ �������� ����������������� ������������ ����������.
	/*!
	\param offset - �������� �������� � ���������������� ������������.
	\param val - ����������� ��������.
	\param timeout - ������� ��������.
	*/
	virtual int read_config(unsigned offset, unsigned long &val, int timeout=0) = 0;

	//! ������ �������� ����������������� ������������ ����������.
	/*!
	\param offset - �������� �������� � ���������������� ������������.
	\param val - ������������ ��������.
	\param timeout - ������� ��������.
	*/
	virtual int write_config(unsigned offset, unsigned long &val, int timeout=0) = 0;

	//! ���������������� ���������� ������� �����/������ ����������
	/*!
	\param name - ��� ������������ �������.
	\param idx - ����� ������������ �������.
	*/
	virtual int register_event( char *name, int idx = 0 ) = 0;

	//! ������� ������� �����/������ ����������
	/*!
	\param timeout - ����� �������� (��).
	\param idx - ����� ������������ �������.
	*/
	virtual int wait_event( int timeout, int idx = 0 );

	//! ���������� ������������ �����/������ ���������� � �������� ������������ ��������
	/*!
	\param timeout - ����� �������� (��).
	\param idx - ����� ������������ �������.
	*/
	virtual int map_memory() = 0;

	//! ����� ����������� ������������ �����/������ ���������� � �������� ������������ ��������
	/*!
	\param timeout - ����� �������� (��).
	\param idx - ����� ������������ �������.
	*/
	virtual int unmap_memory() = 0;

        //! �������� ����������
        virtual int reset() = 0;
};

#endif //_DEVICE_H_
