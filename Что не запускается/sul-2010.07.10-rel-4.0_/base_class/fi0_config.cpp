#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#ifndef _SUL_CONFIG_H_
    #include "sul_config.h"
#endif

#ifndef _FI0_CONFIG_H_
    #include "fi0_config.h"
#endif

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//              Класс для конфигурирования PHASE0
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

fi0::fi0(const char *file)
{
    configured = false;

    if( read_data_file(file) < 0)
        return;

    configured = true;
}

//------------------------------------------------------------------------------

fi0::~fi0()
{
    phases.clear();
}

//------------------------------------------------------------------------------

int fi0::read_data_file(const char *file)
{
    fstream  ifs;
    string   str;

    ifs.open( file );
    if (!ifs.is_open()) {
            //cout << "Error open " << flash_config_file() << endl;
            return -1;
    }

    while (!ifs.eof()) {

            getline( ifs, str );

            char *s = strstr(str.c_str(),"phi0");

            if(!s) continue;

            //cout << str.c_str() << endl;
            break;
    }

    phases.clear();
    int p = 0;
    int number_of_channels = 0;

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
	float data = 0;

        start = str.find_first_not_of(" ", stop);
        stop = str.find_first_of(" ", start);

        string s = str.substr(start,stop - start);

	data = atof(s.c_str());
	value = floor(((data/360.0)*128.0));

        if(value >= 0) number_of_channels++;

        phases.push_back(value);

        //cout << "Line[" << lines.size() << "] : [" << lines[lines.size()-1] << "] "<< endl;
    }

    ifs.close();

    return 0;
}

//------------------------------------------------------------------------------

int fi0::sul_fi0_get_element(unsigned channel, int& data)
{
    if(channel > phases.size())
        return -1;

    data = phases.at(channel);

    return 0;
}

//------------------------------------------------------------------------------
