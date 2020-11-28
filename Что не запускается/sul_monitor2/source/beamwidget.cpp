#include "beamwidget.h"
#include "ui_beamwidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

beamwidget::beamwidget(console& log, sul_base *sul_system, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::beamwidget), tty(log), sul(sul_system)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->setupUi(this);
    bar = statusBar();
    scan = new scanner(90,0,0.1);
    graph = new position_graph(scan,this);
    ui->beamLayout->addWidget(graph);

    setMouseTracking(true);
    timer = new QTimer();

    // таймер сканирования
    connect(timer,SIGNAL(timeout()),this,SLOT(timer_event()));

    // смена направления сканирования
    connect(ui->rbtAxisX,SIGNAL(clicked()),this,SLOT(axis_change()));
    connect(ui->rbtAxisY,SIGNAL(clicked()),this,SLOT(axis_change()));
    connect(ui->rbtAxisXY,SIGNAL(clicked()),this,SLOT(axis_change()));

    // запуск/останов периодического таймера
    connect(ui->btnStart,SIGNAL(clicked()),this,SLOT(start_scanner()));
    connect(ui->btnSetPosition,SIGNAL(clicked()),this,SLOT(setup_position()));
    connect(graph,SIGNAL(new_position(double,double)),this,SLOT(update_position(double,double)));

    // изменение шага сканирования по Х или Y
    connect(ui->step_dr,SIGNAL(editingFinished()),this,SLOT(dr_change()));

    // изменение значения по Х или Y
    connect(ui->value_x0,SIGNAL(valueChanged(double)),this,SLOT(x0_change(double)));
    connect(ui->value_y0,SIGNAL(valueChanged(double)),this,SLOT(y0_change(double)));

    // изменение угла
    connect(ui->scanAngle,SIGNAL(valueChanged(double)),this,SLOT(angle_change()));

    // изменение границ
    connect(ui->scanSectorMax,SIGNAL(editingFinished()),this,SLOT(sector_max_change()));

    tty << "beamwidget::beamwidget()\n";
}

