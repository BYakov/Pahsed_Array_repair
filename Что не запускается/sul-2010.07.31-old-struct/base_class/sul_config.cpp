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

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//         Базовый класс для работы с конфигшурационным пространством
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

space::space(const char *name, int modules, int channels)
{
        //cout << "space::space( " << name << " )" << endl;

        user_block = NULL;
        space_data = NULL;
        configured = false;

        memset(&info,0,sizeof(info));

        file_name = new char[strlen(name)+1];
        if(!file_name) {
                log.msg(GetLastError());
                return;
        }

        strcpy(file_name,name);

        if( space_create_memory(modules, channels) < 0 ) {
                configured = false;
        } else {

                if( space_fill_memory() < 0 ) {
                        configured = false;
                } else {
                        configured = true;
                }
        }
}

//------------------------------------------------------------------------------

space::~space()
{
        //cout << "space::~space()" << endl;

        if(user_block) delete [] user_block;
        if(space_data) delete [] space_data;
        if(file_name) delete[] file_name;

        user_block = NULL;
        space_data = NULL;
        file_name  = NULL;
}

//------------------------------------------------------------------------------

int space::space_set_element(int zone, int block, int offset, u8& data)
{
        if(!space_data)
                return -1;
        int off = zone * info.zone_size + block * info.block_size + offset;
        if(off > info.total_size)
                return -1;

        space_data[off] = data;

        return 0;
}

//------------------------------------------------------------------------------

int space::space_get_element(int zone, int block, int offset, u8& data)
{
        if(!space_data)
                return -1;
        int off = zone * info.zone_size + block * info.block_size + offset;
        if(off > info.total_size)
                return -1;

        data = space_data[off];

        return 0;
}

//------------------------------------------------------------------------------

int space::space_clear_zone(int zone)
{
        if(!space_data)
                return -1;

        int offset = zone * info.zone_size;
        int size = info.zone_size;

        if((offset + size) > info.total_size)
                return -1;

        memset((space_data+offset),0,size);

        return 0;
}

//------------------------------------------------------------------------------

int space::space_autodetect_params(int modules, int channels)
{
        //cout << "space::space_detect_params( " << modules << ", " << channels << " )" << endl;

        fstream  ifs;
        string   str;

        ifs.open( file_name );
        if (!ifs.is_open()) {
                //cout << "Error open " << file_name << endl;
                log.msg( GetLastError() );
                return -1;
        }

        int zone = 0;
        int zsize = 0;
        int bnum = 0;
        int bsize = 0;
        int total = 0;

        while (!ifs.eof()) {

                getline( ifs, str );

                if(strstr(str.c_str(),"LINES")) break;

                if(!str.length()) {

                        if(zone && !bsize && total) {

                                bnum++;
                                bsize = total;
                                //cout << "bsize = " << bsize << endl;
                        }

                        continue;
                }

                int p = 0;
                if(str.at(0) == ' ') {
                        p = str.find_first_not_of(" ",0);
                }

                if(p < 0)
                        continue;

                if( (str.at(p) == ';')||(str.at(p) == '\n') ) {
                        continue;
                }

                if( str.at(p) == '[' ) {

                        zone++;

                        if( (zone > 1) && !zsize ) {
                                zsize = total;
                        }

                        continue;
                }

                int start = 0;
                int stop = 0;
                unsigned idx = 0;

                do {
                        start = str.find_first_not_of(" ", stop);
                        stop = str.find_first_of(" ", start);

                        if(start == -1)
                                break;

                        string s = str.substr(start,stop - start);
                        //cout << s.c_str() << " ";

                        total++;
                        idx++;

                } while ( idx < str.length() );

                cout << endl;

                if(bsize) {
                        if((total%bsize) == 0) {
                                bnum++;
                        }
                }
        }

        if(zone == 1) {
            zsize = total;
        }

        info.zones = zone;
        info.zone_size = zsize;

        if(!info.zone_size) {
            //cout << "Empty file!" << endl;
            return -1;
        }

        info.blocks = bnum;
        info.block_size = bsize;

        if(info.zones == 1) {
            info.blocks_in_zone = bnum;
        }

        //cout << "zones = " << info.zones << endl;
        //cout << "zone_size = " << info.zone_size << endl;
        //cout << "blocks = " << info.blocks << endl;
        //cout << "block_size = " << info.block_size << endl;

        info.total_size = info.zone_size*info.zones;
        info.total_blocks = (info.total_size/info.block_size);
        info.blocks_in_zone = (info.zone_size / info.block_size);
        info.channels = info.block_size;

        //cout << "total_size = " << info.total_size << endl;
        //cout << "total_blocks = " << info.total_blocks << endl;
        //cout << "blocks_in_zone = " << info.blocks_in_zone << endl;
        //cout << "channels = " << info.channels << endl;

        ifs.close();

        return 0;
}

//------------------------------------------------------------------------------

int space::space_create_memory(int modules, int channels)
{
        //cout << "space::space_create_memory()" << endl;

        if(space_data) delete[] space_data;
        if(user_block) delete[] user_block;

        memset(&info,0,sizeof(info));

        space_autodetect_params(modules, channels);

        if(!info.total_size) {
                return -1;
        }

        space_data = new u8[info.total_size];
        if(!space_data) {
                return -1;
        }
        memset(space_data,0,info.total_size);

        user_block = new u8[info.block_size];
        if(!user_block) {
                return -1;
        }
        memset(user_block,0,info.block_size);

        return 0;
}

//------------------------------------------------------------------------------

