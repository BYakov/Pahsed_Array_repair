#ifndef SUL_LEGEND_WIDGET1_H
    #include "sulLegendWidget1.h"
#endif

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

sul_legend_widget1::sul_legend_widget1(sul_base *system, QWidget *parent, Qt::WindowFlags flags):
        QWidget(parent,flags)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    //setWindowTitle(tr("Информация о канале"));

    sul = system;

    QGridLayout *gl = new QGridLayout();

    // отображение основных параметров канала
    for(int i=0; i<sul->sul_total_parameters(); i++) {
        lp.push_back(new QLabel(tr(sul->sul_parameter_name(i))));
        lv.push_back(new QLabel(tr("0")));

        gl->addWidget(lp[i],i,0);
        gl->addWidget(lv[i],i,1);
    }

    setLayout(gl);

    cout << "sul_legend_widget1::sul_legend_widget1()" << endl;
}

//-----------------------------------------------------------------------------

sul_legend_widget1::~sul_legend_widget1()
{
    for(unsigned i=0; i<lp.size(); i++) {
        delete lp.at(i);
        delete lv.at(i);
    }
    lp.clear();
    lv.clear();
    cout << "sul_legend_widget1::~sul_legend_widget1()" << endl;
}

//-----------------------------------------------------------------------------

void sul_legend_widget1::updateScreen(struct channel_info& info)
{
    for(int i=0; i<sul->sul_total_parameters(); i++) {
        struct parameter_t* param = sul->sul_get_parameter(i);
        lv.at(i)->setText(QString::number(param->data));
    }
    repaint();
}

//-----------------------------------------------------------------------------
