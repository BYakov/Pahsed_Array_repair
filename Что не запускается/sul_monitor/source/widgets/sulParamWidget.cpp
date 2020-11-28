
#include "sulParamWidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

//---------------------------------------------------------------

sul_param_widget::sul_param_widget(sul_base *s, QWidget *parent, Qt::WindowFlags flags):
        QWidget(parent,flags)
{
    std::cout << "sul_param_widget::sul_param_widget()" <<  endl;

    setWindowTitle(tr("Параметры конфигурации СУЛ"));
    setWindowIcon(QIcon("config\\icon\\question_icon.png"));

    bar = NULL;
    sul = s;

    struct channel_info ci;
    sul->sul_channel_info(0,ci);

    int total_param = sul->sul_total_parameters();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(4);

    QGroupBox *gb = new QGroupBox(tr("Парметры канала"));
    QVBoxLayout *l = new QVBoxLayout(gb);

    for(int i=0; i<total_param; i++) {
            channelParam.push_back(new QRadioButton(tr(sul->sul_parameter_name(i))));
            l->addWidget(channelParam.at(i));
    }

    for(unsigned i=0; i<channelParam.size(); i++)
        connect(channelParam.at(i),SIGNAL(clicked()),this,SLOT(show_parameter()));

    bar = new QStatusBar();

    QGroupBox *gb1 = new QGroupBox(tr("Файл конфигурации"));
    QVBoxLayout *l1 = new QVBoxLayout(gb1);

    for(int i=0; i<sul->sul_flash_segment_count(); i++) {
        spaceParam.push_back(new QRadioButton(tr(sul->sul_flash_segment_name(i))));
        l1->addWidget(spaceParam.at(i));
    }

    for(unsigned i=0; i<spaceParam.size(); i++)
        connect(spaceParam.at(i),SIGNAL(clicked()),this,SLOT(space_parameter()));

    layout->addWidget(gb);
    layout->addWidget(gb1);

    QVBoxLayout *ll = new QVBoxLayout();
    ll->addLayout(layout);
    ll->addWidget(bar);

    setLayout(ll);

    adjustSize();
}

//-----------------------------------------------------------------------------

sul_param_widget::~sul_param_widget()
{
    close();
    for(unsigned i=0; i<channelParam.size(); i++)
        delete channelParam.at(i);
    channelParam.clear();
    delete bar;
    std::cout << "sul_param_widget::~sul_param_widget()" <<  endl;
}

//-----------------------------------------------------------------------------

void sul_param_widget::show_parameter()
{
    if(!sul) return;

    int param_number = -1;

    for(unsigned i=0; i<channelParam.size(); i++) {
        if(channelParam.at(i)->isChecked()) {
            param_number = i;
            break;
        }
    }

    if(param_number < 0) {
        std::cout << "sul_param_widget::sul_param_widget(): No parameters found!" <<  endl;
        return;
    } else {
        std::cout << "sul_param_widget::sul_param_widget(): "
             << sul->sul_parameter_name(param_number) <<  endl;
    }

    emit show_array_parameter(param_number);

    bar->showMessage(tr(sul->sul_parameter_name(param_number)) + tr(": Ok"));
}

//-----------------------------------------------------------------------------

void sul_param_widget::space_parameter()
{
    if(!sul) return;

    int space_param_number = -1;

    for(unsigned i=0; i<spaceParam.size(); i++) {
        if(spaceParam.at(i)->isChecked()) {
            space_param_number = i;
            break;
        }
    }

    if(space_param_number < 0) {
        std::cout << "sul_param_widget::space_parameter(): No space parameters found!" <<  endl;
        return;
    } else {
        std::cout << "sul_param_widget::space_parameter(): "
             << sul->sul_flash_segment_name(space_param_number) <<  endl;
    }

    emit show_space_parameter(space_param_number);

    bar->showMessage(tr(sul->sul_flash_segment_name(space_param_number)) + tr(": Ok"));
}

//-----------------------------------------------------------------------------
