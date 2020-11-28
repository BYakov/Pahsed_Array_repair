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

#ifndef _SUL_AVR_H_
#include "sul_avr.h"
#endif

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//		Реализация класса управляющих сообщени для СУЛ АВР
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

sul_avr::sul_avr(device *hw, const char *sul_config, const char *ram_config) :
sul_base(sul_config, ram_config),
count(0)
{
	cout << "sul_avr::sul_avr()" << endl;
	sul_connect_device(hw);
}

//------------------------------------------------------------------------------

sul_avr::~sul_avr()
{
	cout << "sul_avr::~sul_avr()" << endl;
}

//------------------------------------------------------------------------------

int sul_avr::send_flash_block(int zone, int block)
{
	//cout << "sul_avr::load_block(" << zone << ", " << block << ")" << endl;
	sul_message msg;

	const u8 *data = flash::space_data_block(zone,block);

	if(!data) {
		//cout << "sul_avr::load_block() - Error get data block" << endl;
		return -1;
	}

	msg.cmd = CMD_BLOCK_LOADED;
	memcpy( msg.data, data, flash::info.block_size );

	if( dev->write_data(&msg,sizeof(sul_message)) != sizeof(sul_message)) {
		//cout << "sul_avr::load_block() - Error write data block" << endl;
		return -1;
	}

	if(checkback(sizeof(sul_message), 10) < 0) {
		return -1;
	}

	if(checkback(CMD_BLOCK_LOADED, 10) < 0) {
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::send_ram_block(int zone, int devn)
{
	cout << "sul_avr::sul_set_ram()" << endl;

	u8 *data = NULL;
	u16 size = ram::info.block_size + 2;
	u8 *ram = new u8[size];

	memset(ram, 0, size);

	data = (u8*)ram_data_block(0,devn);
	if(!data) {
		cout << "sul_avr::sul_set_ram() - Error address of ram block" << endl;
		delete[] ram;
		return -1;
	}

	memcpy(&ram[2], data, ram::info.block_size);

	ram[size-1] = sul_ram_crc(devn);

	ram[0] = CMD_SET_RAM_DATA;
	ram[1] = devn;
	if( dev->write_data(ram, size) != size) {
		cout << "sul_avr::sul_set_ram() - Error write ram block" << endl;
		delete[] ram;
		return -1;
	}

	cout << "sul_avr::sul_set_ram() - Write block " << int(devn) <<
		" CRC: " << int(ram[size-1]) << endl;

	Sleep(100);

	if(checkback(size, 100) < 0) {
		cout << "sul_avr::sul_set_ram() - Error execute command" << endl;
		delete[] ram;
		return -1;
	}

	if(checkback(CMD_SET_RAM_DATA, 100) < 0) {
		cout << "sul_avr::sul_set_ram() - Error execute command" << endl;
		delete[] ram;
		return -1;
	}

	delete[] ram;

	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::checkback(int size, int timeout)
{
	u8	ans = 0;

	if( dev->read_data(&ans,sizeof(ans)) < 0)	{
		return -1;
	}

	if( ans != size ) {
		cout << dec << "sul_avr::checkback_cmd(size) Erorr: send - " << size << " receive - " << int(ans) << endl;
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::checkback(sul_command cmd, int timeout)
{
	u8	ans = 0;

	if( dev->read_data(&ans,sizeof(ans)) < 0)	{
		return -1;
	}

	if( ans != (u8)cmd ) {

		Sleep(timeout);

		if( dev->read_data(&ans,sizeof(ans)) < 0)	{

			if( ans != cmd ) {
				cout << dec << "sul_avr::checkback(): Erorr command - " << int(cmd) << " answer - " << int(ans) << endl;
				return -1;
			} else {
				return 0;
			}
		}
	}

	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::send_cmd(sul_command cmd, int timeout)
{
	u8 command = cmd;

	if(dev->write_data(&command,sizeof(command)) != 1) {
		cout << "sul_avr::send_cmd() - Error" << endl;
		return -1;
	}
	Sleep(timeout);
	if(checkback(sizeof(command), 10) < 0) {
		return -1;
	}
	if(checkback(command, 10) < 0) {
		return -1;
	}
	return 0;
}

//------------------------------------------------------------------------------
//              Реализация интерфейса базового класса
//------------------------------------------------------------------------------

u16 sul_avr::sul_flash_crc(int devn)
{
	cout << "sul_avr::sul_checksum()" << endl;

	u8 cmd;

	cmd = CMD_CTRL_FLASH;

	if(dev->write_data(&cmd,sizeof(cmd)) != 1) {
		cout << "sul_avr::sul_erase_flash() - Error erase flash" << endl;
		return -1;
	}

	if(checkback(sizeof(cmd), 400) < 0) {
		return -1;
	}

	if(checkback(CMD_CTRL_FLASH, 400) < 0) {
		return -1;
	}

	u16 summ;

	if( dev->read_data(&summ, sizeof(summ)) < 0 ) {
		return -1;
	}

	cout << hex << "sul_avr::sul_checksum(): Device FLASH checksum - " << int(summ) << endl;
	cout << dec << endl;

	return summ;
}

//------------------------------------------------------------------------------

int sul_avr::sul_flash_erase(int devn)
{
	cout << "sul_avr::sul_erase_flash()" << endl;

	u8 cmd;

	cmd = CMD_FLASH_CLEAR;

	if(dev->write_data(&cmd,sizeof(cmd)) != 1) {
		cout << "sul_avr::sul_erase_flash() - Error erase flash" << endl;
		return -1;
	}

	//Sleep(200); //********************

	if(checkback(sizeof(cmd), 100) < 0) {
		return -1;
	}

	Sleep(200); //********************

	if(checkback(CMD_FLASH_CLEAR, 15000) < 0) {
		return -1;
	}

	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::sul_flash_load(const char *fname, int devn)
{
	cout << "sul_avr::sul_load_flash( " <<
		(fname ? fname : flash_config_file()) << " )" << endl;

	if(fname) {
                if( sul_flash_reconfig(fname) < 0) {
			flash::log.msg("Ошибка реконфигурации СУЛ!");
			return -1;
		}
	}

	//int offset = 0;

	for(int current_zone=0; current_zone < flash::info.zones; current_zone++) {

		for(int current_block=0; current_block < flash::info.blocks_in_zone; current_block++) {

			cout << "loading... [" << current_zone << "]:[" << current_block << "]";

			if( send_flash_block(current_zone, current_block) < 0) {
				cout << " - ERROR" << endl;
				return -1;
			}

			cout << " - COMPLETE" << endl;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------
/*
int sul_avr::sul_flash_load(int devn)
{
	cout << "sul_avr::sul_load_flash( " << devn << " )" << endl;

	if(!flash::space_configured()) {
		return -1;
	}

	for(int current_zone=0; current_zone < flash::info.zones; current_zone++) {

		cout << "loading... [" << current_zone << "]:[" << devn << "]";

		if( send_flash_block(current_zone, devn) < 0) {

			cout << " - ERROR" << endl;
			return -1;
		}

		cout << " - COMPLETE" << endl;
	}

	return 0;
}
*/
//------------------------------------------------------------------------------

int sul_avr::sul_init(int devn)
{
	cout << "sul_avr::sul_init()" << endl;

	if(send_cmd(CMD_INIT_MODULES, 1000)) {
		return -1;
	}
	/*
	if(send_cmd(CMD_RETURN_DATA128_0, 1000) < 0) {
	return -1;
	}

	if(dev->device_read(data128_0,128) < 0)
	return -1;

	Sleep(1);

	if(send_cmd(CMD_RETURN_DATA128_1, 1000) < 0) {
	return -1;
	}

	if(dev->device_read(data128_1,128) < 0)
	return -1;
	*/
	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::sul_reset(int devn)
{
	cout << "sul_avr::sul_reset()" << endl;
	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::sul_test(int devn)
{
	cout << "sul_avr::sul_test()" << endl;
	return -1;
}

//------------------------------------------------------------------------------

struct sul_state sul_avr::sul_state(int devn)
{
	struct sul_state st = {0};
	return st;
}

//------------------------------------------------------------------------------

int sul_avr::sul_beam_position(u16 x, u16 y, u8 zone, ray_type type)
{
	cout << "sul_avr::sul_beam_position(" << x << ", " << y << ")" << endl;

	struct ctrl_vector v;

	v.cmd = CMD_RECIEVE_VECTOR;
	v.count = (count << 8) | 1;
	v.mode = (mode << 10);
	v.dX = x;
	v.dY = y;
	v.zone = zone;

	switch (type) 
	{
	case RAY_NARROW: v.zone |= (1 << 3); break;
	case RAY_WIDE:   v.zone |= (1 << 7); break;
	}

	//cout << "sizeof(vector) : " << sizeof(vector) << endl;

	if( dev->write_data(&v,sizeof(ctrl_vector)) != sizeof(ctrl_vector)) {
		//cout << "sul_avr::load_block() - Error write data block" << endl;
		return -1;
	}

	if(checkback(sizeof(ctrl_vector), 100) < 0) {
		return -1;
	}

	if(checkback(CMD_RECIEVE_VECTOR, 100) < 0) {
		return -1;
	}

	count++;

	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::sul_flash_save(const char *file)
{
	cout << "sul_flash_save()" << endl;
	return flash::space_save_memory(file);
}

//------------------------------------------------------------------------------

int sul_avr::sul_ram_load(const char *file, int devn)
{
	const char *fname = file ? file : ram_config_file();

	cout << "sul_avr::sul_ram_load( " << fname << " )" << endl;

	if(fname) {
                if( sul_ram_reconfig(fname) < 0) {
			flash::log.msg("Ошибка реконфигурации СУЛ!");
			return -1;
		}
	} else {
		return -1;
	}

	//
	// Передать блоки RAM всем абонентам если devn = 0
	//
	if(!ram::space_configured()) {
		return -1;
	}

	for(int current_zone=0; current_zone < ram::info.zones; current_zone++) {

		for(int current_block=0; current_block < ram::info.blocks_in_zone; current_block++) {

			cout << "loading... [" << current_zone << "]:[" << current_block << "]";

			if( send_ram_block(current_zone, current_block) < 0) {
				cout << " - ERROR" << endl;
				return -1;
			}

			cout << " - COMPLETE" << endl;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------
/*
int sul_avr::sul_ram_load(int devn)
{
	cout << "sul_avr::sul_ram_load( " << devn << " )" << endl;

	//
	// Передать блоки RAM абоненту devn
	//
	for(int current_zone=0; current_zone < ram::info.zones; current_zone++) {

		cout << "loading... [" << current_zone << "]:[" << devn << "]";

		if( send_ram_block(current_zone, devn) < 0) {
			cout << " - ERROR" << endl;
			return -1;
		}

		cout << " - COMPLETE" << endl;
	}

	return 0;
}
*/
//------------------------------------------------------------------------------

int sul_avr::sul_ram_save(const char *file)
{
	cout << "sul_ram_save()" << endl;
	return ram::space_save_memory(file);
}

//------------------------------------------------------------------------------

int sul_avr::sul_ram_erase(int devn)
{
	cout << "sul_ram_erase()" << endl;
	return 0;
}

//------------------------------------------------------------------------------

u16 sul_avr::sul_ram_crc(int devn)
{
	cout << "sul_ram_crc()" << endl;
	return 0;
}

//------------------------------------------------------------------------------

int sul_avr::sul_test(int devn, unsigned char *buffer, int size)
{
    return -1;
}

//------------------------------------------------------------------------------

int sul_avr::sul_channels(int devn)
{
    if(devn) return number_of_channels;

    return number_of_channels*number_of_abonents;
}

//------------------------------------------------------------------------------

