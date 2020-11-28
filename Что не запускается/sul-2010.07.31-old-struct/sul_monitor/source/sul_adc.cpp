
#include "sul_adc.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

sul_adc_widget::sul_adc_widget(device *d, QWidget *parent, Qt::WFlags flags):
        QWidget(parent,flags)
{
    setWindowTitle(tr("Контроль СУЛ"));
    setWindowIcon(QIcon("icon\\question_icon.png"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hl1 = new QHBoxLayout();
    QHBoxLayout *hl2 = new QHBoxLayout();

    layout->setSpacing(4);
    label = new QLabel(tr("Абонент"));
    box = new QSpinBox();

    QGroupBox *gb1 = new QGroupBox(tr("Тип контроля"));
    rbtTestSingle = new QRadioButton(tr("Абонент"), this);
    rbtTestTotal = new QRadioButton(tr("Система"), this);
    rbtTestSingle->setChecked(true);
    rbtTestSingle->setAutoExclusive( true );
    rbtTestTotal->setAutoExclusive( true );
    hl1->addWidget(rbtTestSingle);
    hl1->addWidget(rbtTestTotal);
    gb1->setLayout(hl1);

    QGroupBox *gb2 = new QGroupBox(tr("Начальная фаза"));
    rbtViewFull = new QRadioButton(tr("Да"), this);
    rbtViewPart = new QRadioButton(tr("Нет"), this);
    rbtViewFull->setChecked(true);
    rbtViewFull->setAutoExclusive( true );
    rbtViewPart->setAutoExclusive( true );
    hl2->addWidget(rbtViewFull);
    hl2->addWidget(rbtViewPart);
    gb2->setLayout(hl2);

    btnChannelTest = new QPushButton(tr("Контроль каналов"));
    btnCalculatorTest = new QPushButton(tr("Контроль вычислителей"));
    btnPulseTest = new QPushButton(tr("Контроль импульсов"));
    btnFi0Test = new QPushButton(tr("Начальные фазы"));
    bar = new QStatusBar();

    dev = d;

    box->setValue(1);
    box->setMaximum(1);
    box->setMinimum(1);

    layout->addWidget(label);
    layout->addWidget(box);
    layout->addWidget(gb1);
    layout->addWidget(gb2);
    layout->addWidget(btnChannelTest);
    layout->addWidget(btnCalculatorTest);
    layout->addWidget(btnPulseTest);
    layout->addWidget(btnFi0Test);
    layout->addWidget(bar);

    connect(btnChannelTest,SIGNAL(clicked()),this,SLOT(test_channels()));
    connect(btnCalculatorTest,SIGNAL(clicked()),this,SLOT(test_calculators()));
    connect(btnPulseTest,SIGNAL(clicked()),this,SLOT(test_pulses()));
    connect(btnFi0Test,SIGNAL(clicked()),this,SLOT(test_fi0()));
    connect(box,SIGNAL(valueChanged(int)),this,SLOT(abonent_number_changed(int)));
}

//-----------------------------------------------------------------------------

sul_adc_widget::~sul_adc_widget()
{
}

//-----------------------------------------------------------------------------

void sul_adc_widget::test_channels()
{
        bar->showMessage(tr("Контроль каналов выполнен"));
}

//-----------------------------------------------------------------------------

void sul_adc_widget::test_calculators()
{
        bar->showMessage(tr("Контроль вычислителей выполнен"));
}

//-----------------------------------------------------------------------------

void sul_adc_widget::test_pulses()
{
	bar->showMessage(tr("Контроль импульсов выполнен"));
}

//-----------------------------------------------------------------------------

void sul_adc_widget::abonent_number_changed(int abonent)
{
    emit abonent_changed(abonent);
}

//-----------------------------------------------------------------------------

void sul_adc_widget::test_fi0()
{
    emit show_fi0();
}

//-----------------------------------------------------------------------------
