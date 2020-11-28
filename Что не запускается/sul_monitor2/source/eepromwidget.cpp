#include "eepromwidget.h"
#include "ui_eepromwidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------

eepromwidget::eepromwidget(console& log, sul_base *sul_system, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::eepromwidget), tty(log), sul(sul_system)
{
    ui->setupUi(this);

    bar = statusBar();
    worker = new worker_thread(sul);
    display_timer = new QTimer();
    display_timer->setInterval(500);
    display_timer_counter = 0;

    // �������� ���� ������� ���������
    for(int i=0; i<sul->sul_flash_segment_count(); i++) {
        ui->cbFlashSegmentName->addItem(QString(sul->sul_flash_segment_name(i)));
    }
    ui->spbFlashAbonentNumber->setMaximum(sul->sul_total_abonents()-1);

    connect(display_timer,SIGNAL(timeout()),this,SLOT(display_timer_event()));
    connect(ui->spbFlashAbonentNumber,SIGNAL(valueChanged(int)),this,SLOT(fill_flash()));
    connect(ui->cbFlashSegmentName,SIGNAL(currentIndexChanged(int)),this,SLOT(fill_flash()));
    connect(ui->btnFlashFileOpen,SIGNAL(clicked()),this,SLOT(open_flash()));
    connect(ui->btnFlashErase,SIGNAL(clicked()),this,SLOT(erase_flash()));
    connect(ui->btnFlashLoad,SIGNAL(clicked()),this,SLOT(load_flash()));
    connect(ui->btnFlashSave,SIGNAL(clicked()),this,SLOT(save_flash()));

    fill_flash();

    tty << "eepromwidget::eepromwidget()" << "\n";
}

//-----------------------------------------------------------------------------

eepromwidget::~eepromwidget()
{
    close();
    delete ui;
    tty << "eepromwidget::~eepromwidget()" << "\n";
}

//-----------------------------------------------------------------------------

void eepromwidget::display_timer_event()
{
    ++display_timer_counter;

    if((display_timer_counter % 1) == 0) {
        bar->showMessage(tr("���������� ... ")
                         +QString::number(display_timer_counter/2)
                         +tr(" ���"));
    }
}

//-----------------------------------------------------------------------------

void eepromwidget::fill_flash()
{
    int abonent_index = ui->spbFlashAbonentNumber->value();
    int segment = sul->sul_flash_find_segment(ui->cbFlashSegmentName->currentText().toAscii());
    int block = abonent_index;

    const vector<double>& data_ = sul->sul_flash_block(segment,block);
    if(data_.empty()){
        bar->showMessage(tr("������! �� ���� �������� ������ ��� �������� ") + QString::number(abonent_index));
        return;
    }

    fill_table(data_);

    update_flash_dispaly();
}

//-----------------------------------------------------------------------------

void eepromwidget::fill_table(const vector<double>& data)
{
    if(data.empty()) return;

    QAbstractItemModel *model = ui->eepromTable->model();

    if(data.size() != (unsigned)model->rowCount()*model->columnCount()) {
        bar->showMessage(tr("������������ ������ ������ ��� �����������."));
        return;
    }

    int idx = 0;
    int value = 0;

    //cout << "sul_monitor::fill_table(): vector size = " << data.size() << endl;
    //cout << "sul_monitor::fill_table(): rowCount = " << model->rowCount() << endl;
    //cout << "sul_monitor::fill_table(): columnCount = " << model->columnCount() << endl;

    for (int nRow = 0; nRow < model->rowCount(); ++nRow) {

            for (int nCol = 0; nCol < model->columnCount(); ++nCol) {

                    QModelIndex index = model->index(nRow, nCol);

                    value = data[idx];

                    //cout << "sul_monitor::fill_table(): idx = " <<
                    // idx << " val = " << value;

                    model->setData( index, value );

                    //cout << " ok" << endl;

                    idx++;
            }
    }
}

//-----------------------------------------------------------------------------

void eepromwidget::open_flash()
{
    if(!sul) {
        bar->showMessage(tr("�� ������� ������� ���"));
        return;
    }

    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("�� ������ ���� ������������"));
        return;
    } else {
        bar->showMessage(tr("���� ������������: ") + fileName);
    }

    if( sul->sul_flash_reconfig( fileName.toAscii().data() ) < 0 ) {
        bar->showMessage(tr("������ �������������� ���"));
        return;
    }

    fill_flash();
}

//-----------------------------------------------------------------------------

void eepromwidget::erase_flash()
{
    if(!sul) {
        bar->showMessage(tr("�� ������� ������� ���"));
        return;
    }

    worker->start_task(task_erase_eeprom);
    display_timer->start();

    fill_flash();
}

//-----------------------------------------------------------------------------

void eepromwidget::load_flash()
{
    if(!sul) {
        bar->showMessage(tr("�� ������� ������� ���"));
        return;
    }

    worker->start_task(task_load_eeprom);
    display_timer->start();
}

//-----------------------------------------------------------------------------

void eepromwidget::save_flash()
{
    if(!sul) {
        bar->showMessage(tr("�� ������� ������� ���"));
        return;
    }

    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("�� ������ ���� ��� ���������� ������������"));
        return;
    } else {
        bar->showMessage(tr("���� ��� ���������� ������������: ") + fileName);
    }

    if( sul->sul_flash_save(fileName.toAscii().data()) < 0) {
        bar->showMessage(tr("������ ���������� ������ RAM"));
        return;
    }
}

//-----------------------------------------------------------------------------

void eepromwidget::update_flash_dispaly()
{
    cout << "sul_monitor::update_flash_dispaly()" << endl;

    int abonent_index = ui->spbFlashAbonentNumber->value();
    int abonent_space_crc = sul->sul_flash_space_crc(abonent_index);
    int abonent_device_crc = sul->sul_flash_crc(abonent_index);

    ui->gbFlashData->setTitle(  tr(" ������� ") + QString::number(abonent_index) +
                               tr(". CRC ������: 0x") +
                               QString::number(abonent_space_crc,16) +
                               tr(" CRC ��������: 0x") +
                               QString::number(abonent_device_crc,16) );

    //int total_space_crc = sul->sul_flash_space_crc();
    //int total_device_crc = sul->sul_flash_crc();
    //int total_device_crc = 0xFFFF;
    //ui->lblFileCRC->setText(QString::number(total_space_crc,16));
    //ui->lblHwCRC->setText(QString::number(total_device_crc,16));
}

//-----------------------------------------------------------------------------
/*
void eepromwidget::flashItemChanged( int value, int offset  )
{
    cout << "flashItemChanged(): value = " << value << " offset = " << offset << endl;

    double  data(value);

    int segment = sul->sul_flash_find_segment(ui->cbFlashSegmentName->currentText().toAscii());
    int abonent = ui->spbFlashAbonentNumber->value()-1;

    if( sul->sul_flash_set_element(segment, abonent, offset, data) < 0) {
        bar->showMessage(tr("������ ���������� ������ ������������ FLASH"));
        return;
    }

    update_flash_dispaly();
}
*/
//-----------------------------------------------------------------------------

QString eepromwidget::getFileName()
{
    QFileDialog *fileDialog = new QFileDialog();
    QString fileName = fileDialog->getOpenFileName(0, tr("������� ����"),".",tr("config files (*.cfg)"));
    delete fileDialog;
    return fileName;
}
