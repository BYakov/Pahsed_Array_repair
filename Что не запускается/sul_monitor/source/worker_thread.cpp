#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

//---------------------------------------------------------------------------------------

#include "worker_thread.h"

//---------------------------------------------------------------------------------------
using namespace std;
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
            msleep(100);
            emit task_status(status,task_erase_eeprom);
            //cout << "complete" << endl;
            break;
        case task_load_eeprom:
            //cout << "task_load_eeprom ... ";
            status = sul->sul_flash_load();
            msleep(100);
            emit task_status(status,task_load_eeprom);
            //cout << "complete" << endl;
            break;
        case task_erase_ram:
            //cout << "task_erase_eeprom ... ";
            status = sul->sul_ram_erase();
            msleep(100);
            emit task_status(status,task_erase_ram);
            //cout << "complete" << endl;
            break;
        case task_load_ram:
            //cout << "task_load_eeprom ... ";
            status = sul->sul_ram_load();
            msleep(100);
            emit task_status(status,task_load_ram);
            //cout << "complete" << endl;
            break;
        case task_load_ram_codes: {
            std::cout << "task_load_ram_codes ... " << endl;
            const std::vector<double>& codes = sul->sul_correction_codes();
            if(codes.empty()) {
                emit task_status(-1,task_load_ram_codes);
                break;
            }
            status = sul->sul_ram_load(codes);
            msleep(100);
            emit task_status(status,task_load_ram_codes);
            std::cout << "complete" << endl;
            }
            break;
        case task_rescan_modules:
            std::cout << "sul_rescan_modules ... " << endl;
            status = sul->sul_rescan_modules();
            msleep(100);
            emit task_status(status,task_rescan_modules);
            std::cout << "complete" << endl;
            break;
        case task_setup_eeprom:
            std::cout << "sul_setup_eeprom ... " << endl;
            status = sul->sul_setup_from_flash();
            msleep(100);
            emit task_status(status,task_setup_eeprom);
            std::cout << "complete" << endl;
            break;
        case task_setup_ram:
            std::cout << "sul_setup_ram ... " << endl;
            status = sul->sul_setup_from_ram();
            msleep(100);
            emit task_status(status,task_setup_ram);
            std::cout << "complete" << endl;
            break;
        case task_idle:
            msleep(50);
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
    cout << "worker_thread::start_task(" << task << ")" << endl;

    if(!sul)
        return;

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
