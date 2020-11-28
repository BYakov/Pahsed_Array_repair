#ifndef DBGWIDGET_H
#define DBGWIDGET_H

#include "sul_protocol.h"
#include "sul_base.h"
#include "console.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>

namespace Ui {
    class dbgwidget;
}

class dbgwidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit dbgwidget(console& log, sul_base *sul_system, QWidget *parent = 0);
    ~dbgwidget();

private:
    Ui::dbgwidget *ui;
    console& tty;
    QStatusBar *bar;
    protocol *exchange;
    sul_base *sul;
    QTimer *dbg_timer;

private slots:
    void prepare_abonent_request();
    void dbg_timer_event();
    void send_abonent_request();
    void fill_abonent_form();
    void set_table_view(QTableWidget *t, int rowh, int colw);
};

#endif // DBGWIDGET_H
