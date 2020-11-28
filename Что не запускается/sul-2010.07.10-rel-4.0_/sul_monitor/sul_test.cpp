
#include "sul_test.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

sul_test_widget::sul_test_widget(sul_base *s, QWidget *parent, Qt::WFlags flags):
        QWidget(parent,flags)
{
    setWindowTitle(tr("�������� ���"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hl1 = new QHBoxLayout();
    QHBoxLayout *hl2 = new QHBoxLayout();

    layout->setSpacing(4);
    label = new QLabel(tr("�������"));
    box = new QSpinBox();

    QGroupBox *gb1 = new QGroupBox(tr("��� ��������"));
    rbtTestSingle = new QRadioButton(tr("�������"), this);
    rbtTestTotal = new QRadioButton(tr("�������"), this);
    rbtTestSingle->setChecked(true);
    rbtTestSingle->setAutoExclusive( true );
    rbtTestTotal->setAutoExclusive( true );
    hl1->addWidget(rbtTestSingle);
    hl1->addWidget(rbtTestTotal);
    gb1->setLayout(hl1);

    QGroupBox *gb2 = new QGroupBox(tr("��������� ����"));
    rbtViewFull = new QRadioButton(tr("��"), this);
    rbtViewPart = new QRadioButton(tr("���"), this);
    rbtViewFull->setChecked(true);
    rbtViewFull->setAutoExclusive( true );
    rbtViewPart->setAutoExclusive( true );
    hl2->addWidget(rbtViewFull);
    hl2->addWidget(rbtViewPart);
    gb2->setLayout(hl2);

    btnChannelTest = new QPushButton(tr("�������� �������"));
    btnCalculatorTest = new QPushButton(tr("�������� ������������"));
    btnPulseTest = new QPushButton(tr("�������� ���������"));
    btnFi0Test = new QPushButton(tr("��������� ����"));
    bar = new QStatusBar();

    sul = s;

    box->setValue(1);
    box->setMaximum(sul->sul_active_abonents());
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

sul_test_widget::~sul_test_widget()
{
}

//-----------------------------------------------------------------------------

void sul_test_widget::test_channels()
{
    if(!sul) return;

    if(rbtTestSingle->isChecked()) {

        int abonent = box->value();

	bar->showMessage(tr("�������� �������: ������� ") + QString::number(abonent));

        if(sul->sul_test_channels(abonent) < 0) {
            bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
            return;
        }

        bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("�������� ��������"));

        emit show_analizer_channels();

    } else {

        for(int abonent=1; abonent<sul->sul_active_abonents() + 1; abonent++) {

	    bar->showMessage(tr("�������� �������: ������� ") + QString::number(abonent));

            if(sul->sul_test_channels(abonent) < 0) {
                bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
                return;
            }

	    emit show_grid_channels();

	    Sleep(100);
        }

        bar->showMessage(tr("�������� ������� ��������"));
    }
}

//-----------------------------------------------------------------------------

void sul_test_widget::test_calculators()
{
    if(!sul) return;

    if(rbtTestSingle->isChecked()) {

        int abonent = box->value();

	bar->showMessage(tr("�������� ������������: ������� ") + QString::number(abonent));

        if(sul->sul_test_calculators(abonent) < 0) {
                bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
                return;
        }

        bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("�������� ��������"));

        emit show_analizer_calculators(rbtViewFull->isChecked());

    } else {

        for(int abonent=1; abonent < sul->sul_active_abonents() + 1; abonent++) {

	    bar->showMessage(tr("�������� ������������: ������� ") + QString::number(abonent));

            if(sul->sul_test_calculators(abonent) < 0) {
                    bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
                    return;
            }

	    emit show_grid_calculators(rbtViewFull->isChecked());

	    Sleep(100);
        }

        bar->showMessage(tr("�������� ������������ ��������"));
    }
}

//-----------------------------------------------------------------------------

void sul_test_widget::test_pulses()
{
    if(!sul) return;

    if(rbtTestSingle->isChecked()) {

	int abonent = box->value();

	bar->showMessage(tr("�������� ���������: ������� ") + QString::number(abonent));

	if(sul->sul_test_pulses(abonent) < 0) {
		bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
		return;
	}

	bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("�������� ��������"));

	emit show_analizer_pulses();

    } else {

	for(int abonent=1; abonent < sul->sul_active_abonents() + 1; abonent++) {

	    bar->showMessage(tr("�������� ���������: ������� ") + QString::number(abonent));

	    if(sul->sul_test_pulses(abonent) < 0) {
		    bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
		    return;
	    }

	    emit show_grid_pulses();

	    Sleep(100);
	}

	bar->showMessage(tr("�������� ��������� ��������"));
    }
}

//-----------------------------------------------------------------------------
/*
void sul_test_widget::test_exchange()
{
    if(!sul) return;

    int abonent = box->value();
    int size = sul->sul_total_channels(abonent);

    unsigned char *buffer = (unsigned char *)malloc(size);
    if(!buffer)
        return;

    for(int i=0; i<size; i++)
        buffer[i] = i + 1;

    if(rbtTestSingle->isChecked()) {

        //cout << "sul_test_widget::test_exchange() - abonent " << abonent << endl;

        if(sul->sul_test_exchange(abonent, buffer, size) < 0) {
                //cout << "sul_test_widget::test_exchange() - Error" << endl;
                free(buffer);
                bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
                return;
        }

        bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("�������� ��������"));

    } else {

        for(int abonent=1; abonent < sul->sul_active_abonents() + 1; abonent++) {

            //cout << "sul_test_widget::test_exchange() - abonent " << abonent << endl;

            if(sul->sul_test_exchange(abonent, buffer, size) < 0) {
                    //cout << "sul_test_widget::test_exchange() - Error" << endl;
                    free(buffer);
                    bar->showMessage(tr("������� ") + QString::number(abonent) + tr(": ") + tr("������ ��������"));
                    return;
            }
        }

        bar->showMessage(tr("�������� ������ ��������"));
        free(buffer);
    }

    emit show_exchange_test();
}
*/
//-----------------------------------------------------------------------------

void sul_test_widget::abonent_number_changed(int abonent)
{
    emit abonent_changed(abonent);
}

//-----------------------------------------------------------------------------

void sul_test_widget::test_fi0()
{
    emit show_fi0();
}

//-----------------------------------------------------------------------------
