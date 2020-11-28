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

sul_create_config::sul_create_config(int sul_channels)
{
    total_channels = sul_channels;

    CoordX = new int[total_channels];
    CoordY = new int[total_channels];
    calc_array = new double[total_channels];
    F0 = new double[total_channels];
    Slope = new double[total_channels];

    for(unsigned i=0; i<sizeof(E1)/sizeof(E1[0]); i++)
        connected_channels += E1[i];
}

//---------------------------------------------------------------------------

sul_create_config::~sul_create_config()
{
    if(CoordX) delete[] CoordX;
    if(CoordY) delete[] CoordY;
    if(calc_array) delete[] calc_array;
    if(F0) delete [] F0;
    if(Slope) delete [] Slope;
}

//---------------------------------------------------------------------------

int sul_create_config::calculate_xy()
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

    CoordX[637] = 0;
    CoordX[638] = 0;
    CoordX[639] = 0;

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

    CoordY[637] = 0;
    CoordY[638] = 0;
    CoordY[639] = 0;

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

            cout << s.c_str() << " " ;

            Slope[total] = value;

            total++;

            cout << endl;
    }

    cout << hex << "total : " << total << endl;
    cout << dec << endl;

    ifs.close();

    if(total > connected_channels)
        return false;

    return true;
}

