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

#ifndef _SUL_BASE_H_
#include "sul_base.h"
#endif

using namespace std;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//	         Реализация базового класса СУЛ    	         //
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

#define PINS_ON_CONNECTOR   64

///////////////////////////////////////////////////////////////////

sul_base::sul_base(const char *flash_file, const char *ram_file, int modules, int channels) :
flash(flash_file, modules, channels),
ram(ram_file, modules, channels),
mode(mode_rk)
{
        //cout << "sul_base::sul_base()" << endl;

        fi = new fi0(".\\config\\fi0_mdo.cfg");

        g_state.exch_err = 0;
        g_state.calc_err = 0;
        g_state.chan_err = 0;

        number_of_lines = 0;
        number_of_channels = 0;
        connected_channels = 0;
        number_of_abonents = flash::info.blocks_in_zone;
        pins_on_abonent_connector = PINS_ON_CONNECTOR;

        channel_low_level = 30;
        channel_top_level = 50;
        channel_mid_level = 0.5*(channel_low_level+channel_top_level);

        detect_sul_params();
}

///////////////////////////////////////////////////////////////////

sul_base::~sul_base()
{
        //cout << "sul_base::~sul_base()" << endl;
        dev = NULL;

        lines.clear();
        shifters.clear();
        abonents.clear();
}

///////////////////////////////////////////////////////////////////

void sul_base::sul_set_mode(sul_mode m)
{
        mode = m;
}

///////////////////////////////////////////////////////////////////

