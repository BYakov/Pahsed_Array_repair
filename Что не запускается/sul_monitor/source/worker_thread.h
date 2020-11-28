#ifndef WORKER_THREAD_H
#define WORKER_THREAD_H

#include <QThread>

//-----------------------------------------------------------------------------

#include "sul_base.h"

//-----------------------------------------------------------------------------

enum {
    task_erase_eeprom,
    task_load_eeprom,
    task_erase_ram,
    task_load_ram,
    task_load_ram_codes,
    task_setup_eeprom,
    task_setup_ram,
    task_rescan_modules,
    task_idle,
    task_unknown
};

//-----------------------------------------------------------------------------

class worker_thread : public QThread
{
    Q_OBJECT

private:
    worker_thread();

    sul_base *sul;
    bool exit_ok;
    bool paused;
    int  task_code;
    int	 pulse_count;
    void run();

public:
    worker_thread(sul_base *Sul);
    virtual ~worker_thread();

    void set_task(int task);
    void start_task(int task);
    void stop_task();
    void pause_task(bool state);

signals:
    void task_status(int status, int task_code);
};

//-----------------------------------------------------------------------------


#endif // WORKER_THREAD_H

