#include "antenna.h"
#include "ui_antenna.h"

//-----------------------------------------------------------------------------

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

antenna::antenna(sul_base *sul, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::antenna), m_sul(sul)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    ui->setupUi(this);

    setWindowTitle(QString::fromUtf8("Антенная решетка"));

    memset(&m_channel,0,sizeof(struct channel_t));

    m_parameters.clear();
    update_channel_info();
    m_param_id = -1;
    m_bar = statusBar();
    ui->progressBar->reset();
    ui->progressBar->setValue(0);
    m_thread = new task_thread();
    m_array = 0;

    setup_sul();
    show_param();

    std::cout << "antenna::antenna()" << endl;
}

//---------------------------------------------------------------------------------------

antenna::~antenna()
{
    close();
    if(m_array) delete m_array;
    m_parameters.clear();
    if(m_thread) {
        m_thread->stop();
        m_thread->wait(100);
        delete m_thread;
    }
    if(m_legend) delete m_legend;
    delete ui;
}

//---------------------------------------------------------------------------------------

void antenna::setup_sul()
{
    for(unsigned i=0; i<m_sul->sul_test_available(); i++) {
        QString name = QString::fromUtf8(m_sul->sul_test_name(i));
        ui->cbSelecetTest->addItem(name);
        ui->cbShowParam->addItem(name);
    }

    for(int i=0; i<m_sul->sul_flash_segment_count(); i++) {
        ui->cbShowParam->addItem(QString::fromUtf8(m_sul->sul_flash_segment_name(i)));
    }

    for(int i=0; i<m_sul->sul_ram_segment_count(); i++) {
        ui->cbShowParam->addItem(QString::fromUtf8("RAM ") + QString::number(i));
    }

    if(m_array) return;

    m_legend = new set_channel_phase(m_sul,NULL,Qt::Popup);
    m_array = new array_antenna(m_sul->sul_x_data(), m_sul->sul_y_data(), ui->widget);

    connect(ui->cbSelecetTest,SIGNAL(activated(int)),this,SLOT(select_test()));
    connect(ui->cbShowParam,SIGNAL(activated(int)),this,SLOT(show_param()));
    connect(ui->pbStartTest,SIGNAL(clicked()),this,SLOT(start_test()));
    connect(ui->spbAbonentIndex,SIGNAL(valueChanged(int)),this,SLOT(index_change(int)));
    connect(ui->cbSingleAbonent,SIGNAL(clicked(bool)),this,SLOT(set_test_mode(bool)));
    connect(ui->pbDebug,SIGNAL(clicked()),this,SLOT(debug_slot()));

    connect(ui->cbShowText,SIGNAL(clicked(bool)),m_array,SLOT(setShowTextFlag(bool)));
    connect(ui->elementSize,SIGNAL(valueChanged(int)),m_array,SLOT(elementSizeChange(int)));
    connect(m_array,SIGNAL(mousePressed(int,int,QMouseEvent*)),this,SLOT(mouse_pressed(int,int,QMouseEvent*)));
    connect(this,SIGNAL(selected_channel(channel_t)),m_array,SLOT(selectedChannelChange(channel_t)));
    connect(this,SIGNAL(repaint_antenna()),m_array,SLOT(repaintWidget()));

    ui->antennaLayout->addWidget(m_array);
    ui->cbShowParam->setCurrentIndex(0);
    ui->spbAbonentIndex->setMaximum(m_sul->sul_total_abonents()-1);
    ui->spbAbonentIndex->setMinimum(0);

    m_array->elementSizeChange(ui->elementSize->value());
}

//---------------------------------------------------------------------------------------

void antenna::mouse_pressed(int X, int Y, QMouseEvent *event)
{
    std::cout << "antenna::mouse_pressed(): " << X << " , " << Y << endl;

    if(m_sul->sul_channel_info(X, Y, m_channel) < 0) {
        statusBar()->showMessage(tr("No channel with: ") + tr("X = ") + QString::number(X) + tr(", Y = ") + QString::number(Y));
        std::cout << "antenna::mouse_pressed(): No channel found" << endl;
        memset(&m_channel, 0, sizeof(struct channel_t));
        emit selected_channel(m_channel);
        return;
    }

    statusBar()->showMessage(tr("X = ") + QString::number(X) + tr(", Y = ") + QString::number(Y));

    std::cout << "antenna::mouse_pressed(): Module " << m_channel.entry.M << ", channel " << m_channel.entry.N << endl;

    update_channel_info();

    emit selected_channel(m_channel);

    if(event->button() == Qt::RightButton) {

        m_legend->updateScreen(m_channel);

        m_legend->setGeometry(geometry().x()+event->x()+30,
                              geometry().y()+event->y()+15,
                              m_legend->geometry().width(),
                              m_legend->geometry().height());

        m_legend->adjustSize();
        m_legend->show();
    }
}

