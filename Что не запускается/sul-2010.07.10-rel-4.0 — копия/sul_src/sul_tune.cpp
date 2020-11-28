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

#ifndef _SUL_TUNE_H_
    #include "sul_tune.h"
#endif

//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------


// Заданный массив E1 из элементов в столбцах ФАР
// соответственно (вид на ФАР спереди )

 static int E1[31]= {4,11,14,17,18,19,22,23,24,25,24,25,26,27,26,27,26,
                     27,26,25,24,25,24,23,22,19,18,17,14,11,4};

 //---------------------------------------------------------------------------

sul_tune::sul_tune(int sul_channels)
{
    total_channels = sul_channels;

    connected_channels = 0;

    CoordX = new int[total_channels];
    CoordY = new int[total_channels];
    calc_array = new double[total_channels];
    F0 = new double[total_channels];
    Slope = new double[total_channels];

    memset(CoordX, 0, sizeof(CoordX));
    memset(CoordY, 0, sizeof(CoordY));
    memset(calc_array, 0, sizeof(calc_array));
    memset(F0, 0, sizeof(F0));
    memset(Slope, 0, sizeof(Slope));

    for(unsigned i=0; i<sizeof(E1)/sizeof(E1[0]); i++)
        connected_channels += E1[i];
}

//---------------------------------------------------------------------------

sul_tune::~sul_tune()
{
    if(CoordX) delete[] CoordX;
    if(CoordY) delete[] CoordY;
    if(calc_array) delete[] calc_array;
    if(F0) delete [] F0;
    if(Slope) delete [] Slope;
}

//---------------------------------------------------------------------------

int sul_tune::calculate_xy()
{
    // Создаем массивы координат Х и Y
    int ZX = 0;
    for (int i = 1; i < 32; i++)
    {
        for (int j = 1; j <E1[i-1]+1; j++)
        {
            ZX++;
            CoordX[ZX-1] = i-1;
        }
    }

    //CoordX[637] = 0;
    //CoordX[638] = 0;
    //CoordX[639] = 0;

    int ZY = 0;
    int BaseCoordinatY = 0;
    for (int i = 1; i < 32; i++)
    {
        for (int j = 1; j < E1[i-1]+1; j++)
        {
            ZY++;
            BaseCoordinatY = 27 - E1[i-1];
            CoordY[ZY-1] = BaseCoordinatY + (j-1)*2;
        }
    }

    //CoordY[637] = 0;
    //CoordY[638] = 0;
    //CoordY[639] = 0;

    return 0;
}

//---------------------------------------------------------------------------

bool sul_tune::read_slope_file(const char *fname)
{
    fstream  ifs;
    string   str;

    ifs.open( fname, ios::in );
    if (!ifs.is_open()) {
            return false;
    }

    int total = 0;

    while (!ifs.eof()) {

            getline( ifs, str );

            if(!str.length()) continue;

            if(str.at(0) == ' ')  continue;

            int start = 0;
            int stop = 0;

            start = str.find_first_not_of(" ", stop);
            stop = str.find_first_of(" ", start);

            if(start == -1) continue;

            string s = str.substr(start,stop - start);
            double value = atof(s.c_str());

            Slope[total] = value;

            total++;
    }

    ifs.close();

    if(total > connected_channels)
        return false;

    return true;
}

//---------------------------------------------------------------------------

bool sul_tune::read_f0_file(const char *fname)
{
    fstream  ifs;
    string   str;

    ifs.open( fname, ios::in );
    if (!ifs.is_open()) {
            return false;
    }

    int total = 0;

    while (!ifs.eof()) {

            getline( ifs, str );

            if(!str.length()) continue;

            if(str.at(0) == ' ')  continue;

            int start = 0;
            int stop = 0;

            start = str.find_first_not_of(" ", stop);
            stop = str.find_first_of(" ", start);

            if(start == -1) continue;

            string s = str.substr(start,stop - start);
            double value = atof(s.c_str());

            F0[total] = value;

            total++;
    }

    ifs.close();

    if(total > connected_channels)
        return false;

    return true;
}

//---------------------------------------------------------------------------

int sul_tune::calculate_revises()
{
    // Проверяем правильность исходных файлов и производим
    if(!read_f0_file("f0.txt"))
        return -1;

    if(!read_slope_file("slope.txt"))
        return -1;

    //загрузку массивов
    calculate_sphere(SX1,SY1,R1,Lambda1);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR1[k] = F_eval[k];
    }


    calculate_sphere(SX2,SY2,R2,Lambda2);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR2[k] = F_eval[k];
    }

    calculate_sphere(SX3,SY3,R3,Lambda3);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR3[k] = F_eval[k];
    }

    calculate_sphere(SX4,SY4,R4,Lambda4);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR4[k] = F_eval[k];
    }

    calculate_sphere(SX5,SY5,R5,Lambda5);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR5[k] = F_eval[k];
    }

    calculate_sphere(SX6,SY6,R6,Lambda6);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR6[k] = F_eval[k];
    }

    calculate_sphere(SX7,SY7,R7,Lambda7);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR7[k] = F_eval[k];
    }

    calculate_sphere(SX8,SY8,R8,Lambda8);                                                  //вычисляем сферу
    for (int k = 0; k < connected_channels; k++)
    {
        CORR8[k] = F_eval[k];
    }