int space::space_fill_memory(void)
{
        //cout << "space::space_fill_memory()" << endl;

        fstream  ifs;
        string   str;

        ifs.open( file_name, ios::in );
        if (!ifs.is_open()) {
                log.msg( GetLastError() );
                return -2;
        }

        int total = 0;
        int current_zone = 0;
        int current_block = 0;

        while (!ifs.eof()) {

                getline( ifs, str );

                if(strstr(str.c_str(),"LINES")) break;

                if(!str.length()) {
                        continue;
                }


                int p = 0;
                if(str.at(0) == ' ') {
                        p = str.find_first_not_of(" ",0);
                }

                if(p < 0)
                        continue;

                if( (str.at(p) == ';')||(str.at(p) == '\n')||(str.at(p) == '(') ) {
                        continue;
                }

                if( str.at(p) == '[' ) {

                        space_clear_zone(current_zone);

                        current_block = 0;

                        current_zone++;

                        continue;
                }

                int start = 0;
                int stop = 0;
                unsigned idx = 0;

                do {

                        start = str.find_first_not_of(" ", stop);
                        stop = str.find_first_of(" ", start);

                        if(start == -1) break;

                        string s = str.substr(start,stop - start);
                        u8 value = atoi(s.c_str());

                        //cout << s.c_str() << " " ;

                        space_set_element( current_zone-1, current_block, total, value );
                        space_get_element( current_zone-1, current_block, total, value );

                        info.checksum += value;

                        total++;

                } while (idx < str.length());

                if((total % info.block_size) == 0) {

                        //cout << "processed... [" << current_zone << "] : [" << current_block << "] "<< endl;
                        current_block++;
                        total = 0;
                }

                //cout << endl;
        }

        //cout << hex << "Checksum: " << int(info.checksum) << endl;
        //cout << dec << endl;

        ifs.close();

        return 0;
}

//------------------------------------------------------------------------------

int space::space_reconfig_memory(const char *config_name)
{
        //cout << "space::space_reconfig_memory()" << endl;

        if(file_name) delete[] file_name;

        file_name = new char[strlen(config_name)+1];
        if(!file_name) {
                log.msg(GetLastError());
                return -1;
        }

        strcpy(file_name,config_name);

        if(space_create_memory() < 0) {
                //log.msg("Error!");
                return -1;
        }

        if(space_fill_memory() < 0) {
                //log.msg("Error!");
                return -1;
        }

        return 0;
}

//------------------------------------------------------------------------------

int space::space_save_memory(const char *config)
{
        //cout << "space::space_save_memory()" << endl;

        fstream  ofs;
        string   str;

        if(!file_name) {
                log.msg("Error!");
                return -1;
        }

        if(config) {
                ofs.open( config, ios::out );
        } else {
                ofs.open( "settings.cfg", ios::out );
        }

        if (!ofs.is_open()) {
                log.msg( GetLastError() );
                return -2;
        }

        u8 value = 0;

        for(int current_zone=0; current_zone<info.zones; current_zone++) {

                ofs << endl;
                ofs << "[ Zone" << current_zone << " ]" << endl;

                for(int current_block=0; current_block<info.blocks_in_zone; current_block++) {

                        ofs << endl;
                        ofs << "; " << current_block << endl;

                        for(int j=0; j<info.block_size; j++) {

                                if((j%16) == 0) ofs << endl;

                                if( space_get_element(current_zone,current_block,j,value) < 0)
                                        return -3;
                                else
                                        ofs << dec << setw(3) << int(value) << " ";
                        }

                        ofs << endl;
                }
        }

        ofs.close();

        return 0;
}

//------------------------------------------------------------------------------

const u8* space::space_data_block(int zone, int block)
{
        //cout << "space::space_data_block()" << endl;

        if(zone > info.zones) {
                //cout << "space::space_data_block() - invalid zone number" << endl;
                return NULL;
        }

        if(block > info.blocks_in_zone) {
                //cout << "space::space_data_block() - invalid block number" << endl;
                return NULL;
        }

        u8 value = 0;
        for(int i=0; i<info.block_size; i++) {
                if(space_get_element(zone,block,i,value) < 0)
                        return NULL;
                else
                        user_block[i] = value;
        }

        return user_block;
}

//------------------------------------------------------------------------------

u16 space::space_data_crc(int devn)
{
        if(devn == 0) {
                return info.checksum;
        }

        devn -= 1;

        u8 value = 0;
        u16 device_crc = 0;

        for(int current_zone=0; current_zone<info.zones; current_zone++) {

                for(int i=0; i<info.block_size; i++) {

                        if(space_get_element(current_zone,devn,i,value) < 0)
                                return 0xFFFF;
                        else
                                device_crc += value;
                }
        }

        //cout << "space::space_data_crc(" << devn << ") = " << hex << int(device_crc) << endl;
        //cout << dec << endl;

        return device_crc;
}

//------------------------------------------------------------------------------

int  space::space_fill(int zone, int block, space_fill_type type, u8 pattern)
{
        int i = 0;
        u8 value = 0;

        switch(type) {
            case FILL_RANDOM:
            {
                //srand(pattern);

                for(i=0; i<info.block_size; i++) {
                    if(i < info.channels) {
                        value = (rand() % 31);
                        space_set_element(zone, block, i, value);
                    } else {
                        value = 0;
                        space_set_element(zone, block, i, value);
                    }
                }
                //установка значения последнего элемента в КС блока
                //value = space_data_crc(block+1);
                //space_set_element(zone,block,i,value);
            }
            break;
            case FILL_PATTERN:
            {
                for(i=0; i<info.block_size; i++)
                {
                    if(i < info.channels) {
                        value = pattern;
                        space_set_element(zone, block, i, value);
                    } else {
                        value = 0;
                        space_set_element(zone, block, i, value);
                    }
                }
                //установка значения последнего элемента в КС блока
                //value = space_data_crc(block+1);
                //space_set_element(zone,block,i,value);
            }
            break;
        }
        return 0;
}
