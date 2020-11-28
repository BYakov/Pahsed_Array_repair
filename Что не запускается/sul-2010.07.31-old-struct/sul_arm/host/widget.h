#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QStandardItemModel>


#include "..\..\sul_src\serial.h"
#include "exchange.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget          *ui;
    struct dma_token    token;
    device              *port_tx;
    device              *port_rx;
    QStatusBar          *bar;
    QTimer              *timer;
    int                 transfer_bytes;
    unsigned char       counter;

    struct adc_param    param;
    struct adc_result   result;
    struct adc_buffer   adata;

    int preamble(int code, unsigned char data = 0, unsigned char *buffer = NULL, int size = 0);

public slots:
    void start_timer();
    void timer_event();

    void adc_param();
    void adc_start();
    void adc_result();
    void adc_buffer();
};

#endif // WIDGET_H
