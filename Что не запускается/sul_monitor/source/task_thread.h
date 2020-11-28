#ifndef TASK_THREAD_H
#define TASK_THREAD_H


#include <QThread>

//--------------------------------------

typedef int (*task_routine)(int, void*, int);

//--------------------------------------

class task_thread : public QThread
{
    Q_OBJECT

public:
    explicit task_thread(QObject *parent = 0);
    void stop();
    void setup_task(task_routine new_task, int command, void* param, int param_index = 0);

signals:
    void task_status(int status);

private:
    bool m_exit_flag;
    task_routine m_task;
    int m_command;
    void* m_param;
    int m_param_index;
    void run();
};

#endif // TASK_THREAD_H
