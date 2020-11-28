#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#ifndef _SERIAL_H_
#include "serial.h"
#endif

using namespace std;

///////////////////////////////////////////////////////////////////////////////

serial::serial(const char *name, int flag) : device(name, flag)
{
        //cout << "serial::serial(" << name << ")" << endl;

        oflag = flag;

        write_timeout = 500;
        read_timeout = 500;

        device_open();

        reset();
}

///////////////////////////////////////////////////////////////////////////////

serial::~serial()
{
        //cout << "~serial()" << endl;

        device_close();
}

///////////////////////////////////////////////////////////////////////////////

int serial::device_open(void)
{
        //cout << "serial::device_open()" << endl;
        /*
        if(!GetCommState(handle(), &dcb)){
        log.msg("Не могу получить настройки порта!");
        return -1;
        }

        dcb.BaudRate = CBR_19200;
        dcb.ByteSize = 8;
        dcb.Parity = NOPARITY;
        dcb.StopBits = ONESTOPBIT;
        dcb.XoffLim = 100;

        if(!SetCommState(handle(), &dcb)) {
        log.msg("Не могу настроить порт!");
        return -1;
        }

        timeout.ReadIntervalTimeout = 10;			// Maximum time between read chars. /
        timeout.ReadTotalTimeoutMultiplier = 10;	// Multiplier of characters.        /
        timeout.ReadTotalTimeoutConstant = 10;		// Constant in milliseconds./
        timeout.WriteTotalTimeoutMultiplier = 10;	// Multiplier of characters.        /
        timeout.WriteTotalTimeoutConstant = 10;	// Constant in milliseconds./

        if(!SetCommTimeouts( handle(), &timeout)) {
        cout << "SetCommTimeouts() error" << endl;
        return -1;
        }
        */
        dcb.DCBlength = sizeof(dcb);

        //dcb.BaudRate = SPEED_57600;    // current baud rate
        dcb.BaudRate = SPEED_115200;    // current baud rate
        //dcb.BaudRate = SPEED_230400;
        //dcb.BaudRate = SPEED_921600;
        //dcb.BaudRate = SPEED_460800;
        dcb.fBinary = 1;              // binary mode, no EOF check
        dcb.fParity = 0;              // enable parity checking
        dcb.fOutxCtsFlow = 0;         // CTS output flow control
        dcb.fOutxDsrFlow = 0;         // DSR output flow control

        //dcb.fDtrControl = DTR_CONTROL_ENABLE;  // DTR flow control type
        dcb.fDtrControl = DTR_CONTROL_DISABLE;  // DTR flow control type
        dcb.fDsrSensitivity = 0;				// DSR sensitivity

        dcb.fTXContinueOnXoff = 0;    // XOFF continues Tx
        dcb.fOutX = 0;                // XON/XOFF out flow control
        dcb.fInX = 0;                 // XON/XOFF in flow control
        dcb.fErrorChar = 0;		   // enable error replacement
        dcb.fNull = 0;				   // enable null stripping
        dcb.fRtsControl = RTS_CONTROL_DISABLE;		// RTS flow control
        //dcb.fRtsControl = RTS_CONTROL_ENABLE;			// RTS flow control
        //dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;		// RTS flow control
        dcb.fAbortOnError = 0;        // abort reads/writes on error

        dcb.XonLim = 0;               // transmit XON threshold
        dcb.XoffLim = 0;              // transmit XOFF threshold
        dcb.ByteSize = 8;             // number of bits/byte, 4-8
        dcb.Parity = NOPARITY;        // 0-4=no,odd,even,mark,space
        dcb.StopBits = ONESTOPBIT;    // 0,1,2 = 1, 1.5, 2
        dcb.XonChar = 0;              // Tx and Rx XON character
        dcb.XoffChar = 0;             // Tx and Rx XOFF character
        dcb.ErrorChar = 0;            // error replacement character

        dcb.EofChar = 0;              // end of input character
        dcb.EvtChar = 0;              // received event character

        int stat = SetCommState( get_handle(), &dcb );
        if(!stat) {
                log.msg("Не могу настроить порт!");
                return -1;
        }

        timeout.ReadIntervalTimeout = 100;		// Maximum time between read chars. /
        timeout.ReadTotalTimeoutMultiplier = 100;	// Multiplier of characters.        /
        timeout.ReadTotalTimeoutConstant = 100;		// Constant in milliseconds./
        timeout.WriteTotalTimeoutMultiplier = 100;	// Multiplier of characters.        /
        timeout.WriteTotalTimeoutConstant = 100;         // Constant in milliseconds./

        if(!SetCommTimeouts( get_handle(), &timeout)) {
                //cout << "SetCommTimeouts() error" << endl;
                return -1;
        }

        if(!SetupComm(get_handle(), 0x1000, 0x1000)) {
        //if(!SetupComm(get_handle(), 0x80, 0x80)) {
            //cout << "SetupComm() error" << endl;
            return -1;
        }

        return 0;
}