beamwidget::~beamwidget()
{
    close();
    delete ui;
    if(scan) delete scan;
    if(timer) delete timer;
    if(graph) delete graph;
    tty << "beamwidget::~beamwidget()\n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//		    Запуск и останов сканирования
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void beamwidget::start_scanner()
{
    if(timer->isActive()) {

        stop_scanner();

    } else {

        set_scanner();

        timer->setInterval(ui->period->value());
        timer->start();

        ui->btnStart->setText(tr("Стоп"));
    }
}

//-----------------------------------------------------------------------------

void beamwidget::stop_scanner()
{
    if(timer->isActive()) {

        scan->stop();
        timer->stop();
        ui->btnStart->setText(tr("Старт"));
    }

    ui->currentX->setText(QString::number(scan->get_x()));
    ui->currentY->setText(QString::number(scan->get_y()));
    ui->currentXcode->setText(QString::number(scan->get_x()));
    ui->currentYcode->setText(QString::number(scan->get_y()));

    if(graph) graph->repaint();
}

//-----------------------------------------------------------------------------

void beamwidget::step_scanner()
{
    if(scan->step()) {

        if( sul->sul_beam_position(scan->get_x(), scan->get_y()) < 0 )
        {
            bar->showMessage(tr("Ошибка установки нового положения!"));
        } else {
            bar->showMessage(tr("Кооринаты установлены."));
        }
    }

    ui->currentX->setText(QString::number(scan->get_x()));
    ui->currentY->setText(QString::number(scan->get_y()));
    ui->currentXcode->setText(QString::number(scan->get_x()));
    ui->currentYcode->setText(QString::number(scan->get_y()));

    if(graph) graph->repaint();
}

//-----------------------------------------------------------------------------

void beamwidget::set_scanner()
{
    timer->stop();

    scan->stop();

    scan->set_angle(ui->scanAngle->value());
    scan->set_rm(ui->scanSectorMax->value());
    scan->set_dr(ui->step_dr->value());

    scan->start();

    ui->progressBar->reset();
    ui->progressBar->setRange(0, scan->get_n());
    ui->progressBar->setValue(scan->get_index());

    ui->currentX->setText(QString::number(scan->get_x()));
    ui->currentY->setText(QString::number(scan->get_y()));
    ui->currentXcode->setText(QString::number(scan->get_x()));
    ui->currentYcode->setText(QString::number(scan->get_y()));

    if(graph) graph->repaint();
}

//-----------------------------------------------------------------------------

void beamwidget::setup_position()
{
    scan->set_x(ui->value_x0->value());
    scan->set_y(ui->value_y0->value());

    if( sul->sul_beam_position(scan->get_x(), scan->get_y()) < 0 )
    {
        bar->showMessage(tr("Ошибка установки нового положения!"));
    } else {
        bar->showMessage(tr("Кооринаты установлены."));
    }

    ui->currentX->setText(QString::number(scan->get_x()));
    ui->currentY->setText(QString::number(scan->get_y()));
    ui->currentXcode->setText(QString::number(scan->get_x()));
    ui->currentYcode->setText(QString::number(scan->get_y()));

    if(graph) graph->repaint();
}

//-----------------------------------------------------------------------------

void beamwidget::update_position(double X, double Y)
{
    ui->value_x0->setValue(X);
    ui->value_y0->setValue(Y);

    setup_position();
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//              Изменение параметров сканирования
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void beamwidget::x0_change(double X)
{
    if(ui->cbTrackMode->isChecked())
        setup_position();
}

//-----------------------------------------------------------------------------

void beamwidget::y0_change(double Y)
{
    if(ui->cbTrackMode->isChecked())
        setup_position();
}

//-----------------------------------------------------------------------------

void beamwidget::dr_change()
{
    const double pi = 3.1415926535;
    scan->set_dr(ui->step_dr->value());
    ui->value_x0->setSingleStep(ui->step_dr->value()*cos(ui->scanAngle->value()*pi/180.0));
    ui->value_y0->setSingleStep(ui->step_dr->value()*sin(ui->scanAngle->value()*pi/180.0));
}

//-----------------------------------------------------------------------------

void beamwidget::angle_change()
{
    const double pi = 3.1415926535;
    scan->set_angle(ui->scanAngle->value());
    ui->value_x0->setSingleStep(ui->step_dr->value()*cos(ui->scanAngle->value()*pi/180.0));
    ui->value_y0->setSingleStep(ui->step_dr->value()*sin(ui->scanAngle->value()*pi/180.0));
}

//-----------------------------------------------------------------------------

void beamwidget::sector_max_change()
{
    scan->set_rm(ui->scanSectorMax->value());
}

//-----------------------------------------------------------------------------

void beamwidget::axis_change()
{
    if( ui->rbtAxisX->isChecked() ) {
        ui->scanAngle->setValue(0);
    }
    if( ui->rbtAxisY->isChecked() ) {
        ui->scanAngle->setValue(90);
    }
    if( ui->rbtAxisXY->isChecked() ) {
        ui->scanAngle->setValue(45);
    }
    angle_change();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//          Прерывание таймера при сканировании
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void beamwidget::timer_event()
{
    if(!scan->step()) {
        stop_scanner();
        return;
    }

    if( sul->sul_beam_position(scan->get_x(), scan->get_y()) < 0 )
    {
        bar->showMessage(tr("Ошибка установки нового положения!"));
    } else {
        bar->showMessage(tr("Кооринаты установлены."));
    }

    ui->progressBar->setValue(scan->get_index());

    ui->currentX->setText(QString::number(scan->get_x()));
    ui->currentY->setText(QString::number(scan->get_y()));
    ui->currentXcode->setText(QString::number(scan->get_x()));
    ui->currentYcode->setText(QString::number(scan->get_y()));

    if(graph) graph->repaint();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//              Рисование положения луча и состояния каналов
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void beamwidget::show_position()
{
    if(graph) graph->show();
}
