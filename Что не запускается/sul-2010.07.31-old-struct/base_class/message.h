
#ifndef _MESSAGE_H_
#define _MESSAGE_H_




//! ��������� ���������.
/*!
��������� ����� ���������������� � ��������� ��������� ��
������� � ���������.
*/

class message {

private:

	//! ���� ���������� ���������
	bool msg_off;

public:

	//! ����������� ������ ���������
	message();

	//! ���������� ������ ���������
	virtual ~message();

	//! �������� ����� ���������
	void message_on(void) { msg_off = false; }

	//! ��������� ����� ���������
	void message_off(void) { msg_off = true; }

	//! ������� ��������� ��������� �� ������.
	/*!
	\param error - ��� ��������� ������.
	*/
	void msg( int error );

	//! ������� ���������������� ���������.
	/*!
	\param msg_buf - ���������������� ���������.
	*/
        void msg( const char *msg_buf );
};

#endif //_MESSAGE_H_
