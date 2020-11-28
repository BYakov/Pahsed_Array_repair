
#include "mainwindow.h"
#include "ui_mainwindow.h"

//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------

MainWindow::MainWindow(const char *configFile, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));

    ui->setupUi(this);

    bar = statusBar();

    dev = NULL;
    sul = NULL;
    cw = NULL;
    bw = NULL;
    ew = NULL;
    rw = NULL;
    dw = NULL;
    tw = NULL;

    connect(ui->actExit,SIGNAL(triggered()),this,SLOT(actExit_triggered()));
    connect(ui->actConfig,SIGNAL(triggered()),this,SLOT(actConfig_triggered()));
    connect(ui->btnAutoConfig,SIGNAL(clicked()),this,SLOT(autoConfig()));
    connect(ui->actBeam,SIGNAL(triggered()),this,SLOT(actBeam_triggered()));
    connect(ui->actEEPROM,SIGNAL(triggered()),this,SLOT(actEeprom_triggered()));
    connect(ui->actRAM,SIGNAL(triggered()),this,SLOT(actRam_triggered()));
    connect(ui->actDebug,SIGNAL(triggered()),this,SLOT(actDebug_triggered()));
    connect(ui->actTuneExt,SIGNAL(triggered()),this,SLOT(actTuneExt_triggered()));
    connect(ui->actDeleteObject,SIGNAL(triggered()),this,SLOT(actDeleteObject_triggered()));
    connect(ui->actConsole,SIGNAL(triggered()),this,SLOT(actConsole_triggered()));

    //выбор файла конфигурации системы СУЛ
    connect(ui->btnOpenSulConfig,SIGNAL(clicked()),this,SLOT(openSulConfig()));

    //consoleWidget = new QPlainTextEdit();
    //consoleWidget->setWindowFlags(Qt::SplashScreen);
    //consoleWidget->setTextInteractionFlags(Qt::NoTextInteraction);
    //consoleWidget->setGeometry(geometry().left(),geometry().bottom()+3,450,200);
    //tty.addWidget(consoleWidget);

    ui->plainTextEdit->setTextInteractionFlags(Qt::NoTextInteraction);
    tty.addWidget(ui->plainTextEdit);

    tty << "MainWindow::MainWindow()\n";

    if(configFile) {
        openSulConfig(configFile);
    }
}

//-----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    //QMessageBox::information(this, tr("Конец"), tr("Да! Да!"));

    tty << "MainWindow::~MainWindow()\n";

    if(cw) delete cw;
    if(bw) delete bw;
    if(ew) delete ew;
    if(rw) delete rw;
    if(dw) delete dw;
    if(tw) delete tw;

    close();

    //if(consoleWidget) {
    //    consoleWidget->close();
    //    delete consoleWidget;
    //}
    //tty << "MainWindow::~MainWindow(): delete console interface\n";

    delete ui;
    tty << "MainWindow::~MainWindow(): delete user interface\n";

    if(sul) {
        delete sul;
        sul = NULL;
        tty << "MainWindow::~MainWindow(): delete sul\n";
    }

    if(hlibSul) {
        FreeLibrary(hlibSul);
        hlibSul = NULL;
        tty << "MainWindow::~MainWindow(): free sul library\n";
    }

    if(hlibDev) {
        FreeLibrary(hlibDev);
        hlibDev = NULL;
        tty << "MainWindow::~MainWindow(): free dev library\n";
    }

    tty << "MainWindow::~MainWindow(): application exit\n";
}

//-----------------------------------------------------------------------------

void MainWindow::newDeviceConnected(device *newDev)
{

    if(!newDev)
        return;

    tty << "MainWindow::newDeviceConnected()\n";

    dev = newDev;
}

//-----------------------------------------------------------------------------

void MainWindow::newSulConnected(sul_base *newSul)
{
    if(!newSul)
        return;

    tty << "MainWindow::newSulConnected()\n";

    sul = newSul;

    if(bw) {
        delete bw;
        bw = NULL;
        actBeam_triggered();
    }
    if(ew) {
        delete ew;
        ew = NULL;
        actEeprom_triggered();
    }
    if(rw) {
        delete rw;
        rw = NULL;
        actRam_triggered();
    }
    if(dw) {
        delete dw;
        dw = NULL;
        actDebug_triggered();
    }
    if(tw) {
        delete tw;
        tw = NULL;
        actTuneExt_triggered();
    }
}

//-----------------------------------------------------------------------------

void MainWindow::actConfig_triggered()
{
    if(!cw) {
        cw = new configwidget(tr("..\\bin\\config\\exchange"),tty,this);
        connect(cw,SIGNAL(newDevice(device*)),this,SLOT(newDeviceConnected(device*)));
    }

    cw->show();
}

//-----------------------------------------------------------------------------

void MainWindow::actBeam_triggered()
{
    if(!bw)
        bw = new beamwidget(tty,sul,this);
    bw->show();
}

//-----------------------------------------------------------------------------

void MainWindow::actEeprom_triggered()
{
    if(!ew)
        ew = new eepromwidget(tty,sul,this);
    ew->show();
}

