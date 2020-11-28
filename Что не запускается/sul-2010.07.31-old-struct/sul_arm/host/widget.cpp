#include "widget.h"
#include "sul_analizer.h"
#include "ui_widget.h"

//------------------------------------------------------------------------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->setupUi(this);

    bar = new QStatusBar();
    ui->mainLayout->addWidget(bar);

    timer = new QTimer();

    port_tx = new serial("COM3");
    if(port_tx->is_open())
	bar->showMessage(tr("COM3 открыт"));
    else
        bar->showMessage(tr("Ошибка порта COM3"));

    port_rx = new serial("COM2");
    if(port_rx->is_open())
        bar->showMessage(tr("COM2 открыт"));
    else
        bar->showMessage(tr("Ошибка порта COM2"));

    connect(ui->btnStart,SIGNAL(clicked()),this,SLOT(start_timer()));

    connect(ui->btnSetParam,SIGNAL(clicked()),this,SLOT(adc_param()));
    connect(ui->btnStartAdc,SIGNAL(clicked()),this,SLOT(adc_start()));
    connect(ui->btnResultAdc,SIGNAL(clicked()),this,SLOT(adc_result()));
    connect(ui->btnBufferAdc,SIGNAL(clicked()),this,SLOT(adc_buffer()));

    connect(timer,SIGNAL(timeout()),this,SLOT(timer_event()));

    transfer_bytes = 0;

    setWindowTitle(tr("Тест АЦП (ARM)"));
    setFixedSize(geometry().width(),geometry().height());

    memset(&param.buffer_size,0,sizeof(struct adc_param));
    memset(&result.mean,0,sizeof(struct adc_result));
    memset(&adata.buffer_size,0,sizeof(struct adc_buffer));

    counter = 0;

    unsigned char d = 0;
    //while(port_tx->read_data(&d,1) > 0 );
    while(port_rx->read_data(&d,1) > 0 );
    bar->showMessage( tr(" Буферы портов сброшены.") );
}

//------------------------------------------------------------------------------------------

Widget::~Widget()
{
    delete ui;
    if(port_tx)
        delete port_tx;
    if(bar)
        delete bar;
    if(timer)
        delete timer;
}

//------------------------------------------------------------------------------------------

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------------------------------

void Widget::adc_param()
{
    param.buffer_size = ui->spbNsamples->value();
    param.sample_rate = ui->spbFrequency->value();

    if( preamble(set_adc_param, 0, (unsigned char *)&param.buffer_size, sizeof(struct adc_param)) < 0 ) {
        return;
    }

    Sleep(1);

    transfer_bytes += port_tx->write_data(&param,sizeof(struct adc_param));

    bar->showMessage( QString::number(transfer_bytes) + tr(" байт") );
}

//------------------------------------------------------------------------------------------

void Widget::adc_start()
{
    if( preamble(start_adc) < 0 ) {
        return;
    }

    bar->showMessage( tr("АЦП работает...") );
}

//------------------------------------------------------------------------------------------

void Widget::adc_result()
{
    if( preamble(get_adc_result) < 0 ) {
        return;
    }

    Sleep(1);

    if(port_tx->read_data(&result,sizeof(struct adc_result)) != sizeof(struct adc_result) ) {
        bar->showMessage( tr(" Ошибка! Идет сбор данных АЦП.") );
        return;
    }

    ui->l_mean->setText(QString::number(result.mean));
    ui->l_rms->setText(QString::number(result.rms));

    bar->showMessage( tr(" Обработка АЦП завершена") );
}

//------------------------------------------------------------------------------------------

void Widget::adc_buffer()
{
    int size = 128;

    adata.buffer_size = size;

    if( preamble(get_adc_buffer, size) < 0 ) {
        return;
    }

    Sleep(1);

    unsigned short *buffer = (unsigned short*)malloc(size*sizeof(unsigned short));
    if(!buffer) {
        bar->showMessage( tr(" Ошибка выделения буффера!") );
        return;
    }

    Sleep(10);

    if( port_tx->read_data(buffer,size) != size ) {
        bar->showMessage( tr(" Ошибка приема данных АЦП!") );
        free(buffer);
        return;
    }

    data_plot *plot = new data_plot(buffer);
    plot->show();

    free(buffer);

    bar->showMessage( tr(" Данные АЦП получены.") );
}

//------------------------------------------------------------------------------------------
//          Функции подготовки обмена

int Widget::preamble(int code, unsigned char data, unsigned char *buffer, int size)
{
    struct dma_token token = {0};

    token.code = code;
    token.size = size;
    token.data = data;

    init_dma_token(&token,data,buffer,size);

    if( port_tx->write_data(&token, sizeof(struct dma_token)) != sizeof(struct dma_token) ) {
            bar->showMessage(tr("preamble(): Ошибка передачи управляющего сообщения!"));
            return -1;
    }

    return 0;
}

//------------------------------------------------------------------------------------------

void Widget::timer_event()
{
/*
    int size = sizeof(struct host_data);

    packet.data[0] = ui->spbUsartID->value();
    packet.data[1] = ui->spbUsartCtrl->value();
    packet.data[2] = ui->spbNumBytes->value();
    packet.data[3] = ui->spbUsartD0->value();
    packet.data[4] = ui->spbUsartD1->value();
    packet.data[5] = ui->spbUsartD2->value();
    packet.data[6] = ui->spbUsartD3->value();

    if( preamble(size, usart_debug_msg, 0, (unsigned char*)&packet) ) {
        bar->showMessage(tr("timer_event(): Ошибка передачи заголовка!"));
        return;
    }

    Sleep(1);

    transfer_bytes += port_tx->write_data(&packet.data,size);

    bar->showMessage( QString::number(transfer_bytes) + tr(" байт") );
*/
    adc_param();
}

//------------------------------------------------------------------------------------------

void Widget::start_timer()
{
    if(!port_tx->is_open())
        return;

    if(timer->isActive()) {
        timer->stop();
        ui->btnStart->setText(tr("Старт"));
        return;
    }

    if(ui->periodVal->value()) {

        // настройка таймера на циклическую работу
        ui->btnStart->setText(tr("Стоп"));
        timer->setInterval(ui->periodVal->value());
        timer->start();

        return;
    }

    // однократная выдача
    timer_event();
}

//------------------------------------------------------------------------------------------