bool sul_create_config::read_f0_file(const char *fname)
{
    return false;
}
/*
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Label10->Caption = "";
    Label13->Caption = "";
    Label24->Caption = "";
    Label27->Caption = "";
    Label28->Caption = "";
    Label30->Caption = "";
    Label13->Font->Color = clWindowText;
    Label24->Font->Color = clBlue;
    Label30->Font->Color = clRed;
    Lambda1 = Edit1->Text.ToDouble();
    Lambda2 = Edit2->Text.ToDouble();
    Lambda3 = Edit3->Text.ToDouble();
    Lambda4 = Edit5->Text.ToDouble();
    Lambda5 = Edit8->Text.ToDouble();
    Lambda6 = Edit9->Text.ToDouble();
    Lambda7 = Edit10->Text.ToDouble();
    Lambda8 = Edit11->Text.ToDouble();
    Kcant = Edit17->Text.ToDouble();
    R1 = Edit4->Text.ToDouble();
    R2 = Edit14->Text.ToDouble();
    R3 = Edit15->Text.ToDouble();
    R4 = Edit16->Text.ToDouble();
    R5 = Edit18->Text.ToDouble();
    R6 = Edit19->Text.ToDouble();
    R7 = Edit20->Text.ToDouble();
    R8 = Edit21->Text.ToDouble();
    SX1 = Edit6->Text.ToDouble();
    SX2 = Edit22->Text.ToDouble();
    SX3 = Edit23->Text.ToDouble();
    SX4 = Edit24->Text.ToDouble();
    SX5 = Edit25->Text.ToDouble();
    SX6 = Edit26->Text.ToDouble();
    SX7 = Edit27->Text.ToDouble();
    SX8 = Edit28->Text.ToDouble();
    SY1 = Edit7->Text.ToDouble();
    SY2 = Edit29->Text.ToDouble();
    SY3 = Edit30->Text.ToDouble();
    SY4 = Edit31->Text.ToDouble();
    SY5 = Edit32->Text.ToDouble();
    SY6 = Edit33->Text.ToDouble();
    SY7 = Edit34->Text.ToDouble();
    SY8 = Edit35->Text.ToDouble();
    F0_add = Edit36->Text.ToDouble();
    AnsiString newname = Edit12->Text;

    err = false;
    AnsiString msg9 = "", msg10 = "";

    if ((fid_inf0 = fopen("inf0.txt","rt"))== NULL)
    {
        err = true;
        msg9 = "inf0.txt,";
    }
    if ((fid_incant = fopen("incant.txt","rt"))== NULL)
    {
        err = true;
        msg10 = "incant.txt";
    }

    if ((msg9 != "" || msg10 != ""))
    {
        Label24->Caption="Не могу прочитать исходные файлы:";
        Label30->Caption = msg9 + " " + msg10;
        Label13->Caption = "Проверьте наличие файлов";
        Label10->Caption = "Ошибка !!!";

        Label13->Font->Color = clRed;

        fclose(fid_incant);
        fclose(fid_inf0);
        err = true;
    }
    // Проверяем правильность исходных файлов и производим
    //загрузку массивов

    sfera(lambda,SX1,SY1,R1,Lambda1);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR1[k] = F_eval[k];
    }


    sfera(lambda,SX2,SY2,R2,Lambda2);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR2[k] = F_eval[k];
    }

    sfera(lambda,SX3,SY3,R3,Lambda3);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR3[k] = F_eval[k];
    }

    sfera(lambda,SX4,SY4,R4,Lambda4);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR4[k] = F_eval[k];
    }

    sfera(lambda,SX5,SY5,R5,Lambda5);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR5[k] = F_eval[k];
    }

    sfera(lambda,SX6,SY6,R6,Lambda6);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR6[k] = F_eval[k];
    }

    sfera(lambda,SX7,SY7,R7,Lambda7);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR7[k] = F_eval[k];
    }

    sfera(lambda,SX8,SY8,R8,Lambda8);                                                  //вычисляем сферу
    for (int k = 0; k < 637; k++)
    {
        CORR8[k] = F_eval[k];
    }

    int r=0, g=0, m=0;
    if (!err)
    {
        while (g != -1 && r < 638)
        {
            g = fscanf(fid_inf0, "%f", &F0[r]);
            r++;
            if (g != -1)
                m++;
        }
            if(m != 637)
        {
            msg9 = "inf0.txt";
            err = true;
        }
    }

    r=0; g=0; m=0;
    if (!err)
    {
        while (g != -1 && r < 638)
        {
            g = fscanf(fid_incant, "%f", &CANT[r]);
            r++;
            if (g != -1)
                m++;
        }
        if(m != 637)
        {
            msg10 = "incant.txt";
            err = true;
        }
    }

    if (msg9 != "" || msg10 != "")
    {
        Label27->Caption = "Не верен формат исходных файлов:";
        Label28->Caption = msg9 + " " + msg10;
        Label27->Font->Color=clRed;
        Label28->Font->Color=clRed;
    }
    fclose(fid_incant);
    fclose(fid_inf0);

    if (CheckBox4->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR1_F0[k] = fmod(720+CORR1[k]-F0[k]+F0_add,360);
            CORR1_128[k] = floor(CORR1_F0[k]*127/360);     //отбрасываем дробную часть
        }
    }
    if (CheckBox5->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR2_F0[k] = fmod(720+CORR2[k]-F0[k]+F0_add,360);
            CORR2_128[k] = floor(CORR2_F0[k]*127/360);
        }
    }
    if (CheckBox6->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR3_F0[k] = fmod(720+CORR3[k]-F0[k]+F0_add,360);
            CORR3_128[k] = floor(CORR3_F0[k]*127/360);
        }
    }
    if (CheckBox7->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR4_F0[k] = fmod(720+CORR4[k]-F0[k]+F0_add,360);
            CORR4_128[k] = floor(CORR4_F0[k]*127/360);
        }
    }
    if (CheckBox8->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR5_F0[k] = fmod(720+CORR5[k]-F0[k]+F0_add,360);
            CORR5_128[k] = floor(CORR5_F0[k]*127/360);
        }
    }
    if (CheckBox9->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR6_F0[k] = fmod(720+CORR6[k]-F0[k]+F0_add,360);
            CORR6_128[k] = floor(CORR6_F0[k]*127/360);
        }
    }
    if (CheckBox10->Checked)
    {
        for (int k=0; k<637;k++)
        {
            CORR7_F0[k] = fmod(720+CORR7[k]-F0[k]+F0_add,360);
            CORR7_128[k] = floor(CORR7_F0[k]*127/360);
        }
    }
    if (CheckBox11->Checked)
    {
        for (int k = 0; k < 637; k++)
        {
            CORR8_F0[k] = fmod(720 + CORR8[k] - F0[k] + F0_add, 360);
            CORR8_128[k] = floor(CORR8_F0[k]*127/360);
        }
    }

    for (int k = 0; k < 637; k++)
    {
        if (CANT[k] > 0)
            CANT_128[k] = floor(17.15*Kcant*64/CANT[k]);
        else
            CANT_128[k] = 0;
    }


//=========================================================
// Создаем файл для занесения в СУЛ
//=========================================================

    AnsiString name1 = "CORR1_F0";
    AnsiString name2 = "CORR2_F0";
    AnsiString name3 = "CORR3_F0";
    AnsiString name4 = "CORR4_F0";
    AnsiString name5 = "CORR5_F0";
    AnsiString name6 = "CORR6_F0";
    AnsiString name7 = "CORR7_F0";
    AnsiString name8 = "CORR8_F0";
    AnsiString name10 = "CANT";
    AnsiString name11 = "CoordX";
    AnsiString name12 = "CoordY";
    AnsiString name13 = "LINES";

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

        Label13->Caption="Файл '"+newname+"' сформирован";
        Label13->Font->Color=100;
    }

    fclose(fid_outcorr);
}
*/
//++++++++++++++++++ СВОИ ФУНКЦИИ +++++++++++++++++

//---------------------------------------------------------------------------

void sul_create_config::calculate_sphere(double SX, double SY, double R, double Lambda)
{
    double x = 0;
    double y = 0;
    int M = 0;

    for (int i=1;i<32;i++){

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
    fprintf(fid_outcorr,"%d%s",Array[637]," ");
    fprintf(fid_outcorr,"%d%s",Array[638]," ");
    fprintf(fid_outcorr,"%d%s",Array[639]," ");

    fprintf(fid_outcorr,"%s\n\n"," ");
 }
*/
//---------------------------------------------------------------------------