void sul_base::sul_connect_device(device *hw)
{
        if(hw && (hw != dev)) dev = hw;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_phase_shifter_info(unsigned int N, struct phase_shifter& shifter)
{
    memset(&shifter, 0, sizeof(struct phase_shifter));

    if(N >= shifters.size()) {
        //cout << "Invalid channel number: " << N << endl;
        return -1;
    }

    shifter = shifters.at(N);

    //cout << "N: " << int(shifter.channel_number) <<
    //" L: " << int(shifter.line) <<
    //" C: " << int(shifter.pulse_code) << endl;
    //" S: " << int(shifter.state) <<
    //" C: " << int(shifter.connector) <<
    //" X: " << int(shifter.x) <<
    //" Y: " << int(shifter.y) << endl;

    return 0;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_phase_shifter_info(unsigned char X, unsigned char Y, struct phase_shifter& shifter)
{
    // проблема при повороте решетки на 90 градусов. При этом нужно как то знать что X стал Y а Y стал X.

    int off = 0;
    unsigned N;

    memset(&shifter, 0, sizeof(struct phase_shifter));

    //cout << "X " << int(X) << " " << "Y " << int(Y) << endl;

    if(Y > lines.size() || Y < 0) {
        cout << "Invalid coordinate Y: " << int(Y) << endl;
        return -1;
    }

    for(int i=0; i<Y; i++) {
        off += lines.at(i);
    }

    for(int col=0; col<lines.at(Y); col++ ) {

        N = off + col;

        if((shifters.at(N).x == X) && (shifters.at(N).y == Y)) {

            shifter = shifters.at(N);
    /*
            cout << "N: " << int(shifter.channel_number) <<
                    " L: " << int(shifter.line) <<
                    " S: " << int(shifter.state) <<
                    " C: " << int(shifter.connector) <<
                    " X: " << int(shifter.x) <<
                    " Y: " << int(shifter.y) << endl;
    */
            return 0;
        }
    }

    return -1;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_total_channels(int devn)
{
    if(devn) return number_of_channels;

    return connected_channels;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_total_abonents()
{
    return number_of_abonents;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_active_abonents()
{
    int N = abonents.size();
    if(N)
        return N - 1;
    return 0;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_abonent_address(unsigned index)
{
    if(index && index < abonents.size())
        return abonents.at(index).address;
    return 0;
}

///////////////////////////////////////////////////////////////////

int sul_base::sul_total_lines()
{
    return lines.size();
}


///////////////////////////////////////////////////////////////////
int sul_base::detect_sul_params()
{
    //cout << "sul_base::detect_params()" << endl;

    fstream  ifs;
    string   str;

    ifs.open( flash_config_file() );
    if (!ifs.is_open()) {
            //cout << "Error open " << flash_config_file() << endl;
            return -1;
    }

    while (!ifs.eof()) {

            getline( ifs, str );

            char *s = strstr(str.c_str(),"LINES");

            if(!s) continue;

            //cout << str.c_str() << endl;
            break;
    }

    lines.clear();
    int p = 0;

    while(!ifs.eof()) {

        getline( ifs, str );

        if(!str.length())  continue;

        if(str.at(0) == ' ') {
            p = str.find_first_not_of(" ",0);
        }

        if(p < 0) continue;

        if((str.at(p) == ';')||(str.at(p) == '\n')||(str.at(p) == '(') ) continue;

        int start = 0;
        int stop = 0;
        int value = 0;

        start = str.find_first_not_of(" ", stop);
        stop = str.find_first_of(" ", start);

        string s = str.substr(start,stop - start);

        value = atoi(s.c_str());

        if(value > 0) number_of_lines++;

        lines.push_back(value);

        //cout << "Line[" << lines.size() << "] : [" << lines[lines.size()-1] << "] "<< endl;
    }

    ifs.close();

    number_of_abonents = flash::info.blocks_in_zone;
    number_of_channels = flash::info.channels;

    for(unsigned i=0; i<lines.size();i++) {
        connected_channels += lines[i];
    }

    alloc_phase_shifters();

    return 0;
}

///////////////////////////////////////////////////////////////////

int sul_base::alloc_phase_shifters()
{
    //cout << "sul_base::alloc_phase_shifters()" << endl;

    // резервируем кратное number_of_channels число фазовращателей
    shifters.clear();
    shifters.reserve(number_of_abonents*number_of_channels);

    if(number_of_abonents*number_of_channels != connected_channels) {
        cout << "Connected phase shifters: " << int(connected_channels) << endl;
        cout << "Abonents  phase shifters: " << int(number_of_abonents*number_of_channels) << endl;
    }

//    fstream  ofs;
//    ofs.open( "grid_array.txt", ios::out );
//    if (!ofs.is_open()) {
//            return -1;
//    }

    int N = 0;
    unsigned char X = 0;
    unsigned char Y = 0;
    int Fi0 = 0;
    struct phase_shifter shifter = {0};

    for(unsigned i=0; i<lines.size(); i++) {

        //ofs << "Line number: " << i << endl;
        //ofs << "Phase shifters count: " << lines.at(i) << endl;
        //cout << "Line number: " << i << endl;
        //cout << "Phase shifters count: " << lines.at(i) << endl;

        for(int j=0; j<lines.at(i); j++) {

            shifter.channel_number = N++;
            shifter.line = i;
            shifter.state = shifter.channel_number < connected_channels ? channel_untested : channel_unconnected;
            shifter.abonent = (shifter.channel_number / number_of_channels);
            shifter.connector = div(shifter.channel_number-shifter.abonent*number_of_channels,pins_on_abonent_connector).quot;

            sul_flash_get_element(9,shifter.abonent,(shifter.channel_number%number_of_channels),X);
            sul_flash_get_element(10,shifter.abonent,(shifter.channel_number%number_of_channels),Y);

            shifter.x = X;
            shifter.y = Y;

            if(fi->fi0_configured()) {
                if( fi->sul_fi0_get_element(shifter.channel_number,Fi0) < 0 ) {
                    shifter.fi0_code = 0;
                } else {
                    shifter.fi0_code = Fi0;
                }
            }

/*
            ofs << "N: " << int(shifter.channel_number) <<
            " L: " << int(shifter.line) <<
            " S: " << int(shifter.state) <<
            " C: " << int(shifter.connector) <<
            " X: " << int(shifter.x) <<
            " Y: " << int(shifter.y) << endl;
*/
/*
            cout << "N: " << int(shifter.channel_number) <<
            " L: " << int(shifter.line) <<
            " S: " << int(shifter.state) <<
            " C: " << int(shifter.connector) <<
            " F: " << int(shifter.fi0_code) <<
            " X: " << int(shifter.x) <<
            " Y: " << int(shifter.y) << endl;
*/
            shifters.push_back(shifter);
        }
    }

//    ofs.close();

    return 0;
}

//----------------------------------------------------------------------------------

void sul_base::sul_set_top_level(int value)
{
    if(value <= 0) return;

    channel_top_level = value;
    channel_mid_level = 0.5*(channel_top_level + channel_low_level);
}

//----------------------------------------------------------------------------------

void sul_base::sul_set_low_level(int value)
{
    if(value <= 0) return;

    channel_low_level = value;
    channel_mid_level = 0.5*(channel_top_level + channel_low_level);
}

//----------------------------------------------------------------------------------
