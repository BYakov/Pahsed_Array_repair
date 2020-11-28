#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCodec>
#include <QPlainTextEdit>
#include <QFileDialog>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#include "configwidget.h"
#include "beamwidget.h"
#include "eepromwidget.h"
#include "ramwidget.h"
#include "dbgwidget.h"
#include "tunewidget.h"
#include "console.h"
#include "sul_base.h"
#include "device.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const char *configFile = 0, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    configwidget *cw;
    beamwidget *bw;
    eepromwidget *ew;
    ramwidget *rw;
    dbgwidget *dw;
    tunewidget *tw;
    //QPlainTextEdit *consoleWidget;
    QStatusBar *bar;
    console tty;

private:
    HMODULE hlibSul;
    HMODULE hlibDev;
    device *dev;
    dev_factory factoryDev;
    sul_base *sul;
    sul_factory factorySul;

    QVariant libSul;
    QVariant libDev;
    QVariant ifc;
    QVariant speed;
    QVariant excel;
    QVariant flash;
    QVariant ram;
    QVariant vid;
    QVariant Abon;
    QVariant Chan;
    QVariant dx_step1;
    QVariant dy_step1;
    QVariant dx_step2;
    QVariant dy_step2;

    void parseConfigFile(const char *file);
    void loadSulLibrary(QString libNameSul);
    void loadDevLibrary(QString libNameDev);

private slots:
    void autoConfig();
    void openSulConfig(const char *cmdlineConfigFile = 0);
    void actConsole_triggered();
    void actDeleteObject_triggered();
    void actTuneExt_triggered();
    void actExit_triggered();
    void actConfig_triggered();
    void actBeam_triggered();
    void actEeprom_triggered();
    void actRam_triggered();
    void actDebug_triggered();

    //! Подключили новое устройство
    void newDeviceConnected(device *newDev);
    void newSulConnected(sul_base *newSul);
    QString getFileName();
};

#endif // MAINWINDOW_H
