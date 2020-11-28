#include "ramwidget.h"
#include "ui_ramwidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

ramwidget::ramwidget(QWidget *parent, console *log) :
    QMainWindow(parent),
    ui(new Ui::ramwidget), tty(log)
{
    ui->setupUi(this);
/*
    ui->ramTable->setRowCount(8);
    ui->ramTable->setColumnCount(16);

    QAbstractItemModel *m = ui->ramTable->model();

    for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
        ui->ramTable->setColumnWidth(nCol,43);
    }
    for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
        ui->ramTable->setRowHeight(nRow,24);
    }
*/
    if(tty) tty->print("ramwidget::ramwidget()");
}

ramwidget::~ramwidget()
{
    close();
    delete ui;
    if(tty) tty->print("ramwidget::~ramwidget()");
}
