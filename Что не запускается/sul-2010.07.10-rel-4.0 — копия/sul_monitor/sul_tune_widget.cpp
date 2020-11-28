
#include "sul_tune_widget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

sul_tune_widget::sul_tune_widget(int N, QWidget *parent, Qt::WFlags flags):
        QWidget(parent,flags)
{
    setWindowTitle(tr("Создание файла конфигурации"));

    n_sectors = N;

    bar = new QStatusBar();
    btnCreate = new QPushButton(tr("Расчет"));

    for(int i=0; i<n_sectors; i++) {
	cb[i].setText(tr("Корректура ") + QString::number(i+1));
    }

    QGridLayout *gl = new QGridLayout();

    QLabel *l1 = new QLabel(tr("Корректуры"));
    QLabel *l2 = new QLabel(tr("Фокус"));
    QLabel *l3 = new QLabel(tr("Шаг, dx"));
    QLabel *l4 = new QLabel(tr("Шаг, dy"));
    QLabel *l5 = new QLabel(tr("Длина\nволны"));

    gl->addWidget(l1,0,0);
    gl->addWidget(l2,0,1);
    gl->addWidget(l3,0,2);
    gl->addWidget(l4,0,3);
    gl->addWidget(l5,0,4);

    for(int i=0; i<n_sectors; i++) {

	gl->addWidget(&cb[i],i+1,0);
	gl->addWidget(&spbR[i],i+1,1);
	gl->addWidget(&spbX[i],i+1,2);
	gl->addWidget(&spbY[i],i+1,3);
	gl->addWidget(&spbL[i],i+1,4);
    }

    gl->addWidget(btnCreate,n_sectors+1,0,0);
    gl->addWidget(bar,n_sectors+2,0,1,5 );

    setLayout(gl);
}

//-----------------------------------------------------------------------------

sul_tune_widget::~sul_tune_widget()
{
    if(bar) delete bar;
    if(btnCreate) delete btnCreate;
}

//-----------------------------------------------------------------------------

void sul_tune_widget::create_config_file()
{
}

//-----------------------------------------------------------------------------