///////////////////////////////////////////////////////////////////////////////

int serial::read_data(void *data, int size, int timeout)
{
        //cout << "serial::read_device()" << endl;

        int		stat = 0;
        int		event = 0;
        DWORD		Read = 0;
        OVERLAPPED	ReadOL; //структура для асинхронной записи

        if(oflag & FILE_FLAG_OVERLAPPED) {

                ZeroMemory(&ReadOL,sizeof(ReadOL));
                ReadOL.hEvent = CreateEvent(NULL, true, true, NULL);

                ReadFile( get_handle(), data, size, &Read, &ReadOL );

                event = WaitForSingleObject(ReadOL.hEvent, (timeout ? timeout : read_timeout));

                if( (event == WAIT_OBJECT_0) && (GetOverlappedResult(get_handle(), &ReadOL, &Read, false)) ) {
                        CloseHandle(ReadOL.hEvent);
                        return Read;
                } else {
                        //log.msg(GetLastError());
                        CloseHandle(ReadOL.hEvent);
                        return -1;
                }

        } else {

                stat = ReadFile( get_handle(), data, size, &Read, NULL );
                if(!stat) {
                        //log.msg(GetLastError());
                        return -1;
                }
        }

        //cout << "read_data() " << Read << endl;

        return Read;
}

///////////////////////////////////////////////////////////////////////////////

int serial::write_data(const void *data, int size, int timeout)
{
        //cout << "serial::write_device()" << endl;

        bool	stat = 0;
        int		event = 0;
        DWORD		Write = 0;
        OVERLAPPED	WriteOL; //структура для асинхронной записи

        if(oflag & FILE_FLAG_OVERLAPPED) {

                ZeroMemory(&WriteOL,sizeof(WriteOL));
                WriteOL.hEvent = CreateEvent(NULL, true, true, NULL);

                WriteFile( get_handle(), data, size, &Write, &WriteOL );

                event = WaitForSingleObject(WriteOL.hEvent, (timeout ? timeout : write_timeout));

                if( (event == WAIT_OBJECT_0) && (GetOverlappedResult(get_handle(), &WriteOL, &Write, false)) ) {
                        CloseHandle(WriteOL.hEvent);
                        return Write;
                } else {
                        //log.msg(GetLastError());
                        CloseHandle(WriteOL.hEvent);
                        return -1;
                }

        } else {

                stat = WriteFile( get_handle(), data, size, &Write, NULL );
                if(!stat) {
                        //log.msg(GetLastError());
                        return -1;
                }
        }

        return Write;
}

///////////////////////////////////////////////////////////////////////////////

int serial::device_ctrl(int cmd, void *data)
{
        //cout << "serial::device_ctrl()" << endl;

        switch(cmd) {
                case COM_SET_SPEED: {
                        //set_speed((serial_speed)data);
                                                        } break;
                case COM_GET_SPEED: {
                        *((int*)data) = (int)get_speed();
                                                        } break;
                case COM_GET_DIALOG: {
                        get_dialog();
                                                         } break;
        }
        return 0;
}

///////////////////////////////////////////////////////////////////////////////

int serial::device_close(void)
{
        //cout << "serial::device_close()" << endl;
        return 0;
}

///////////////////////////////////////////////////////////////////////////////

int serial::set_speed(serial_speed speed)
{
        //cout << "serial::set_speed()" << endl;
        return 0;
}

///////////////////////////////////////////////////////////////////////////////

serial_speed serial::get_speed(void)
{
        //cout << "serial::set_speed()" << endl;
        DCB dcb = {0};
        GetCommState(get_handle(),&dcb);
        switch(dcb.BaudRate) {
                                case 57600:
                                        return SPEED_57600;
                                case 115200:
                                        return SPEED_115200;
                                case 921600:
                                        return SPEED_921600;
                                default: return SPEED_UNKNOWN;
        }
}

///////////////////////////////////////////////////////////////////////////////

int serial::get_dialog(void)
{
        //cout << "serial::get_dialog()" << endl;
        config.dwSize = sizeof(config);
        CommConfigDialogA(name(), NULL, &config);
        dcb = config.dcb;
        SetCommState(get_handle(),&dcb);
        return 0;
}

///////////////////////////////////////////////////////////////////////////////

int serial::reset()
{
    if( !FlushFileBuffers(get_handle()) )
        return -1;

    if(!PurgeComm(get_handle(),PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR ))
        return -2;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

int serial::read_raw( void *data, int size, int timeout )
{
    int		stat = 0;
    DWORD	Read = 0;

    stat = ReadFile( get_handle(), data, size, &Read, NULL );
    if(!stat) {
            //log.msg(GetLastError());
            return -1;
    }

    return Read;
}

////////////////////////////////////////////////////////////////////////////////

int serial::write_raw( void *data, int size, int timeout )
{
    bool	stat = 0;
    DWORD	Write = 0;

    stat = WriteFile( get_handle(), data, size, &Write, NULL );
    if(!stat) {
        return -1;
    }

    return Write;
}
