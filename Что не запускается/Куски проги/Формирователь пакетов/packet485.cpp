#include <windows.h>
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#ifndef PACKET485_H
#include "packet485.h"
#endif

using namespace std;

///////////////////////////////////////////////////////////////////////////////

packet485::packet485(device *dev)
{
        p.length = 0;
        p.paddr = NULL;
        hw = dev;
        hw->reset();
}

///////////////////////////////////////////////////////////////////////////////

packet485::~packet485()
{
        free_packet485();
}

///////////////////////////////////////////////////////////////////////////////

unsigned char packet485::data_crc()
{
        unsigned char dcrc = 0;
        struct host_dbg_header *h = (struct host_dbg_header *)p.paddr;

        if(h->size == 0)
                return 0;

        unsigned char *data_addr = (unsigned char *)(p.paddr + sizeof(struct host_dbg_header));

        for(unsigned i=0; i < (unsigned)h->size; i++)
        {
                dcrc += data_addr[i];
        }

        return dcrc;
}

///////////////////////////////////////////////////////////////////////////////

unsigned char packet485::data_crc(unsigned char *data, int size)
{
        unsigned char dcrc = 0;

        if(size == 0) return 0;

        for(int i=0; i < size; i++)
        {
                dcrc += data[i];
        }

        return dcrc;
}

///////////////////////////////////////////////////////////////////////////////

unsigned char packet485::header_crc()
{
        unsigned char hcrc = 0;
        unsigned char *ptr = p.paddr;

        for(unsigned i=0; i<sizeof(struct host_dbg_header)-1; i++)
        {
                hcrc += ptr[i];
        }

        return hcrc;
}

///////////////////////////////////////////////////////////////////////////////

unsigned char packet485::header_crc(struct host_dbg_header *h)
{
        unsigned char hcrc = 0;
        unsigned char *ptr = (unsigned char*)h;

        for(unsigned i=0; i<sizeof(struct host_dbg_header)-1; i++)
        {
                hcrc += ptr[i];
        }

        return hcrc;
}

///////////////////////////////////////////////////////////////////////////////

unsigned char packet485::main_crc()
{
        unsigned char mcrc = 0;
        unsigned char *ptr = p.paddr;

        for(unsigned i=0; i<sizeof(struct main_packet)-1; i++)
        {
                mcrc += ptr[i];
        }

        return mcrc;
}

///////////////////////////////////////////////////////////////////////////////

unsigned char packet485::cmd_to_size( unsigned char cmd, unsigned char user_size )
{
        unsigned char size = 0;

        switch (cmd) {
                case host_eeprom_data: { size = 128; } break;
                case host_ram_data: { size = 128; } break;
                case host_scale: { size = 3; } break;
                case target_scale_return: { size = 3; } break; //должен быть один байт. 2 для отладки записи в ПЛИС
                case target_eeprom_clear: { size = 2; } break;
                case target_ram_clear: { size = 1; } break;
                case target_eeprom_to_plm: { size = 0; } break;
                case target_ram_to_plm: { size = 0; } break;
                case target_eeprom_data: { size = 128; } break;
                case target_ram_data: { size = 128; } break;
                case target_eeprom_crc: { size = 2; } break;
                case target_ram_crc: { size = 2; } break;
                case target_ctrl_impulse: { size = 0; } break;
                case target_impulse_return: { size = 128; } break;
                case target_ctrl_channel: { size = 0; } break;
                case target_channel_return: { size = 128; } break;
                case target_ctrl_calc: { size = 0; } break;
                case target_calc_return: { size = 128; } break;
                //case host_to_target: { size = user_size; } break;
                //case target_to_host: { size = user_size; } break;
                case host_to_target: { size = 128; } break;
                case target_to_host: { size = 128; } break;
                case target_address: { size = 1; } break;
        }

        return size;
}

///////////////////////////////////////////////////////////////////////////////

