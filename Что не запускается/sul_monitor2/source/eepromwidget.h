#ifndef EEPROMWIDGET_H
#define EEPROMWIDGET_H

#include "sul_base.h"
#include "console.h"
#include "worker_thread.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>

namespace Ui {
    class eepromwidget;
}

class eepromwidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit eepromwidget(console& log, sul_base *sul_system, QWidget *parent = 0);
    virtual ~eepromwidget();

private:
    Ui::eepromwidget *ui;
    console& tty;
    sul_base *sul;
    QStatusBar *bar;
    QTimer *display_timer;
    worker_thread *worker;
    int display_timer_counter;

private slots:
    void fill_table(const std::vector<double>& data);
    void update_flash_dispaly();
    void display_timer_event();
    void fill_flash();
    void open_flash();
    void erase_flash();
    void load_flash();
    void save_flash();
    QString getFileName();
};

#endif // EEPROMWIDGET_H