//---------------------------------------------------------------------------------------

void antenna::update_channel_info()
{
    ui->lb_lineNumber->setText(QString::number(m_channel.entry.line_number));
    ui->lb_moduleNumber->setText(QString::number(m_channel.entry.M));
    ui->lb_connNumber->setText(tr("X")+QString::number(m_channel.entry.X));
    ui->lb_moduleChNumber->setText(QString::number(m_channel.entry.number_on_module));
    ui->lb_antennaChNumber->setText(QString::number(m_channel.entry.N));
    ui->lb_X->setText(QString::number(m_channel.entry.x_grid));
    ui->lb_Y->setText(QString::number(m_channel.entry.y_grid));
    ui->lb_lineChNumber->setText(QString::number(m_channel.entry.number_on_line));
    ui->lb_factoryNumber->setText(QString::number(m_channel.entry.factory_number));
}

//---------------------------------------------------------------------------------------

void antenna::update_screen()
{
    std::cout << __FUNCTION__ << std::endl;
    emit repaint_antenna();
    show_param();
}

//---------------------------------------------------------------------------------------

int antenna::show_param()
{
    int idx = ui->cbShowParam->currentIndex();
    int const_count = 6;
    int test_count = m_sul->sul_test_available();
    int flash_count = m_sul->sul_flash_segment_count();

    if(idx < const_count) {
        return show_const_param();
    }
    if((idx >= const_count) && (idx < (const_count + test_count))) {
        return show_test_param();
    }
    if(idx >= const_count + test_count && (idx < (const_count + test_count + flash_count))) {
        return show_flash_param();
    }
    if(idx >= (const_count + test_count + flash_count)) {
        return show_ram_param();
    }

    return 0;
}

//---------------------------------------------------------------------------------------

int antenna::show_const_param()
{
    struct channel_t C;

    const std::vector<double>& X = m_sul->sul_x_data();
    const std::vector<double>& Y = m_sul->sul_y_data();

    int param_id = ui->cbShowParam->currentIndex();

    m_parameters.clear();

    for(int i=0; i<m_sul->sul_total_channels(); i++) {

        if(m_sul->sul_channel_info(X.at(i), Y.at(i), C) < 0)
            continue;

        switch(param_id) {
        case 0:
            m_parameters.push_back(C.entry.number_on_module);
            break;
        case 1:
            m_parameters.push_back(C.entry.number_on_line);
            break;
        case 2:
            m_parameters.push_back(C.entry.phase0);
            break;
        case 3:
            m_parameters.push_back(C.entry.slope);
            break;
        case 4:
            m_parameters.push_back(C.entry.x_grid);
            break;
        case 5:
            m_parameters.push_back(C.entry.y_grid);
            break;
        }
    }

    m_array->setParameters(&m_parameters);
    m_array->repaint();

    return 1;
}

//---------------------------------------------------------------------------------------


int antenna::show_test_param()
{
    m_param_id = ui->cbShowParam->currentIndex()-6;

    struct channel_t C;

    const std::vector<double>& X = m_sul->sul_x_data();
    const std::vector<double>& Y = m_sul->sul_y_data();

    m_parameters.clear();

    for(int i=0; i<m_sul->sul_total_channels(); i++) {

        if(m_sul->sul_channel_info(X.at(i), Y.at(i), C) < 0)
            continue;

            parameter_t param = C.list.at(m_param_id);
            m_parameters.push_back(param.data);
    }

    m_array->setParameters(&m_parameters);
    m_array->repaint();

    return 1;
}

//------------------------------------------------------------------------------------

int antenna::show_flash_param()
{
    int segment_id = m_sul->sul_flash_find_segment(ui->cbShowParam->currentText().toStdString().c_str());

    if(segment_id < 0)
        return -1;

    m_parameters.clear();

    for(unsigned i=0; i<m_sul->sul_total_abonents(); i++) {

        const std::vector<double>& data = m_sul->sul_flash_block(segment_id, i);

        int N = m_sul->sul_abonent_channels(i);

        for(int j=0; j<N; j++) {

            m_parameters.push_back(data.at(j));
        }
    }

    m_array->setParameters(&m_parameters);
    m_array->repaint();

        return 1;
}