trans_type packet485::cmd_to_type( unsigned char cmd )
{
        trans_type type = to_empty;

        switch (cmd) {
                case host_to_target:
                case host_eeprom_data:
                case host_ram_data:
                case host_scale:
                        type = to_target;
                        break;
                case target_eeprom_data:
                case target_ram_data:
                case target_eeprom_crc:
                case target_ram_crc:
                case target_impulse_return:
                case target_channel_return:
                case target_calc_return:
                case target_to_host:
                case target_address:
                case target_scale_return:
                        type = to_host;
                        break;
                case target_eeprom_to_plm:
                case target_ram_to_plm:
                case target_eeprom_clear:
                case target_ram_clear:
                case target_ctrl_impulse:
                case target_ctrl_channel:
                case target_ctrl_calc:
                case target_reset:
                        type = to_target_cmd;
                        break;

        }

        return type;
}

///////////////////////////////////////////////////////////////////////////////

void packet485::create_packet485(  unsigned char addr,
                                   unsigned char cmd,
                                   unsigned char bn,
                                   void *data,
                                   unsigned char data_size )
{
        free_packet485();

        //вычислим размер нового пакета
        p.length = sizeof(struct host_dbg_header) + data_size;

        //выделим новый блок данных
        p.paddr = (unsigned char*)malloc(p.length);
        if(!p.paddr) {
                p.length = 0;
        }
        memset(p.paddr, 0, p.length);

        struct host_dbg_header *h = (struct host_dbg_header *)p.paddr;

        //скопируем блок данных пользователя в новый пакет
        if(data)
                memcpy(p.paddr + sizeof(struct host_dbg_header), data, data_size);

        //заполним служебные поля нового пакета
        h->sign = host_signature;
        h->addr = addr;
        h->code = cmd;
        h->size = data_size;

        //контрольная сумма данных пакета
        h->dcrc = data_crc();

        h->bnum = bn;
        h->txrx = cmd_to_type( h->code );

        //контрольная сумма заголовка пакета
        h->hcrc = header_crc();
}

///////////////////////////////////////////////////////////////////////////////

struct host_dbg_header packet485::create_dbg_header(  unsigned char addr,
                                                      unsigned char cmd,
                                                      unsigned char bn,
                                                      void *data,
                                                      unsigned char data_size )
{
        struct host_dbg_header h = {0};

        //скопируем блок данных пользователя в новый пакет
        if(data) {
            //контрольная сумма данных пакета
            h.dcrc = data_crc((unsigned char*)data, data_size);
        }

        //заполним служебные поля нового пакета
        h.sign = host_signature;
        h.addr = addr;
        h.code = cmd;
        h.size = data_size;

        h.bnum = bn;
        h.txrx = cmd_to_type( h.code );

        //контрольная сумма заголовка пакета
        h.hcrc = header_crc(&h);

        return h;
}

///////////////////////////////////////////////////////////////////////////////

void packet485::create_packet485( unsigned short x, unsigned short y, unsigned char cmd )
{
        free_packet485();

        //вычислим размер нового пакета
        p.length = sizeof(struct main_packet);

        //выделим новый блок данных
        p.paddr = (unsigned char*)malloc(p.length);
        if(!p.paddr) {
                p.length = 0;
        }
        memset(p.paddr,0,p.length);

        struct main_packet *mpacket = (struct main_packet *)p.paddr;

        //заполним служебные поля нового пакета
        mpacket->mhdr.sign = host_signature;
        unsigned char x0 = (x & 0xff);
        unsigned char x1 = ((x >> 8) & 0xff);
        mpacket->mdata.x = x1 | (x0 << 8);
        unsigned char y0 = (y & 0xff);
        unsigned char y1 = ((y >> 8) & 0xff);
        mpacket->mdata.y = y1 | (y0 << 8);
        mpacket->mdata.cmd = cmd;

        //контрольная сумма пакета
        mpacket->mtail.mcrc = main_crc();
}

///////////////////////////////////////////////////////////////////////////////

void packet485::free_packet485( )
{
        // освободим структуру пакета
        if(p.paddr) {
                free(p.paddr);
                p.length = 0;
                p.paddr = NULL;
        }
}

///////////////////////////////////////////////////////////////////////////////

