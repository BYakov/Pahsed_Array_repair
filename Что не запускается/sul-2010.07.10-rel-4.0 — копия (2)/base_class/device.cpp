
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

#ifndef _DEVICE_H_
#include "device.h"
#endif

using namespace std;

//
// Конструктор (открытие устройства)
//
device::device(const char *name, int flag)
{
        //cout << "device::device(" << name << ")" << endl;

        dev_name = new char[strlen(name)+1];
        if(!dev_name) {
                log.msg(GetLastError());
                return;
        }

        //strncpy(dev_name,name,strlen(name));
        strcpy(dev_name,name);

        for(int i=0; i<EVENT_NUMBER; i++)
                event[i] = NULL;

        opened = false;
        mapped = false;

        fd = CreateFileA(
                dev_name,
                GENERIC_WRITE|GENERIC_READ,
                0,
                NULL,
                OPEN_EXISTING,
                flag,
                NULL);

        if (fd == INVALID_HANDLE_VALUE) {// Тут жопа какая то
                fd = NULL;
                log.msg( GetLastError() );
                delete[] dev_name;
                dev_name = NULL;
                return;
        }

        opened = true;
}

//
// Деструктор (закрытие устройства)
//
device::~device()
{
        //cout << "device::~device()" << endl;

        if(mapped) {
                log.msg("Ошибка! Отображение памяти активно, при удалениии объекта!");
        }
        for(int i=0; i<EVENT_NUMBER; i++) {
                if(event[i]) {
                        CloseHandle(event[i]);
                        event[i] = NULL;
                }
        }
        if(fd) {
                CloseHandle(fd);
                fd = NULL;
                opened = false;
        }
        if(dev_name) {
                delete[] dev_name;
                dev_name = NULL;
        }
}

//
// Проверяет дескриптор устройства
//
bool device::is_open()
{
        return opened;
}

//
// Создает дескриптор события
//
bool device::create_event(const char *name, int idx)
{
        if(idx > EVENT_NUMBER)
                return false;

        if( event[idx] != NULL )
                return false;

        event[idx] = CreateEventA( NULL, TRUE, FALSE, name );
        if(!event[idx])
                return false;
        else
                return true;
}

int device::wait_event( int timeout, int idx )
{
        if(idx > EVENT_NUMBER)
                return error_event_index;

        if( !event[idx] )
                return error_event_handle;

        int status = WaitForSingleObject( get_event(idx), timeout );
        if( status == WAIT_TIMEOUT ) {
                return error_wait_timeout;
        }
        return status_ok;
}

int device::read_raw( void *data, int size, int timeout )
{
    return -1;
}

int device::write_raw( void *data, int size, int timeout )
{
    return -1;
}
