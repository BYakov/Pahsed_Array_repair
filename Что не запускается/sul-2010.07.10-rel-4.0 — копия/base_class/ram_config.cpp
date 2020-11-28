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

#ifndef _SUL_CONFIG_H_
    #include "sul_config.h"
#endif

#ifndef _RAM_CONFIG_H_
    #include "ram_config.h"
#endif

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//              Класс для конфигурирования RAM
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

ram::ram(const char *file) : space( file )
{
        //cout << "ram(" << file << ")" << endl;

        tuned_data = new u8[info.zone_size];
        if(!tuned_data) {
                //cout << "Error allocate memory for RAM!" << endl;
        }
}

//------------------------------------------------------------------------------

ram::~ram()
{
        //cout << "~ram()" << endl;
        if(tuned_data)
                delete[] tuned_data;
        tuned_data = NULL;
}

//------------------------------------------------------------------------------

const char *ram::ram_config_file()
{
        return space_config_file();
}

//------------------------------------------------------------------------------

const struct space_info& ram::ram_file_info()
{
        return space_info();
}

//------------------------------------------------------------------------------

const unsigned char *ram::ram_data_block(int zone,int block)
{
        return space_data_block(zone,block);
}

//------------------------------------------------------------------------------

int ram::sul_ram_reconfig(const char *config)
{
        return space_reconfig_memory(config);
}

//------------------------------------------------------------------------------

int ram::sul_ram_set_element(int zone, int block, int offset, u8& data)
{
        return space_set_element(zone,block,offset,data);
}

//------------------------------------------------------------------------------

int ram::sul_ram_get_element(int zone, int block, int offset, u8& data)
{
        return space_get_element(zone,block,offset,data);
}

//------------------------------------------------------------------------------

int ram::sul_ram_fill(int zone, int block, space_fill_type type, u8 pattern)
{
        return space_fill(zone, block, type, pattern);
}

//------------------------------------------------------------------------------

u16 ram::sul_ram_space_crc(int devn)
{
        return space_data_crc(devn);
}

//------------------------------------------------------------------------------