int packet485::send_main_packet( )
{
        if(!hw) return -1;

        unsigned res = hw->write_data(p.paddr,p.length);
        if(res != p.length)
                return -1;

        return 0;
}

//-----------------------------------------------------------------------------

bool packet485::headers_ok(struct host_dbg_header *h, struct target_dbg_header *t)
{
    if(t->sign != target_signature)
        return false;

    //if(t->crc != h->dcrc)
        //return false;

    if(t->addr != h->addr)
        return false;

    if(t->code != h->code)
        return false;

    return true;
}

//-----------------------------------------------------------------------------

int packet485::send_dbg_packet()
{
    struct host_dbg_header *h = (struct host_dbg_header*)p.paddr;
    struct target_dbg_header t = {0};
    int res = -1;

    if(!hw) return -1;
    if(!h) return -1;

    // посылаем командный заголовок
    res = hw->write_data(p.paddr,sizeof(struct host_dbg_header));
    if(res != sizeof(struct host_dbg_header)) {
        //cout << "send_dbg_packet(): Error send host header" << endl;
        return -1;
    }

    Sleep(30);

    // передаем данные
    res = hw->write_data(p.paddr+sizeof(struct host_dbg_header),h->size);
    if(res != h->size) {
        //cout << "send_dbg_packet(): Error send host data" << endl;
        return -1;
    }

    target_processing_delay(h->code);

    // принимаем подтверждение
    res = hw->read_data(&t,sizeof(struct target_dbg_header));
    if(res != sizeof(struct target_dbg_header)) {
        //cout << "send_dbg_packet(): Error receive target header" << endl;
        return -1;
    }

    if(!headers_ok(h,&t)) {
        //cout << "send_dbg_packet(): Error compare headers" << endl;
        return -1;
    }

    return h->size;
}

///////////////////////////////////////////////////////////////////////////////

void packet485::target_processing_delay(int code)
{
    switch(code) {
        case host_eeprom_data: Sleep(1800); break;
        case host_scale: Sleep(100); break;
        case target_ctrl_channel: Sleep(1000); break;
        case target_eeprom_clear: Sleep(15000); break;
        case target_eeprom_crc : Sleep(20); break;
        default: Sleep(5);
    }
}

int packet485::receive_dbg_packet(void *buffer)
{
    struct host_dbg_header *h = (struct host_dbg_header*)p.paddr;
    int res = -1;

    if(!hw) return -1;
    if(!h) return -1;

    // посылаем командный заголовок
    res = hw->write_data(p.paddr,sizeof(struct host_dbg_header));
    if(res != sizeof(struct host_dbg_header))
        return -1;

    target_processing_delay(h->code);

    // считываем данные
    res = hw->read_data(buffer,h->size);
    if(res != h->size)
        return -1;

    return res;
}

///////////////////////////////////////////////////////////////////////////////

int packet485::request( unsigned char addr,
                                           unsigned char cmd,
                                           unsigned char bn,
                                           void *data,
                                           unsigned char data_size )
{
        unsigned char res = 0;

        create_packet485( addr, cmd, bn, data, data_size );

        trans_type type = cmd_to_type(cmd);

        flush_buffers();

        switch(type) {
                                case to_host:
                                        {
                                                res = receive_dbg_packet(data);
                                        }
                                        break;
                                case to_target:
                                        {
                                                res = send_dbg_packet();
                                        }
                                        break;
                                case to_target_cmd:
                                        {
                                                res = send_dbg_packet();
                                        }
                break;
                                default :
                                        {
                                                return -1;
                                        }
        }

        if(res != data_size)
                return -1;
        else
                return 0;
}

//------------------------------------------------------------------------------

int packet485::request( unsigned short x, unsigned short y, unsigned char cmd )
{
        create_packet485( x, y, cmd );
        return send_main_packet();
}

//------------------------------------------------------------------------------

void packet485::reconnect_device(device *dev)
{
        if(dev) hw = dev;
}

//------------------------------------------------------------------------------

const struct packet packet485::get_packet()
{
        return p;
}

//------------------------------------------------------------------------------

int packet485::flush_buffers()
{
    return hw->reset();
    //return 0;
}
