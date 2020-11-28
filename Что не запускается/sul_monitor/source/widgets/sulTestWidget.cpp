
#include "sulTestWidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#ifndef __linux__
#include <windows.h>
#endif

using namespace std;

//---------------------------------------------------------------

sul_test_widget::sul_test_widget(sul_base *s, QWidget *parent, Qt::WindowFlags flags):
        QWidget(parent,flags)
{
    setWindowTitle(tr("Контроль СУЛ"));
    setWindowIcon(QIcon("config\\icon\\question_icon.png"));

    sul = s;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hl1 = new QHBoxLayout();
    QHBoxLayout *hl2 = new QHBoxLayout();
    QHBoxLayout *hl3 = new QHBoxLayout();
    QVBoxLayout *vl2 = new QVBoxLayout();

    layout->setSpacing(4);
    hl2->addWidget(new QLabel(tr("Абонент")));
    hl2->addWidget(new QLabel(tr("Адрес абонента")));
    box = new QSpinBox();
    labelAddr = new QLabel(tr("       0x0 / 0"));
    hl3->addWidget(box);
    hl3->addWidget(labelAddr);

    QGroupBox *gb1 = new QGroupBox(tr("Тип контроля"));
    rbtTestSingle = new QRadioButton(tr("Абонент"), this);
    rbtTestTotal = new QRadioButton(tr("Система"), this);
    rbtTestSingle->setChecked(false);
    rbtTestSingle->setAutoExclusive( true );
    rbtTestTotal->setChecked(true);
    rbtTestTotal->setAutoExclusive( true );
    hl1->addWidget(rbtTestSingle);
    hl1->addWidget(rbtTestTotal);
    gb1->setLayout(hl1);

    QGroupBox *gb2 = new QGroupBox(tr("Выбор теста"));
    for(unsigned i=0; i<sul->sul_test_available(); i++) {
        rbSelectedTest.push_back(new QRadioButton(tr(sul->sul_test_name(i))));
        vl2->addWidget(rbSelectedTest.at(i));
    }
    pbStartTest = new QPushButton(tr("Старт"));
    connect(pbStartTest,SIGNAL(clicked()),this,SLOT(start_test()));
    vl2->addWidget(pbStartTest);
    gb2->setLayout(vl2);

    bar = new QStatusBar();

    box->setValue(0);
    box->setMinimum(0);
    box->setMaximum(sul->sul_total_abonents()-1);

    //layout->addWidget(label);
    layout->addLayout(hl2);
    layout->addLayout(hl3);
    //layout->addWidget(box);
    layout->addWidget(gb1);
    layout->addWidget(gb2);

    layout->addWidget(bar);

    connect(box,SIGNAL(valueChanged(int)),this,SLOT(abonent_number_changed(int)));

    adjustSize();

    cout << "sul_test_widget::sul_test_widget()" <<  endl;
}

//-----------------------------------------------------------------------------

sul_test_widget::~sul_test_widget()
{
    for(unsigned i=0; i<rbSelectedTest.size(); i++)
        delete rbSelectedTest.at(i);
    rbSelectedTest.clear();
    delete pbStartTest;
    cout << "sul_test_widget::~sul_test_widget()" <<  endl;
}

//-----------------------------------------------------------------------------

void sul_test_widget::start_test()
{
    if(!sul) return;

    int test_number = -1;

    for(unsigned i=0; i<sul->sul_test_available(); i++) {
        if(rbSelectedTest.at(i)->isChecked()) {
            test_number = i;
            break;
        }
    }

    cout << "sul_test_widget::test(" << test_number << "): " << sul->sul_test_name(test_number) <<  endl;

    int err = 0;
    int res = 0;
    if(rbtTestSingle->isChecked()) {

	int abonent_index = box->value();

        bar->showMessage(tr(sul->sul_test_name(test_number)) +
			 ": " + QString::number(abonent_index));

	res = sul->sul_test(abonent_index, test_number);
	if(res < 0) {

            bar->showMessage(tr("Абонент ") +
			     QString::number(abonent_index) +
                             tr(": ") +
                             tr("Ошибка"));
            return;

        } else {

	    emit abonent_test_complete(test_number+1);
        }

    } else {

	//for(unsigned abonent_index=0; abonent_index < sul->sul_active_abonents(); abonent_index++) {
        for(unsigned abonent_index=0; abonent_index < sul->sul_total_abonents(); abonent_index++) {

	    bar->showMessage(sul->sul_test_name(test_number) +
                             tr(": Абонент ") +
			     QString::number(abonent_index));

	    res = sul->sul_test(abonent_index, test_number);
	    if(res < 0) {

		bar->showMessage(tr("Абонент ") +
				 QString::number(test_number) +
                                 tr(": ") +
                                 tr("Ошибка"));
                continue;

            } else {

		emit abonent_test_complete(test_number+1);
            }

	    Sleep(1);
        }
    }

    if(err == 0)
	bar->showMessage(tr(sul->sul_test_name(test_number)) + tr(": Ok"));
    else
	bar->showMessage(tr(sul->sul_test_name(test_number)) + tr(": Ошибка!"));
}

//-----------------------------------------------------------------------------

void sul_test_widget::abonent_number_changed(int abnent_index)
{
    labelAddr->setText(tr("       0x") +
                       QString::number(sul->sul_abonent_address(abnent_index),16) +
                       tr(" / ") +
                       QString::number(sul->sul_abonent_address(abnent_index)));
    emit abonent_changed(abnent_index);
}

//-----------------------------------------------------------------------------
