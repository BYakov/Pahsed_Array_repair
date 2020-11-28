//---------------------------------------------------------------------------------------

#include "sul_monitor.h"

//---------------------------------------------------------------------------------------

worker_thread::worker_thread() : QThread()
{
    exit_ok = true;
    sul = NULL;
    task_code = task_idle;
    //timer = NULL;
    pulse_count = 0;
}

//---------------------------------------------------------------------------------------

worker_thread::worker_thread(sul_base *Sul) : QThread()
{
    exit_ok = false;
    sul = Sul;
    task_code = task_idle;
    pulse_count = 0;
}

//---------------------------------------------------------------------------------------

worker_thread::~worker_thread()
{
    if(isRunning()) {
        stop_task();
        wait(1000);
    }
}

//---------------------------------------------------------------------------------------

void worker_thread::run()
{
    //cout << "worker_thread::run()" << endl;

    int status = 0;

    setTerminationEnabled(false);

    while(!exit_ok) {

        if(paused)
            continue;

        switch(task_code) {
            case task_erase_eeprom:
                //cout << "task_erase_eeprom ... ";
                status = sul->sul_flash_erase();
                emit task_status(status);
                //cout << "complete" << endl;
            break;
            case task_load_eeprom:
                //cout << "task_load_eeprom ... ";
                status = sul->sul_flash_load();
                emit task_status(status);
                //cout << "complete" << endl;
            break;
        case task_erase_ram:
            //cout << "task_erase_eeprom ... ";
            status = sul->sul_ram_erase();
            emit task_status(status);
            //cout << "complete" << endl;
        break;
        case task_load_ram:
            //cout << "task_load_eeprom ... ";
            status = sul->sul_ram_load();
            emit task_status(status);
            //cout << "complete" << endl;
        break;
            case task_idle:
                msleep(1000);
                continue;
            break;
        }

        task_code = task_idle;
        //cout << "worker_thread(): thread working..." << endl;
    }

    setTerminationEnabled(true);

    //cout << "worker_thread(): stopped" << endl;

    quit();
}

//-----------------------------------------------------------------------------

void worker_thread::start_task( int task )
{
    //cout << "worker_thread::start_task()" << endl;

    if(!sul) return;

    exit_ok = false;
    paused = false;
    task_code = task;

    if(!isRunning())
        QThread::start();
}

//-----------------------------------------------------------------------------

void worker_thread::stop_task()
{
    //cout << "worker_thread::stop_task()" << endl;
    setTerminationEnabled(true);
    exit_ok = true;
    task_code = task_idle;
}

//-----------------------------------------------------------------------------

void worker_thread::pause_task(bool state)
{
    //cout << "pause = " << state << endl;
    paused = state;
    task_code = task_idle;
}

//-----------------------------------------------------------------------------
