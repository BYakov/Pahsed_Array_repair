#ifndef WORKER_THREAD_H
#define WORKER_THREAD_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QThread>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------

#include "sul_base.h"

//-----------------------------------------------------------------------------

enum {
    task_erase_eeprom,
    task_load_eeprom,
    task_erase_ram,
    task_load_ram,
    task_idle,
};

//-----------------------------------------------------------------------------
/*
class worker_thread : public QThread
{
    Q_OBJECT

public:
    worker_thread();
    worker_thread(sul_base *Sul);
    virtual ~worker_thread();

private:
    sul_base *sul;
    bool exit_ok;
    bool paused;
    int  task_code;
    int	 pulse_count;

    virtual void run();

public:
    void set_task(int task);
    void start_task(int task);
    void stop_task();
    void pause_task(bool state);

signals:
    void task_status(int status);
};
*/
//-----------------------------------------------------------------------------


#endif // WORKER_THREAD_H

