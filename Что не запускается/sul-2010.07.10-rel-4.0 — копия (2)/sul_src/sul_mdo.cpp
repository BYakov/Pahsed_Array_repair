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

#ifndef _SUL_MDO_H_
#include "sul_mdo.h"
#endif

using namespace std;

//------------------------------------------------------------------------------

sul_mdo::sul_mdo( device *hw, const char *sul_mdo_config, const char *ram_mdo_config ):
sul_base( sul_mdo_config, ram_mdo_config)
{
        //cout << "sul_mdo::sul_mdo()" << endl;

        packet = new packet485(hw);

        sul_connect_device(hw);

        detect();
}

//------------------------------------------------------------------------------

sul_mdo::~sul_mdo()
{
        //cout << "sul_mdo::~sul_mdo()" << endl;

        if(packet) delete packet;
}

//------------------------------------------------------------------------------

int sul_mdo::detect()
{
        cout << "sul_mdo::detect_abonents()" << endl;

        int i=0;
        unsigned char   addresses[MAX_ABONENT_NUMBER];
        unsigned char   size = 1;
        unsigned char   total = 0;

        memset(addresses,0,sizeof(addresses));

        int   res = 0;
        for(i=1; i<MAX_ABONENT_NUMBER+1; i++) {

                res = packet->request(i,target_address,0,&addresses[i-1],size);
                if(res < 0) {
                        cout << "detect_abonents(" << i << "): target_address - error" << endl;
                        continue;
                } else {
                        cout << "detect_abonents(" << i << "): address " << int(addresses[i-1]) << " Ok" << endl;
                        total++;
                }
                Sleep(1);
        }

        if(!total) return 0;

        //abonents.at(0) - будет зарезервирован для групповой передачи
        //индексирвание вектора абонентов долдно вестись с 1. ( для красоты :) )
        abonents.reserve( total+1 );

        struct module a = {0};

        abonents.push_back(a);

        for(i=1; i<=MAX_ABONENT_NUMBER; i++) {
                if((addresses[i-1] != 0xff) && (addresses[i-1] != 0)) {
                        a.address = addresses[i-1];
                        abonents.push_back(a);
                        cout << "insert abonent at address: " << int(a.address) << endl;
                }
        }

        cout << "found " << int(total) << " abonents" << endl;
        //cout << "vector size " << int(abonents.size()) << " abonents" << endl;

        return total;
}

//------------------------------------------------------------------------------

void sul_mdo::info()
{
        //cout << "sul_mdo::info()" << endl;

        unsigned i = 0;
        int res = 0;
        int err = 0;

        for(i=1; i<abonents.size(); i++) {

                if(!is_online(i)) continue;

                //КС данных EEPROM из конфигурационного пространства
                abonents.at(i).config_eeprom_cs = sul_flash_crc(i);

                //КС данных из EEPROM устройства
                res = packet->request(address(i), target_eeprom_crc, 0, &abonents.at(i).device_eeprom_cs, 2);
                if(res < 0) {
                        //cout << "sul_mdo::info(): Abonent " << int(address(i)) << ": target_eeprom_crc - error" << endl;
                        --err;
                }

                Sleep(20);

                //КС данных из RAM устройства
                res = packet->request(address(i), target_ram_crc, 0, &abonents.at(i).device_ram_cs, 2);
                if(res < 0) {
                        //cout << "sul_mdo::info(): Abonent " << int(address(i)) << ": target_eeprom_crc - error" << endl;
                        --err;
                }
        }
}

//------------------------------------------------------------------------------

int sul_mdo::write_eeprom_block(int zone, int block)
{
        //cout << "sul_mdo::write_eeprom_block()" << endl;

        unsigned char *data = (unsigned char*)flash_data_block(zone,block);
        if(!data) {
                //cout << "write_eeprom_block(): invalid block address" << endl;
                return -1;
        }

        int res = packet->request(bn_to_addr(block),host_eeprom_data,zone,data,flash_block_size());
        if(res < 0) {
                //cout << "write_eeprom_block(): target_eeprom_data - error." << endl;
                return -1;
        }

        return 0;
}

//------------------------------------------------------------------------------

