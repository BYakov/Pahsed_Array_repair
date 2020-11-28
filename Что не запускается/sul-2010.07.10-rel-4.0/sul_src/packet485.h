#ifndef PACKET485_H
#define PACKET485_H

#ifndef _DEVICE_H_
#include "..\base_class\device.h"
#endif

#ifndef _SUL_MDO_CMD_H_
#include "sul_mdo_cmd.h"
#endif

//!����� ��� ������ � �������� ������ �� ���������� RS485 
class packet485
{
private:

	struct packet       p;    //!< �������������� �����
	device              *hw;  //!< ��������� ��� �������� ������

	packet485();              //!< ����������� ������

	//! ����������� ����� ��������� �����
	void free_packet485();

	//! �������� ����� ��������� ������
	int send_main_packet();

	//! �������� ����� ��������� ������
	int send_dbg_packet();

	//! ��������� ���������� �����
	/*!
	\param buffer - ����� ����������������� ������ ��� ������ ������.
	*/
	int receive_dbg_packet(void *buffer);

        //! ���������� ���������� �������� � �������� �� �������� ���������.
        /*!
        \param h - ��������� ���������� ��������.
        \param h - ��������� �������� �� ��������.
        \param data_crc_flag - �������� ����������� ����� ������, � �� ���������.
        */
        bool headers_ok(struct host_dbg_header *h, struct target_dbg_header *t);

	//! ��������� �������� �� ��������� ������� ���������
	void target_processing_delay(int code);

public:
	packet485(device *dev);    //!< ����������� ������
	virtual ~packet485();               //!< ���������� ������


	/*!
	\param addr - ����� �������� ��� ��������� ������.
	\param cmd - ��� ������� ������.
	\param bn - ����� ����� ������.
	\param *data - ������ ��� ������.
	\param data_size - ������ ����� ������ � ������.
	*/
	void create_packet485( unsigned char addr,
			      unsigned char cmd,
			      unsigned char bn,
			      void *data,
			      unsigned char data_size );

	/*!
	\param addr - ����� �������� ��� ��������� ������.
	\param cmd - ��� ������� ������.
	\param bn - ����� ����� ������.
	\param *data - ������ ��� ������.
	\param data_size - ������ ����� ������ � ������.
	*/
	struct host_dbg_header create_dbg_header(  unsigned char addr,
						    unsigned char cmd,
						    unsigned char bn,
						    void *data,
						    unsigned char data_size );

	//! ����������� ����� ��������� �����
	/*!
	\param x - ���������� X.
	\param y - ���������� Y.
	\param cmd - ��� ������� ������.
	*/
	void create_packet485( unsigned short x = 0,
			       unsigned short y = 0,
			       unsigned char cmd = 0 );

	//! �������� / ��������� ����� ����������� ������
	/*!
	\param addr - ����� �������� ��� ��������� ������.
	\param cmd - ��� ������� ������.
	\param bn - ����� ����� ������.
	\param *data - ������ ��� ������.
	\param data_size - ������ ����� ������ � ������.
	*/
	int request( unsigned char addr,
		unsigned char cmd,
		unsigned char bn,
		void *data,
		unsigned char data_size );


	//! �������� ����� ��������� ������
	/*!
	\param x - ���������� X.
	\param y - ���������� Y.
	\param cmd - ��� ������� ������.
	*/
	int request( unsigned short x = 0,
		unsigned short y = 0,
		unsigned char cmd = 0 );

	//! ������������ ����������� ����� ������ ������
	unsigned char data_crc();

	//! ������������ ����������� ����� ����� ������
	/*!
	\param data - ����� ����� ������.
	\param size - ������ ����� ������.
	*/
	unsigned char data_crc(unsigned char *data, int size);

	//! ������������ ����������� ����� ��������� ������
	unsigned char header_crc();

	//! ������������ ����������� ����� ��������� ������
	/*!
	\param h - ��������� ������������.
	*/
	unsigned char header_crc(struct host_dbg_header *h);

	//! ������������ ����������� ����� ��������� ������
	unsigned char main_crc();

	//! ���������� ����� ��������� ������ ������
	/*!
	\param dev - ��������� �� ������ ������ ����������.
	*/
	void reconnect_device(device *dev);

	//! ���������� ��������� ��������������� ������
	const struct packet get_packet();

	/*!
	\param cmd - ���������� �� ���� ������� ������ ������.
	\param user_size - ������ ������ ������������.
	*/
	unsigned char cmd_to_size( unsigned char cmd,
		unsigned char user_size = 0 );

	/*!
	\param cmd - ���������� �� ���� ������� ��� ���������.
	*/
	trans_type cmd_to_type( unsigned char cmd );

        //! �������� �������� ������ ������ � ��������
        int flush_buffers();
};

#endif // PACKET485_H
