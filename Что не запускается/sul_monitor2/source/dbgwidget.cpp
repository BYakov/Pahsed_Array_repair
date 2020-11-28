#include "dbgwidget.h"
#include "ui_dbgwidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------

dbgwidget::dbgwidget(console& log, sul_base *sul_system, QWidget *parent) : QMainWindow(parent),
ui(new Ui::dbgwidget), tty(log), sul(sul_system)
{
    ui->setupUi(this);
    bar = statusBar();
    dbg_timer = new QTimer();
    dbg_timer->setInterval(ui->dbgPeriod->value());

    connect(dbg_timer,SIGNAL(timeout()),this,SLOT(dbg_timer_event()));

    if(sul) {
        exchange = sul->sul_exchange_protocol();
    }
    if(exchange) {
        // заполним поля кодами команд
        for(unsigned i=0; i<exchange->total_commands(); i++) {
            ui->abonentCmd->addItem(QString(exchange->command_name(i)));
        }
    }

    // работа с абонентами
    connect(ui->btnSend,SIGNAL(clicked()),this,SLOT(send_abonent_request()));
    connect(ui->abonentCmd,SIGNAL(currentIndexChanged(int)),this,SLOT(prepare_abonent_request()));
    connect(ui->abonentIndex,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));
    connect(ui->msgBlockNum,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));
    connect(ui->headerData,SIGNAL(cellChanged(int,int)),this,SLOT(prepare_abonent_request()));
    connect(ui->outputData,SIGNAL(cellChanged(int,int)),this,SLOT(prepare_abonent_request()));

    tty << "dbgwidget::dbgwidget()" << "\n";
}

//-----------------------------------------------------------------------------

dbgwidget::~dbgwidget()
{
    if(dbg_timer) {
        dbg_timer->stop();
    }
    close();
    tty << "dbgwidget::~dbgwidget()" << "\n";
    delete dbg_timer;
    delete ui;
}

//-----------------------------------------------------------------------------

void dbgwidget::prepare_abonent_request()
{
    tty << "prepare_abonent_request()" << "\n";

    if(!exchange) {
        bar->showMessage(tr("Ошибка! Протокл обмена не определен!"));
        return;
    }

    int abonent = ui->abonentIndex->value();
    int cmd = exchange->command_value(ui->abonentCmd->currentIndex());
    int bn = ui->msgBlockNum->value();
    int size = exchange->cmd_to_size(cmd);

    ui->msgBlockSize->setValue(size);

    struct host_mdr_dbg hdr = {0};
    unsigned char *buffer = (unsigned char*)malloc(size);
    memset(buffer,0,size);

    ui->inputData->setRowCount(size);
    ui->outputData->setRowCount(size);

    // Обнуление таблицы принимаемых данных
    QAbstractItemModel *m3 = ui->inputData->model();
    for (int nCol = 0; nCol < m3->columnCount(); ++nCol) {
        for (int nRow = 0; nRow < m3->rowCount(); ++nRow) {
            QModelIndex index = m3->index(nRow, nCol);
            m3->setData( index, 0 );
        }
    }

    // Заполнение таблицы передаваемых данных
    QAbstractItemModel *m2 = ui->outputData->model();
    for (int nCol = 0; nCol < m2->columnCount(); ++nCol) {
        for (int nRow = 0; nRow < size; ++nRow) {
            QModelIndex index = m2->index(nRow, nCol);
            buffer[nRow] = m2->data( index ).toInt();
        }
    }

    hdr = exchange->fill_host_mdr_dbg(abonent,cmd,bn,size);

    // Заполнение таблицы заголовка
    QAbstractItemModel *m1 = ui->headerData->model();
    for (int nCol = 0; nCol < m1->columnCount(); ++nCol) {
        for (unsigned nRow = 0; nRow < sizeof(struct host_mdr_dbg); ++nRow) {
            QModelIndex index1 = m1->index(nRow, nCol);
            m1->setData( index1, *((unsigned char*)&hdr + nRow) );
        }
    }

    free(buffer);
}

//-----------------------------------------------------------------------------

void dbgwidget::dbg_timer_event()
{
    if(!exchange) {
        bar->showMessage(tr("Ошибка! Протокл обмена не определен!"));
        return;
    }

    int abonent = ui->abonentIndex->value();
    int cmd = exchange->command_value(ui->abonentCmd->currentIndex());
    int bn = ui->msgBlockNum->value();
    unsigned char data[256];
    int size = exchange->cmd_to_size(cmd);
    ui->msgBlockSize->setValue(size);

    memset(data,0,sizeof(data));

    // заполнение данными
    if(exchange->cmd_to_type(cmd) == to_target) {
        QAbstractItemModel *model2 = ui->outputData->model();
        for (int nCol = 0; nCol < model2->columnCount(); ++nCol) {
            for (int nRow = 0; nRow < size; ++nRow) {
                QModelIndex index = model2->index(nRow, nCol);
                data[nRow] = model2->data( index ).toInt();
            }
        }
    }

    if( exchange->dbg_request(abonent,cmd,bn,data,size) < 0 ) {

        bar->showMessage(tr("Ошибка выполнения запроса"));
        return;
    }

    // Заполнение таблицы принимаемых данных
    if(exchange->cmd_to_type(cmd) == to_host) {

        QAbstractItemModel *model3 = ui->inputData->model();
        for (int nCol = 0; nCol < model3->columnCount(); ++nCol) {
            for (int nRow = 0; nRow < size; ++nRow) {
                QModelIndex index = model3->index(nRow, nCol);
                model3->setData( index, data[nRow] );
            }
        }
    }


    bar->showMessage(tr("Запрос выполнен."));
}

//-----------------------------------------------------------------------------

void dbgwidget::send_abonent_request()
{
    if( ui->dbgPeriod->value() > 0 ) {

        if(dbg_timer->isActive()) {
            dbg_timer->stop();
            ui->btnSend->setChecked(false);
            ui->btnSend->setText(tr("Старт"));
        } else {
            dbg_timer->setInterval(ui->dbgPeriod->value());
            ui->btnSend->setChecked(true);
            ui->btnSend->setText(tr("Стоп"));
            dbg_timer->start();
        }
    } else {
        ui->btnSend->setChecked(false);
        dbg_timer_event();
    }
}

//-----------------------------------------------------------------------------

void dbgwidget::fill_abonent_form()
{
    for (int nCol = 0; nCol < 1; ++nCol) {

        for (int nRow = 0; nRow < 10; ++nRow) {

            QModelIndex index1 = ui->headerData->model()->index(nRow, nCol);
            ui->headerData->model()->setData( index1, 0 );
        }
    }

    for (int nCol = 0; nCol < 1; ++nCol) {

        for (int nRow = 0; nRow < 128; ++nRow) {

            QModelIndex index2 = ui->outputData->model()->index(nRow, nCol);
            QModelIndex index3 = ui->inputData->model()->index(nRow, nCol);

            ui->outputData->model()->setData( index2, 0 );
            ui->inputData->model()->setData( index3, 0 );
        }
    }

    prepare_abonent_request();
}

//-----------------------------------------------------------------------------

void dbgwidget::set_table_view(QTableWidget *t, int rowh, int colw)
{
    QAbstractItemModel *m = t->model();

    for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
        t->setColumnWidth(nCol,colw);
    }
    for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
        t->setRowHeight(nRow,rowh);
    }
}

//-----------------------------------------------------------------------------