int sul_mdo::read_eeprom_block(int zone, int block, unsigned char *buffer, int size)
{
        //cout << "sul_mdo::read_eeprom_block()" << endl;

        if(size < flash_block_size()); {
                //cout << "read_eeprom_block(): invalid buffer size" << endl;
                return -1;
        }

        int res = packet->request(address(block),target_eeprom_data,zone,buffer,flash_block_size());
        if(res < 0) {
                //cout << "read_eeprom_block(): target_eeprom_data - error." << endl;
                return -1;
        }

        return 0;
}

//------------------------------------------------------------------------------

int sul_mdo::write_ram_block(int zone, int block)
{
        //cout << "sul_mdo::write_ram_block()" << endl;

        unsigned char *data = (unsigned char*)ram_data_block(zone,block);
        if(!data) {
                //cout << "write_ram_block(): invalid block address" << endl;
                return -1;
        }

        int res = packet->request(bn_to_addr(block),host_ram_data,zone,data,ram_block_size());
        if(res < 0) {
                //cout << "write_ram_block(): host_ram_data - error." << endl;
                return -1;
        }

        return 0;
}

//------------------------------------------------------------------------------

int sul_mdo::read_ram_block(int zone, int block, unsigned char *buffer, int size )
{
        //cout << "sul_mdo::read_ram_block()" << endl;

        if(size < ram_block_size()) {
                //cout << "read_ram_block(): invalid buffer size" << endl;
                return -1;
        }

        int res = packet->request(address(block),target_ram_data,zone,buffer,ram_block_size());
        if(res < 0) {
                //cout << "read_ram_block(): target_ram_data - error." << endl;
                return -1;
        }

        return 0;
}

//------------------------------------------------------------------------------

bool sul_mdo::is_online(unsigned addr)
{
    if(!addr) return false;

    for(unsigned i=0; i<abonents.size(); i++) {
        if(abonents.at(i).address == addr)
            return true;
    }

    return false;
}

//------------------------------------------------------------------------------

bool sul_mdo::is_any()
{
    if(abonents.size())
            return true;
    return false;
}

//------------------------------------------------------------------------------

unsigned char sul_mdo::bn_to_addr(unsigned bn)
{
    return bn+1;
}

//------------------------------------------------------------------------------

unsigned char sul_mdo::address(unsigned addr)
{
    return addr;
}

//------------------------------------------------------------------------------
//              Реализация интерфейса базового класса
//------------------------------------------------------------------------------

