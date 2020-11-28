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

#ifndef _FLASH_CONFIG_H_
    #include "flash_config.h"
#endif

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//              Класс для конфигурирования FLASH
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

flash::flash(const char *file, int modules, int channels) : space( file, modules, channels )
{
        //cout << "flash(" << file << ")" << endl;
}

//------------------------------------------------------------------------------

flash::~flash()
{
        //cout << "~flash()" << endl;
}

//------------------------------------------------------------------------------

const char *flash::flash_config_file()
{
        return space_config_file();
}

//------------------------------------------------------------------------------

const struct space_info& flash::flash_file_info()
{
        return space_info();
}

//------------------------------------------------------------------------------

const unsigned char *flash::flash_data_block(int zone,int block)
{
        return space_data_block(zone,block);
}

//------------------------------------------------------------------------------

int flash::sul_flash_reconfig(const char *config)
{
        return space_reconfig_memory(config);
}

//------------------------------------------------------------------------------

int flash::sul_flash_set_element(int zone, int block, int offset, u8& data)
{
        return space_set_element(zone,block,offset,data);
}

//------------------------------------------------------------------------------

int flash::sul_flash_get_element(int zone, int block, int offset, u8& data)
{
        return space_get_element(zone,block,offset,data);
}

//------------------------------------------------------------------------------

int flash::sul_flash_fill(int zone, int block, space_fill_type type, u8 pattern)
{
        return space_fill(zone, block, type, pattern);
}

//------------------------------------------------------------------------------

u16 flash::sul_flash_space_crc(int devn)
{
        return space_data_crc(devn);
}