/*
    if (CheckBox4->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR1_F0[k] = fmod(720+CORR1[k]-F0[k]+F0_add,360);
            CORR1_128[k] = floor(CORR1_F0[k]*127/360);     //отбрасываем дробную часть
        }
    }
    if (CheckBox5->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR2_F0[k] = fmod(720+CORR2[k]-F0[k]+F0_add,360);
            CORR2_128[k] = floor(CORR2_F0[k]*127/360);
        }
    }
    if (CheckBox6->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR3_F0[k] = fmod(720+CORR3[k]-F0[k]+F0_add,360);
            CORR3_128[k] = floor(CORR3_F0[k]*127/360);
        }
    }
    if (CheckBox7->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR4_F0[k] = fmod(720+CORR4[k]-F0[k]+F0_add,360);
            CORR4_128[k] = floor(CORR4_F0[k]*127/360);
        }
    }
    if (CheckBox8->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR5_F0[k] = fmod(720+CORR5[k]-F0[k]+F0_add,360);
            CORR5_128[k] = floor(CORR5_F0[k]*127/360);
        }
    }
    if (CheckBox9->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR6_F0[k] = fmod(720+CORR6[k]-F0[k]+F0_add,360);
            CORR6_128[k] = floor(CORR6_F0[k]*127/360);
        }
    }
    if (CheckBox10->Checked)
    {
        for (int k=0; k<connected_channels;k++)
        {
            CORR7_F0[k] = fmod(720+CORR7[k]-F0[k]+F0_add,360);
            CORR7_128[k] = floor(CORR7_F0[k]*127/360);
        }
    }
    if (CheckBox11->Checked)
    {
        for (int k = 0; k < connected_channels; k++)
        {
            CORR8_F0[k] = fmod(720 + CORR8[k] - F0[k] + F0_add, 360);
            CORR8_128[k] = floor(CORR8_F0[k]*127/360);
        }
    }

    for (int k = 0; k < connected_channels; k++)
    {
        if (CANT[k] > 0)
            CANT_128[k] = floor(17.15*Kcant*64/CANT[k]);
        else
            CANT_128[k] = 0;
    }
*/
/*
    // Создаем файл для последующей инициализации СУЛ
    const char *sectors = { "CORR1_F0"; "CORR2_F0"; "CORR3_F0"; "CORR4_F0";
                            "CORR5_F0"; "CORR6_F0"; "CORR7_F0"; ,"CORR8_F0";
                            "CANT"; "CoordX"; "CoordY"; "LINES" }
    if (!err)
    {
        fid_outcorr = fopen(newname.c_str(),"wt");
        struct date d;
        getdate(&d);
        fprintf(fid_outcorr,"%s %d %d %d\n\n","; Дата:  ",d.da_day,d.da_mon,d.da_year);
        fclose(fid_outcorr);

        FILE *fid_outcorr;
            fid_outcorr = fopen(newname.c_str(),"at");

        fprintf(fid_outcorr,"%s%s%s\n","[",name1,"]");
        if (CheckBox4->Checked)
            outfile(CORR1_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name2,"]");
        if (CheckBox5->Checked)
            outfile(CORR2_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name3,"]");
        if (CheckBox6->Checked)
            outfile(CORR3_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name4,"]");
        if (CheckBox7->Checked)
            outfile(CORR4_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name5,"]");
        if (CheckBox8->Checked)
            outfile(CORR5_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name6,"]");
        if (CheckBox9->Checked)
            outfile(CORR6_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name7,"]");
        if (CheckBox10->Checked)
            outfile(CORR7_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name8,"]");
        if (CheckBox11->Checked)
            outfile(CORR8_128);
        fprintf(fid_outcorr,"%s\n\n","");

        fprintf(fid_outcorr,"%s%s%s\n","[",name10,"]");
            outfile(CANT_128);

        fprintf(fid_outcorr,"%s%s%s\n","[",name11,"]");
            outfile(CoordX);

        fprintf(fid_outcorr,"%s%s%s\n","[",name12,"]");
            outfile(CoordY);

        fprintf(fid_outcorr,"%s%s%s\n","[",name13,"]");
        for(int i = 0; i < 31; i++)
        {
            fprintf(fid_outcorr,"%d\n",E1[i]);
        }

        fclose(fid_outcorr);
    }

    fclose(fid_outcorr);
*/
    return 0;
}

//---------------------------------------------------------------------------

void sul_tune::calculate_sphere(double SX, double SY, double R, double Lambda)
{
    double x = 0;
    double y = 0;
    int M = 0;

    for (int i=1;i<32;i++) {

        x = abs(16-i);

        for (int j=1;j<E1[i-1]+1;j++){

            if(fmod(i,2)==1) {
                y = abs(E1[i-1]/2-j+0.5);
            } else {
                y = abs((E1[i-1]-1)/2-j+1);
            }

            F_eval[M]= fmod(7200-(360*(sqrt(SX*SX*x*x+SY*SY*y*y+R*R)-R)/Lambda),360);
            M += 1;
        }
    }
}

//Описание функции загрузки выходного файла
//==========================================
/*
void TForm1::outfile(int Array[650])
{

int i=1, j;
int Z=0;
int nummod = 0;


        while (i<32)
    {
        j=1;

        while (j<E1[i-1]+1)
        {
            Z=Z+1;                     // номер по порядку
            int R= fmod(Z,128);
            if (R == 1)
            {
                nummod++;
                fprintf(fid_outcorr,"%s\n\n"," ");
                fprintf(fid_outcorr,"%s%d\n",";  модуль ",nummod);
            }

            if (j == E1[i-1])
            {
                fprintf(fid_outcorr,"%d%s\n",Array[Z-1]," ");
            }
            else
            {
                fprintf(fid_outcorr,"%d%s",Array[Z-1]," ");
            }
            j=j+1;

       }
       i=i+1;
    }
    fprintf(fid_outcorr,"%d%s",Array[connected_channels]," ");
    fprintf(fid_outcorr,"%d%s",Array[638]," ");
    fprintf(fid_outcorr,"%d%s",Array[639]," ");

    fprintf(fid_outcorr,"%s\n\n"," ");
 }
*/
//---------------------------------------------------------------------------
