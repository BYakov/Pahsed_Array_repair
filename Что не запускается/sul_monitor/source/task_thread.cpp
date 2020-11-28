#include "task_thread.h"

//-----------------------------------------------------------------------------

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>

//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

task_thread::task_thread(QObject *parent) :
    QThread(parent)
{
    m_exit_flag = false;
    m_task = NULL;
    m_param_index = 0;
}

//-----------------------------------------------------------------------------

void task_thread::run()
{
    setTerminationEnabled(true);

    int status = -1;

    if(m_task) {
        std::cout << "task_thread::run(): start task" << endl;
        status = m_task(m_command, m_param, m_param_index);
        std::cout << "task_thread::run(): stop task" << endl;
        emit task_status(status);
    }

    msleep(100);

    std::cout << "task_thread::run(): thread finished" << endl;
}

//-----------------------------------------------------------------------------

void task_thread::stop()
{
    m_exit_flag = true;
}

//-----------------------------------------------------------------------------

void task_thread::setup_task(task_routine new_task, int command, void *param, int param_index)
{
    std::cout << "task_thread::setup_task()" << endl;

    m_command = command;
    m_param = param;
    m_task = new_task;
    m_param_index = param_index;
}

//-----------------------------------------------------------------------------

