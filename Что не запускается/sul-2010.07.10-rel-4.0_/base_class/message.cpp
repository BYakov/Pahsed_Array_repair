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

using namespace std;

#ifndef _MESSAGE_H_
#include "message.h"
#endif

/////////////////////////////////////////////////////////////////////

message::message()
{
        //cout << "message::message()" << endl;
        msg_off = false;
}

/////////////////////////////////////////////////////////////////////

message::~message()
{
        //cout << "message::~message()" << endl;
}

/////////////////////////////////////////////////////////////////////

//
// Выдает системное сообщение о последней ошибке...
//
void message::msg( int error )
{
        void* lpMsgBuf;

        if( msg_off )
                return;

        FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                error,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (char*) &lpMsgBuf,
                0,
                NULL
                );

        // Process any inserts in lpMsgBuf.
        //
        // Display the string.
        MessageBoxA( NULL, (char*)lpMsgBuf, "Message...", MB_OK | MB_ICONINFORMATION );
        // Free the buffer.
        LocalFree( lpMsgBuf );
        return;
}

//////////////////////////////////////////
// Выдает диагностическое сообщение
//////////////////////////////////////////
void message::msg( const char *msg_buf )
{
        if( msg_off )
                return;

        // Display the string.
        MessageBoxA( NULL, msg_buf, "Message...", MB_OK | MB_ICONINFORMATION );

        return;
}
