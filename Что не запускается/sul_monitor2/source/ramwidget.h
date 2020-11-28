#ifndef RAMWIDGET_H
#define RAMWIDGET_H

#include "console.h"
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
    class ramwidget;
}

class ramwidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit ramwidget(QWidget *parent = 0, console *log = NULL);
    ~ramwidget();

private:
    Ui::ramwidget *ui;
    QStandardItemModel *ramModel;
    console *tty;
};

#endif // RAMWIDGET_H
