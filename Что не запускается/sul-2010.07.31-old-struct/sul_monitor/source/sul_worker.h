#ifndef SUL_MONITOR_H
#define SUL_MONITOR_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QStandardItemModel>

#include "ui_sul_monitor.h"

#include "sul_mdo.h"
#include "sul_avr.h"
#include "serial.h"
#include "scanner.h"
#include "packet485.h"
#include "angle_correct.h"

#define SYSTEM_CONFIG_FILE ".\\config\\system.cfg"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class sul_channel_analizer : public QWidget
{
        Q_OBJECT

private:
        QAbstractItemModel  *m;
        QStatusBar          *bar;
        int                 square_size;

public:
        sul_channel_analizer(QAbstractItemModel *m, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~sul_channel_analizer();

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);

public:
        void set_model(QAbstractItemModel *m);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class sul_graph : public QWidget
{
	Q_OBJECT

private:
	scanner	*scan;

	QLabel *X;
	QLabel *Y;

public:
	sul_graph(scanner *scan = NULL, QWidget *parent = 0, Qt::WFlags flags = 0);
	~sul_graph();


protected:
	void paintEvent(QPaintEvent *event);

public:
	void repaint();

};

//-----------------------------------------------------------------------------

enum sul_type {
	SUL_AVR,
	SUL_MDO,
};

//-----------------------------------------------------------------------------

enum ifc_type {
	IFC_RS232_1,
	IFC_RS232_2,
	IFC_RS485_1,
	IFC_RS485_2,
};

//-----------------------------------------------------------------------------
class worker_thread : public QThread {

    explicit worker_thread(void *sul);
    virtual ~worker_thread();

private:
    void run();

public:
    int start_task();
    int stop_task();
};
//-----------------------------------------------------------------------------

#endif // SUL_MONITOR_H