//------------------------------------------------------------------------------------

int antenna::show_ram_param()
{
    m_param_id = 0;

    const std::vector<double>& codes = m_sul->sul_correction_codes();

    if(codes.empty())
        return 0;

    m_parameters.clear();

    for(unsigned i=0; i<codes.size(); i++) {

            m_parameters.push_back(codes.at(i));
    }

    m_array->setParameters(&m_parameters);
    m_array->repaint();

    return 1;
}

//---------------------------------------------------------------------------------------

void antenna::task_complete()
{
}

//---------------------------------------------------------------------------------------

void antenna::index_change(int index)
{
    ui->lbAbonentAddress->setText("0x"+QString::number(m_sul->sul_abonent_address(index),16));
}

//---------------------------------------------------------------------------------------

void antenna::set_test_mode(bool mode)
{
    if(mode) {
        index_change(0);
    }
    ui->spbAbonentIndex->setEnabled(mode);
}

//---------------------------------------------------------------------------------------

void antenna::select_test()
{
    ui->progressBar->reset();
    ui->progressBar->setValue(0);
}

//---------------------------------------------------------------------------------------

void antenna::start_test()
{
    int test_number = ui->cbSelecetTest->currentIndex();

    std::cout << "antenna::start_test(" << test_number << "): " << m_sul->sul_test_name(test_number) <<  endl;

    ui->progressBar->reset();
    ui->progressBar->setValue(0);

    m_thread->setup_task(task, test_number, this, ui->spbTestParamIndex->value());
    m_thread->start();

    // необходимо дождаться завершения, иначе вылетает программа
    m_thread->wait();
}

//---------------------------------------------------------------------------------------

int antenna::task(int command, void *param, int param_index)
{
    std::cout << "antenna::task(" << command << ", " << param << ")" << endl;

    if(!param) return -1;

    antenna *widget = (antenna *)param;

    int err = 0;
    int res = 0;
    int test_number = command;

    if(widget->ui->cbSingleAbonent->isChecked()) {

        int abonent_index = widget->ui->spbAbonentIndex->value();

        QString msg = QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) +
                QString::fromUtf8(": ") + QString::number(abonent_index);

        widget->m_bar->showMessage(msg);

        res = widget->m_sul->sul_test(abonent_index, test_number, param_index);
        if(res < 0) {

            widget->m_bar->showMessage(QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) +
                             QString::fromUtf8(": Абонент ") +
                             QString::number(abonent_index) +
                             QString::fromUtf8(" - Ошибка"));
            return -1;
        }

        widget->update_screen();

    } else {

        widget->ui->progressBar->reset();
        widget->ui->progressBar->setRange(0, widget->m_sul->sul_total_abonents()-1);
        widget->ui->progressBar->setValue(0);

        for(unsigned abonent_index=0; abonent_index < widget->m_sul->sul_total_abonents(); abonent_index++) {

            widget->m_bar->showMessage(QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) +
                             QString::fromUtf8(": Абонент ") +
                             QString::number(abonent_index));

            widget->ui->progressBar->setValue(abonent_index);

            res = widget->m_sul->sul_test(abonent_index, test_number, param_index);
            if(res < 0) {

                widget->m_bar->showMessage(QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) +
                                 QString::fromUtf8(": Абонент ") +
                                 QString::number(abonent_index) +
                                 QString::fromUtf8(" - Ошибка"));
                err++;

                continue;

            } else {

                widget->m_bar->showMessage(QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) +
                                 QString::fromUtf8(": Абонент ") +
                                 QString::number(abonent_index) +
                                 QString::fromUtf8(" - Ok"));

                widget->update_screen();
            }
        }
    }

    if(err == 0)
        widget->m_bar->showMessage(QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) + QString::fromUtf8(": Ok"));
    else
        widget->m_bar->showMessage(QString::fromUtf8(widget->m_sul->sul_test_name(test_number)) + QString::fromUtf8(": Ошибка!"));

    return 0;
}

//---------------------------------------------------------------------------------------

void antenna::debug_slot()
{
    m_sul->sul_flash_load();
}

//---------------------------------------------------------------------------------------