//-----------------------------------------------------------------------------

void MainWindow::actRam_triggered()
{
    if(!rw)
        rw= new ramwidget(this,&tty);
    rw->show();
}

//-----------------------------------------------------------------------------

void MainWindow::actDebug_triggered()
{
    if(!dw)
        dw = new dbgwidget(tty,sul,this);
    dw->show();
}

//-----------------------------------------------------------------------------

void MainWindow::actExit_triggered()
{
    close();
}

//-----------------------------------------------------------------------------

void MainWindow::actTuneExt_triggered()
{
    if(!tw) {
        if(sul) {
            tw = new tunewidget(tty,sul,this);
        } else {
            bar->showMessage(tr("Необходимо выбрать систему СУЛ!"));
            return;
        }
    }
    tw->show();
}

//-----------------------------------------------------------------------------

void MainWindow::actDeleteObject_triggered()
{
    tty << "MainWindow::actDeleteObject_triggered()\n";

    if(cw) delete cw;
    if(bw) delete bw;
    if(ew) delete ew;
    if(rw) delete rw;
    if(dw) delete dw;
    if(tw) delete tw;

    cw = NULL;
    bw = NULL;
    ew = NULL;
    rw = NULL;
    dw = NULL;
    tw = NULL;

    if(sul) {
        delete sul;
        sul = NULL;
        tty << "delete SUL object" << "\n";
    }

    if(dev) {
        delete dev;
        dev = NULL;
        tty << "delete DEV object" << "\n";
    }

    if(hlibSul) {
        FreeLibrary(hlibSul);
        hlibSul = NULL;
        tty << "free SUL library" << "\n";
    }

    if(hlibDev) {
        FreeLibrary(hlibDev);
        hlibDev = NULL;
        tty << "free DEV library" << "\n";
    }
}

//-----------------------------------------------------------------------------

void MainWindow::actConsole_triggered()
{
/*
    if(consoleWidget->isVisible()) {
        consoleWidget->close();
    } else {
        consoleWidget->setGeometry(geometry().left(),geometry().bottom()+3,450,200);
        consoleWidget->show();
    }
*/
}

//-----------------------------------------------------------------------------

void MainWindow::parseConfigFile(const char *file)
{
        tty << "sul_monitor::parseConfigFile(" << file << ")" << "\n";

        QSettings *settings = new QSettings( file, QSettings::IniFormat );
        libSul = settings->value("LIBSUL", "UNKNOWN");
        libDev = settings->value("LIBDEV", "UNKNOWN");
        ifc = settings->value("INTERFACE", "UNKNOWN");
        speed = settings->value("INTERFACE_SPEED", "115200");
        excel = settings->value("CONFIG_EXCEL", NULL);
        flash = settings->value("CONFIG_FLASH", NULL);
        ram = settings->value("CONFIG_RAM", NULL);
        vid = settings->value("CONFIG_VID", NULL);
        Abon = settings->value("ABONENTS", "0");
        Chan = settings->value("ABONENTS_CHANNELS", "128");
        dx_step1 = settings->value("STEP_DX1", "0");
        dy_step1 = settings->value("STEP_DY1", "0");
        dx_step2 = settings->value("STEP_DX2", "0");
        dy_step2 = settings->value("STEP_DY2", "0");

        tty << "\n";
        tty << "LIBSUL: "  << libSul.toString().toStdString().c_str() << "\n";
        tty << "LIBDEV: "  << libDev.toString().toStdString().c_str() << "\n";
        tty << "INTERFACE: "  << ifc.toString().toStdString().c_str() << "\n";
        tty << "INTERFACE_SPEED: "  << speed.toString().toStdString().c_str() << "\n";
        tty << "CONFIG_EXCEL: "  << excel.toString().toStdString().c_str() << "\n";
        tty << "CONFIG_FLASH: "  << flash.toString().toStdString().c_str() << "\n";
        tty << "CONFIG_RAM: "  << ram.toString().toStdString().c_str() << "\n";
        tty << "CONFIG_VID: "  << vid.toString().toStdString().c_str() << "\n";
        tty << "ABONENTS: "  << Abon.toString().toStdString().c_str() << "\n";
        tty << "ABONENTS_CHANNELS: "  << Chan.toString().toStdString().c_str() << "\n";
        tty << "STEP_DX1: "  << dx_step1.toString().toStdString().c_str() << "\n";
        tty << "STEP_DY1: "  << dy_step1.toString().toStdString().c_str() << "\n";
        tty << "STEP_DX2: "  << dx_step2.toString().toStdString().c_str() << "\n";
        tty << "STEP_DY2: "  << dy_step2.toString().toStdString().c_str() << "\n";

        // считаем значения из файла конфигурацци
        vector<double> litera;
        litera.clear();
        for(int i=1; i<=8; i++) {
            QString str("L");
            QString param = str + QString::number(i);
            QVariant val = settings->value(param, "12345.0");
            if(val.toDouble() != 12345.0) {
                litera.push_back(val.toDouble());
                tty << "L: " << val.toDouble() << "\n";
            }
        }
        tty << "\n";

        delete settings;

        QString msg = tr("Интерфейс: ") + ifc.toString()
                      +  ",  " + speed.toString()
                      +  ",  " + libDev.toString()
                      +  ",  " + tr("СУЛ: ") + libSul.toString()
                      +  ",  " + flash.toString() + ",  " + ram.toString();

        bar->showMessage(msg);
}

