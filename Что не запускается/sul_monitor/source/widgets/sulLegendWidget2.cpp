#ifndef SUL_LEGEND_WIDGET2_H
    #include "sulLegendWidget2.h"
#endif

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

sul_legend_widget2::sul_legend_widget2(sul_base *system, QWidget *parent, Qt::WindowFlags flags):
        QWidget(parent,flags)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    setWindowTitle(tr("Информация о канале"));

    sul = system;

    QGridLayout *gl = new QGridLayout();

    // отображение параметров канала
    for(int i=0; i<sul->sul_total_parameters(); i++) {
        lp.push_back(new QLabel(tr(sul->sul_parameter_name(i))));
        lv.push_back(new QLabel(tr("0")));

        gl->addWidget(lp[i],i,0);
        gl->addWidget(lv[i],i,1);
    }

    setLayout(gl);

    cout << "sul_legend_widget2::sul_legend_widget2()" << endl;
}

//-----------------------------------------------------------------------------

sul_legend_widget2::~sul_legend_widget2()
{
    for(unsigned i=0; i<lp.size(); i++) {
        delete lp.at(i);
        delete lv.at(i);
    }
    lp.clear();
    lv.clear();
    cout << "sul_legend_widget2::~sul_legend_widget2()" << endl;
}

//-----------------------------------------------------------------------------

void sul_legend_widget2::updateScreen(struct channel_info& info)
{
    int param_id = 0;

    for(unsigned i=0; i<info.phase0.size(); i++) {
        lv.at(param_id++)->setText(QString::number(info.phase0.at(i)));
    }

    for(unsigned i=0; i<info.gain0.size(); i++) {
        lv.at(param_id++)->setText(QString::number(info.gain0.at(i)));
    }

    for(unsigned i=0; i<info.extra.size(); i++) {
        lv.at(param_id++)->setText(QString::number(info.extra.at(i)));
    }

    repaint();
}

//-----------------------------------------------------------------------------
