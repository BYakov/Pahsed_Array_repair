#ifndef LEGEND_WIDGET_H
    #include "legendwidget.h"
#endif

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

legend_widget::legend_widget(QWidget *parent, Qt::WindowFlags flags):
        QWidget(parent,flags)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    //setWindowTitle(tr("Информация о канале"));

    QGridLayout *gl = new QGridLayout();

    // отображение основных параметров канала
    paramName.push_back(new QLabel(tr("Имя 1")));
    paramName.push_back(new QLabel(tr("Имя 2")));

    paramValue.push_back(new QLabel(tr("Значение 1")));
    paramValue.push_back(new QLabel(tr("Значение 2")));

    for(unsigned i=0; i<paramName.size(); i++) {
	gl->addWidget(paramName[i],i,0);
	gl->addWidget(paramValue[i],i,1);
    }

    setLayout(gl);

    cout << "legend_widget::legend_widget()" << endl;
}

//-----------------------------------------------------------------------------

legend_widget::~legend_widget()
{
    close();
    for(unsigned i=0; i<paramName.size(); i++) {
	delete paramName.at(i);
	delete paramValue.at(i);
    }
    paramValue.clear();
    paramName.clear();
    cout << "legend_widget::~legend_widget()" << endl;
}

//-----------------------------------------------------------------------------

void legend_widget::updateParam(unsigned param_id, QString name, QString value)
{
    if(param_id >= paramName.size())
	return;

    paramName.at(param_id)->setText(name);
    paramValue.at(param_id)->setText(value);

    repaint();
}

//-----------------------------------------------------------------------------