//-----------------------------------------------------------------------------

void MainWindow::openSulConfig(const char *cmdlineConfigFile)
{
    tty << "void MainWindow::openSulConfig()\n";

    QString fileName;

    if(cmdlineConfigFile) {
        fileName = cmdlineConfigFile;
    } else {
        fileName = getFileName();
    }

    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл конфигурации СУЛ"));
        return;
    } else {
        bar->showMessage(tr("Файл конфигурации: ") + fileName);
        tty << fileName.toStdString().c_str() << "\n";
    }

    parseConfigFile( fileName.toStdString().c_str() );

    //loadDevLibrary(libDev.toString());
    loadSulLibrary(libSul.toString());
}

//-----------------------------------------------------------------------------

void MainWindow::loadSulLibrary(QString libNameSul)
{
    tty << "loadSulLibrary(" << libNameSul.toStdString().c_str() << ")" << "\n";
/*
    if(!dev) {
        QString s = tr("Ошибка! Необходимо выбрать интерфейс связи с СУЛ.");
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        return;
    }
*/
    if(sul) {
        delete sul;
        sul = NULL;
    }

    if(hlibSul) {
        FreeLibrary(hlibSul);
        hlibSul = NULL;
    }

    hlibSul = LoadLibraryA(libNameSul.toStdString().c_str());
    if(!hlibSul) {
        QString s = tr("Ошибка! Не могу загрузить библиотеку СУЛ: ") + libNameSul;
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        exit(111);
    }

    factorySul = (sul_factory)GetProcAddress(hlibSul,"create_sul");
    if(!factorySul) {
        QString s = tr("Ошибка! Не могу получить адрес функции create_sul() из библиотеки: ") + libNameSul;
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        FreeLibrary(hlibSul);
        exit(222);
    }

    tty << "Get factory address: create_sul() - Ok" << "\n";

    sul = factorySul(dev,
                     excel.toByteArray().data(),
                     flash.toByteArray().data(),
                     ram.toByteArray().data(),
                     vid.toByteArray().data(),
                     dx_step2.toDouble(),
                     dy_step2.toDouble() );
    if(!sul) {
        QString s = tr("Ошибка! Ошибка подключения к СУЛ.");
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        FreeLibrary(hlibSul);
        exit(333);
    } else {
        tty << "Create SUL object - Ok" << "\n";
    }

    //tty << "Scanning active modules..." << "\n";
    //int active_modules = sul->sul_rescan_modules();
    //tty << "Found: " << active_modules << " modules." << "\n";

    newSulConnected(sul);
}

//-----------------------------------------------------------------------------

void MainWindow::loadDevLibrary(QString libNameDev)
{
    if(dev) {
        delete dev;
        dev = NULL;
    }

    if(hlibDev) {
        FreeLibrary(hlibDev);
        hlibDev = NULL;
    }

    tty << "loadDevLibrary(" << libNameDev.toStdString().c_str() << ")" << "\n";

    hlibDev = LoadLibraryA(libNameDev.toStdString().c_str());
    if(!hlibDev) {
        QString s = tr("Ошибка! Не могу загрузить библиотеку связи с СУЛ: ") + libNameDev;
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        exit(333);
    }

    factoryDev = (dev_factory)GetProcAddress(hlibDev,"create_io_device");
    if(!factoryDev) {
        QString s = tr("Ошибка! Не могу получить адрес функции create_io_device() из библиотеки: ") + libNameDev;
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        FreeLibrary(hlibDev);
        exit(444);
    }

    tty << "Get factory address: create_io_device() - Ok" << "\n";

    dev = factoryDev(ifc.toByteArray().data(), FILE_FLAG_NO_BUFFERING, speed.toInt());

    if(!dev->device_is_open()) {
        QString s = tr("Ошибка! Устройство не готово. Выберите другой интерфейс") + libNameDev;
        QMessageBox::information(this, tr("Монитор СУЛ"), s);
        FreeLibrary(hlibDev);
        exit(444);
    } else {
        tty << "Create DEV object - Ok" << "\n";
    }
}

//-----------------------------------------------------------------------------

void MainWindow::autoConfig()
{
    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл конфигурации СУЛ"));
        return;
    } else {
        bar->showMessage(tr("Файл конфигурации: ") + fileName);
        tty << fileName.toStdString().c_str() << "\n";
    }

    parseConfigFile( fileName.toStdString().c_str() );

    loadDevLibrary(libDev.toString());
    loadSulLibrary(libSul.toString());
}

//-----------------------------------------------------------------------------

QString MainWindow::getFileName()
{
    QFileDialog *fileDialog = new QFileDialog();
    QString fileName = fileDialog->getOpenFileName(0, tr("Открыть файл"),".",tr("config files (*.cfg)"));
    delete fileDialog;
    return fileName;
}
