#ifndef BEAMWIDGET_H
#define BEAMWIDGET_H

#include "sul_base.h"
//#include "scanner.h"
#include "position_graph.h"
#include "console.h"
#include <QMainWindow>

namespace Ui {
    class beamwidget;
}

class beamwidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit beamwidget(console& log, sul_base *sul_system = NULL, QWidget *parent = 0);
    virtual ~beamwidget();

private:
    Ui::beamwidget  *ui;
    console&        tty;
    sul_base        *sul;
    scanner         *scan;
    position_graph  *graph;
    QTimer          *timer;
    QStatusBar      *bar;

public slots:
    void start_scanner();
    void stop_scanner();
    void step_scanner();
    void set_scanner();
    void setup_position();

    void dr_change();
    void x0_change(double X);
    void y0_change(double Y);
    void angle_change();
    void sector_max_change();
    void axis_change();
    void timer_event();
    void show_position();
    void update_position(double X, double Y);
};

#endif // BEAMWIDGET_H