int sul_mdo::sul_init(int addr)
{
        //cout << "sul_mdo::sul_init()" << endl;

        int res = 0;
        int err = 0;

        if(addr) {

            if(!is_online(addr)) return -1;

            res = packet->request(address(addr),target_eeprom_to_plm, 0, NULL, 0);
            if(res < 0) {
                        //cout << "sul_init(): Abonent " << int(address(addr)) << ": target_eeprom_to_plm - error" << endl;
                        --err;
            }

        } else {

            if(!is_any()) return -1;

            for(unsigned i=1; i<abonents.size(); ++i) {

                    if(!is_online(i)) continue;

                    res = packet->request(address(i),target_eeprom_to_plm, 0, NULL, 0);
                    if(res < 0) {
                            //cout << "sul_init(): Abonent " << int(address(i)) << ": target_eeprom_to_plm - error" << endl;
                            --err;
                            continue;
                    }
            }
        }

        return err;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_reset(int addr)
{
        //cout << "sul_mdo::sul_reset()" << endl;

        int res = 0;
        int err = 0;

        if(addr) {

            if(!is_online(addr)) return -1;

            res = packet->request(address(addr),target_reset, 0, NULL, 0);
            if(res < 0) {
                        //cout << "sul_reset(): Abonent " << int(address(addr)) << ": target_reset - error" << endl;
                        --err;
            }

        } else {

            if(!is_any()) return -1;

            for(unsigned i=1; i<abonents.size(); ++i) {

                if(!is_online(i)) continue;

                res = packet->request(address(i), target_reset, 0, NULL, 0);
                if(res < 0) {
                        //cout << "sul_reset(): Abonent " << i << ": target_reset - error" << endl;
                        --err;
                        continue;
                }
            }

        }

        return err;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_test(int addr)
{
        //проверка обмена
        //проверка вычислителей
        //проверка каналов
        return -1;
}

//------------------------------------------------------------------------------
/*
int sul_mdo::sul_test_exchange(int addr, unsigned char *buffer, int size)
{
    if(!is_online(addr)) return -1;

    int res = 0;
    unsigned char *to_target = (unsigned char*)malloc(size);
    unsigned char *to_host = (unsigned char*)malloc(size);

    if(!to_target || !to_host || !size)
        return -1;

    memset(to_host,0,size);
    memcpy(to_target,buffer,size);

    res = packet->request(address(addr), host_to_target, 0, to_target, size);
    if(res < 0) {
        //cout << "sul_test_exchange(): Abonent " << int(address(addr)) << ": host_to_target - error" << endl;
        free(to_target);
        free(to_host);
        return -1;
    }

    Sleep(500);

    res = packet->request(address(addr), target_to_host, 0, to_host, size);
    if(res < 0) {
        //cout << "sul_test_exchange(): Abonent " << int(address(addr)) << ": target_to_host - error" << endl;
        free(to_target);
        free(to_host);
        return -1;
    }

    res = memcmp(to_host,to_target,size);

    free(to_target);
    free(to_host);

    return res;
}
*/
//------------------------------------------------------------------------------

int sul_mdo::sul_test_channels(int addr)
{
    if(!is_online(addr)) return -1;

    int res = 0;
    int size = sul_total_channels(addr);
    int offset = (address(addr)-1)*size;

    unsigned char *buffer = (unsigned char *)malloc(size);
    if(!buffer)
        return -1;

    memset(buffer,0,size);

    res = packet->request(address(addr), target_ctrl_channel, 0, NULL, 0);
    if(res < 0) {
        //cout << "sul_test(): Abonent " << int(address(addr)) << ": target_ctrl_channel - error" << endl;
        free(buffer);
        return -1;
    }

    Sleep(800);

    res = packet->request(address(addr), target_channel_return, 0, buffer, size);
    if(res < 0) {
        //cout << "sul_test(): Abonent " << int(address(addr)) << ": target_channel_return - error" << endl;
        free(buffer);
        return -1;
    }

    // корректировка размера в случае если число каналов абонента
    // больше чем число подключенных каналов
    if(size+offset > sul_total_channels()) {
        size -= (number_of_channels*number_of_abonents - connected_channels);
    }

    for(int i=0; i<size; i++) {

        shifters.at(offset+i).chan_code = buffer[i];
        if((shifters.at(offset+i).chan_code >= channel_low_level) &&
           (shifters.at(offset+i).chan_code <= channel_top_level)) {
            shifters.at(offset+i).state = channel_operational;
        } else {
            if(shifters.at(offset+i).chan_code == 0)
                shifters.at(offset+i).state = channel_short_circuit;
            else
                shifters.at(offset+i).state = channel_open_fault;
        }
    }

    free(buffer);

    return 0;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_test_calculators(int addr)
{
    if(!is_online(addr)) return -1;

    int res = 0;
    int size = sul_total_channels(addr);
    int offset = (address(addr)-1)*size;

    unsigned char *buffer = (unsigned char *)malloc(size);
    if(!buffer)
        return -1;

    memset(buffer,0,size);

    res = packet->request(address(addr), target_ctrl_calc, 0, NULL, 0);
    if(res < 0) {
        //cout << "sul_test(): Abonent " << int(address(addr)) << ": target_ctrl_channel - error" << endl;
        free(buffer);
        return -1;
    }

    Sleep(800);

    res = packet->request(address(addr), target_calc_return, 0, buffer, size);
    if(res < 0) {
        //cout << "sul_test(): Abonent " << int(address(addr)) << ": target_channel_return - error" << endl;
        free(buffer);
        return -1;
    }

    if(size+offset > sul_total_channels()) {
        size -= (number_of_channels*number_of_abonents - connected_channels);
    }

    for(int i=0; i<size; i++) {
        shifters.at(offset+i).calc_code = buffer[i];
    }

    free(buffer);

    return 0;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_test_pulses(int addr)
{
    if(!is_online(addr)) return -1;

    int res = 0;
    int size = sul_total_channels(addr);
    int offset = (address(addr)-1)*size;

    unsigned char *buffer = (unsigned char *)malloc(size);
    if(!buffer)
	return -1;

    memset(buffer,0,size);

    res = packet->request(address(addr), target_ctrl_impulse, 0, NULL, 0);
    if(res < 0) {
	free(buffer);
	return -1;
    }

    Sleep(800);

    res = packet->request(address(addr), target_impulse_return, 0, buffer, size);
    if(res < 0) {
	free(buffer);
	return -1;
    }

    if(size+offset > sul_total_channels()) {
	size -= (number_of_channels*number_of_abonents - connected_channels);
    }

    for(int i=0; i<size; i++) {
	shifters.at(offset+i).pulse_code = buffer[i];
    }

    free(buffer);

    return 0;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_beam_position(u16 x, u16 y, u8 zone, ray_type type)
{
        if(!is_any()) return -1;

        unsigned char cmd = (type << 4) | zone;

        return packet->request(x, y, cmd);
}

//------------------------------------------------------------------------------

struct sul_state sul_mdo::sul_state(int addr)
{
        struct sul_state st = {0};
        return st;
}

//------------------------------------------------------------------------------
//                              Работа с FLASH
//------------------------------------------------------------------------------

int sul_mdo::sul_flash_erase(int addr)
{
        struct host_dbg_header hdr = {0};
        //cout << "sul_mdo::sul_erase_flash()" << endl;

        int res = 0;
        int err = 0;

        dev->reset();

        if(addr) {

            if(!is_online(addr)) return -1;

            res = packet->request(address(addr), target_eeprom_clear, flash::info.zones, NULL, 0);
            if(res < 0) {
                    //cout << "sul_flash_erase(): Abonent " << int(address(addr)) << ": target_eeprom_clear - error" << endl;
                    --err;
            }

        } else {

            if(!is_any()) return -1;

            //Стереть FLASH у всех абонентов
            for(unsigned i=1; i<abonents.size(); ++i) {

                    if(!is_online(i)) continue;

                    //cout << "Erasing abonents " << int(address(i)) << " EEPROM ..." << endl;

                    hdr = packet->create_dbg_header(address(i),target_eeprom_clear,flash::info.zones, NULL, 0);
                    if( dev->write_raw(&hdr,sizeof(struct host_dbg_header)) < 0 ) {
                        //cout << "sul_flash_erase(): Abonent " << int(address(i)) << ": target_eeprom_clear - error" << endl;
                        --err;
                    }

                    Sleep(300);
            }

            Sleep(15000);

            for(unsigned i=1; i<abonents.size(); ++i) {

                struct target_dbg_header thdr = {0};

                if(!is_online(i)) continue;

                if( dev->read_raw(&thdr,sizeof(struct target_dbg_header)) != sizeof(struct target_dbg_header) ) {
                    //cout << "sul_flash_erase(): Abonent " << int(address(i)) << ": header error" << endl;
                    --err;
                    continue;
                } else {
                    if( thdr.code != target_eeprom_clear ||
                        thdr.sign != target_signature ) {
                        //cout << "sul_flash_erase(): Abonent " << int(address(i)) << ": address error" << endl;
                    } else {
                        //cout << "Abonent " << int(thdr.addr) << " - COMPLETE" << endl;
                    }
                }
            }
        }

        return err;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_flash_load(const char *fname, int addr)
{
        cout << "sul_mdo::sul_load_flash( " <<
                (fname ? fname : flash_config_file()) << " )" << endl;

        if(fname) {
                if( sul_flash_reconfig(fname) < 0) {
                        flash::log.msg("Ошибка реконфигурации пространства FLASH!");
                        return -1;
                }
        }

        int err = 0;

        if(addr) {

            if(!is_online(addr)) return -1;

            cout << "sul_mdo::sul_load_flash( " << int(address(addr)) << " )" << endl;

            //Загрузить данные из конфигурационного пространства во FLASH абонента
            for(int current_zone=0; current_zone < flash::info.zones; ++current_zone) {

               cout << "loading... [" << current_zone << "]:[" << addr << "]";

               if(!is_online(addr)) continue;

               if( write_eeprom_block( current_zone, addr ) < 0 ) {
                   cout << " - ERROR" << endl;
                   --err;
                   break;
               }

               cout << " - COMPLETE" << endl;
           }

        } else {

            if(!is_any()) return -1;

            //Загрузить данные из файла во FLASH абонентов
            for(int current_zone=0; current_zone < flash::info.zones; ++current_zone) {

                    for(int current_block=0; current_block < flash::info.blocks_in_zone; ++current_block) {

                            cout << "Loading ... [" << current_zone << "]:[" << current_block << "]";

                            if(!is_online(current_block+1)) continue;

                            if( write_eeprom_block( current_zone, current_block ) < 0 ) {
                                    cout << " - ERROR" << endl;
                                    --err;
                                    break;
                            }

                            cout << " - COMPLETE" << endl;

                            Sleep(400);
                    }
            }

        }

        return err;
}

//------------------------------------------------------------------------------

u16 sul_mdo::sul_flash_crc(int addr)
{
        //cout << "sul_mdo::sul_flash_crc()" << endl;

        int res = 0;
        int err = 0;
        u16 crc = 0;

        if(addr) {

            if(!is_online(addr)) return -1;

            res = packet->request(address(addr),
                                  target_eeprom_crc,
                                  flash::info.zones,
                                  &abonents.at(address(addr)).device_eeprom_cs,
                                  sizeof(u16));
            if(res < 0) {
                //cout << "sul_flash_crc(): Abonent " << int(address(addr)) << ": target_eeprom_crc - error" << endl;
                --err;
            } else {
                cout << "sul_flash_crc(): Abonent " << int(address(addr)) << ": crc " << hex << int(abonents.at(address(addr)).device_eeprom_cs) << endl;
                cout << dec << endl;
            }
            crc = abonents.at(address(addr)).device_eeprom_cs;

        } else {

            if(!is_any()) return -1;

            for(unsigned i=1; i<abonents.size(); ++i) {

                    if(!is_online(i)) continue;

                    res = packet->request(address(i),
                                          target_eeprom_crc,
                                          flash::info.zones,
                                          &abonents.at(address(addr)).device_eeprom_cs,
                                          sizeof(u16));
                    if(res < 0) {
                            //cout << "sul_flash_crc(): Abonent " << int(address(i)) << ": target_eeprom_crc - error" << endl;
                            --err;
                            continue;
                    } else {
                            cout << "sul_flash_crc(): Abonent " << int(address(i)) << ": crc " << hex << int(abonents.at(address(addr)).device_eeprom_cs) << endl;
                            cout << dec << endl;

                            crc += abonents.at(address(addr)).device_eeprom_cs;
                    }
            }
        }

        return crc;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_flash_save(const char *file)
{
        //if(file)
            //cout << "sul_flash_save(" << file << ")" << endl;

        return flash::space_save_memory(file);
}

//------------------------------------------------------------------------------
//      Работа с RAM
//------------------------------------------------------------------------------

int sul_mdo::sul_ram_load(const char *fname, int addr)
{
    cout << "sul_mdo::sul_ram_load( " <<
            (fname ? fname : ram_config_file()) << " )" << endl;

    if(fname) {
            if( sul_ram_reconfig(fname) < 0) {
                    ram::log.msg("Ошибка реконфигурации пространства RAM!");
                    return -1;
            }
    }

    int err = 0;

    if(addr) {

        if(!is_online(addr)) return -1;

        cout << "sul_mdo::sul_ram_load( " << int(address(addr)) << " )" << endl;

        //Загрузить данные из конфигурационного пространства в RAM абонента
        for(int current_zone=0; current_zone < ram::info.zones; ++current_zone) {

           cout << "loading... [" << current_zone << "]:[" << addr << "]";

           if( write_ram_block( current_zone, addr ) < 0 ) {
               cout << " - ERROR" << endl;
               --err;
               break;
           }

           cout << " - COMPLETE" << endl;
       }

    } else {

        if(!is_any()) return -1;

        //Загрузить данные конфигурационного пространства в RAM абонентов
        for(int current_zone=0; current_zone < ram::info.zones; ++current_zone) {

                for(int current_block=0; current_block < ram::info.blocks_in_zone; ++current_block) {

                        if(!is_online(current_block+1)) continue;

                        cout << "loading... [" << current_zone << "]:[" << current_block << "]";

                        if( write_ram_block( current_zone, current_block ) < 0 ) {
                                cout << " - ERROR" << endl;
                                --err;
                                break;
                        }

                        cout << " - COMPLETE" << endl;
                }
        }
    }

    return err;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_ram_save(const char *file)
{
    //if(file)
        //cout << "sul_ram_save( " << file << " )" << endl;

    return ram::space_save_memory(file);
}

//------------------------------------------------------------------------------

int sul_mdo::sul_ram_erase(int addr)
{
    //cout << "sul_mdo::sul_ram_erase()" << endl;

    int res = 0;
    int err = 0;

    if(addr) {

        if(!is_online(addr)) return -1;

        res = packet->request(address(addr), target_ram_clear, 0, NULL, 0);
        if(res < 0) {
                //cout << "sul_ram_erase(): Abonent " << int(address(addr)) << ": target_ram_clear - error" << endl;
                --err;
        } else {
                //cout << "sul_ram_erase(): Abonent " << int(address(addr)) << " ram erased" << endl;
        }

    } else {

        if(!is_any()) return -1;

        for(unsigned i=1; i<abonents.size(); ++i) {

                if(!is_online(i)) continue;

                res = packet->request(address(i), target_ram_clear, 0, NULL, 0);
                if(res < 0) {
                        //cout << "sul_ram_erase(): Abonent " << int(address(i)) << ": target_ram_clear - error" << endl;
                        --err;
                        continue;
                } else {
                        //cout << "sul_ram_erase(): Abonent " << int(address(i)) << " ram erased" << endl;
                }
        }
    }

    return err;
}

//------------------------------------------------------------------------------

u16 sul_mdo::sul_ram_crc(int addr)
{
    //cout << "sul_mdo::sul_ram_crc()" << endl;

    int res = 0;
    int err = 0;
    u16 abonent_crc[MAX_ABONENT_NUMBER] = {0};
    u16 crc = 0;

    if(addr) {

        if(!is_online(addr)) return -1;

        res = packet->request(address(addr), target_ram_crc, 0, &abonent_crc[addr], sizeof(u16));
        if(res < 0) {
            //cout << "sul_ram_crc(): Abonent " << int(address(addr)) << ": target_ram_crc - error" << endl;
            --err;
        } else {
            cout << "sul_ram_crc(): Abonent " << int(address(addr)) << ": crc " << hex << int(abonent_crc[addr]) << endl;
            cout << dec << endl;
        }
        crc = abonent_crc[addr];

    } else {

        if(!is_any()) return -1;

        for(unsigned i=1; i<abonents.size(); ++i) {

                if(!is_online(i)) continue;

                res = packet->request(address(i), target_ram_crc, 0, &abonent_crc[i], sizeof(u16));
                if(res < 0) {
                        //cout << "sul_ram_crc(): Abonent " << int(address(i)) << ": target_ram_crc - error" << endl;
                        --err;
                        continue;
                } else {
                        cout << "sul_ram_crc(): Abonent " << int(address(i)) << ": crc " << hex << int(abonent_crc[i]) << endl;
                        cout << dec << endl;
                }
                crc += abonent_crc[i];
        }
    }

    if(err < 0)
        return 0xffff;
    else
        return crc;
}

//------------------------------------------------------------------------------

int sul_mdo::sul_set_scale(int addr, unsigned char scale, unsigned char reset_duration, unsigned char pause_duration)
{
    unsigned char Scale[3] = {scale, reset_duration, pause_duration};
    int res = 0;
    int err = 0;

    //cout << "sul_set_scale()" << endl;

    if(addr) {

        if(!is_online(addr)) return -1;

        res = packet->request(address(addr), host_scale, 0, &Scale, sizeof(unsigned char));
        if(res < 0) {
                //cout << "sul_set_scale(): Abonent " << int(address(addr)) << ": host_scale - error" << endl;
                return -1;
        }

    } else {

        if(!is_any()) return -1;

        for(unsigned i=1; i<abonents.size(); ++i) {

                if(!is_online(i)) continue;

                res = packet->request(address(i), host_scale, flash::info.zones, &Scale, sizeof(Scale));
                if(res < 0) {
                        //cout << "sul_set_scale(): Abonent " << int(address(i)) << ": host_scale - error" << endl;
                        --err;
                        continue;
                }
        }
    }

    return 0;
}

//------------------------------------------------------------------------------

unsigned char sul_mdo::sul_get_scale(int addr)
{
    unsigned char Scale[3] = {0};
    int res = 0;

    if(!is_online(addr)) return -1;

    res = packet->request(address(addr), target_scale_return, 0, &Scale, sizeof(Scale));
    if(res < 0) {
        //cout << "sul_get_scale(): Abonent " << int(address(addr)) << ": target_scale_return - error" << endl;
        return 0;
    }

    return Scale[0];
}
