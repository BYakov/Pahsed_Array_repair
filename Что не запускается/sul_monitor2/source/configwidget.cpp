#include "configwidget.h"
#include "ui_configwidget.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------

configwidget::configwidget(const QString &path, console& log, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::configwidget), tty(log)
{
    ui->setupUi(this);
    bar = statusBar();
    interface_list.clear();
    device_list.clear();
    param_list.clear();

    QStringList filters;
    filters << "*.dll" << "*.DLL";

    dir = new QDir( path );
    dir->setNameFilters(filters);

    QStringList files = dir->entryList();

    for(int i=0; i<files.size(); i++) {
        interface_list.push_back(files.at(i));
    }

    setup_interface_list(interface_list);

    interfaceChanged(ui->cbIfcAvailable->currentText());

    connect(ui->cbIfcAvailable,SIGNAL(currentIndexChanged(QString)),this,SLOT(interfaceChanged(QString)));
    connect(ui->pbConnectDevice,SIGNAL(clicked(bool)),this,SLOT(connectDevice(bool)));
    connect(ui->pbWriteData,SIGNAL(clicked()),this,SLOT(WriteData()));
    connect(ui->pbReadData,SIGNAL(clicked()),this,SLOT(ReadData()));

    hlib = NULL;
    dev.clear();

    tty << "configwidget::configwidget(" << path.toAscii().data() << ")\n";
}

//-----------------------------------------------------------------------------

configwidget::~configwidget()
{
    close();

    delete ui;
    delete dir;

    interface_list.clear();
    device_list.clear();
    param_list.clear();

    disconnect_devices();

    if(hlib) FreeLibrary(hlib);

    dev.clear();
    hlib = NULL;

    tty << "configwidget::~configwidget()\n";
}

//-----------------------------------------------------------------------------

void configwidget::setup_interface_list(vector<QString> &ifc_list)
{
    ui->cbIfcAvailable->clear();
    for(unsigned i=0; i<ifc_list.size(); i++) {
        ui->cbIfcAvailable->addItem(ifc_list.at(i));
    }
}

//-----------------------------------------------------------------------------

void configwidget::setup_device_list(vector<QString> &dev_list)
{
    ui->cbDeviceName->clear();
    for(unsigned i=0; i<dev_list.size(); i++) {
        ui->cbDeviceName->addItem(dev_list.at(i));
    }
}

//-----------------------------------------------------------------------------

void configwidget::setup_param_list(vector<QString> &param_list)
{
    ui->cbDeviceParam->clear();
    for(unsigned i=0; i<param_list.size(); i++) {
        ui->cbDeviceParam->addItem(param_list.at(i));
    }
}

//-----------------------------------------------------------------------------

int configwidget::enum_serial()
{
    device_list.clear();

    for(unsigned i=1; i<=12; i++) {

        QString pn = "COM" + QString::number(i);

        HANDLE h = CreateFileA(
                pn.toAscii().data(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL);

        if(h == (HANDLE)-1) {
            tty << "Serial port: " << pn.toAscii().data() << " not accessible\n";
            h = 0;
        } else {
            device_list.push_back(pn);
            CloseHandle(h);
            tty << "Serial port: " << pn.toAscii().data() << " accessible\n";
        }
    }

    return device_list.size();
}

//-----------------------------------------------------------------------------

int configwidget::enum_usb()
{
    /*
    device_list.clear();

    QString pn = "\\\\.\\ArmUsbDevice0";

    HANDLE h = CreateFileA(
            pn.toAscii().data(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

    if(h == (HANDLE)-1) {
        tty << "Serial port: " << pn.toAscii().data() << " not accessible" << endl;
        h = 0;
    } else {
        device_list.push_back(pn);
        CloseHandle(h);
        tty << "Serial port: " << pn.toAscii().data() << " accessible" << endl;
    }

    return device_list.size();
*/
    return 0;
}

//-----------------------------------------------------------------------------

int configwidget::enum_network()
{
    /*
    device_list.clear();
    return device_list.size();
*/
    return 0;
}

//-----------------------------------------------------------------------------

void configwidget::interfaceChanged(QString ifc)
{
    device_list.clear();
    param_list.clear();

    const char *lib = ifc.toAscii().data();

    if(strcmp(lib,"usb_exch.dll") == 0) {

        enum_usb();
        device_list.push_back("\\\\.\\ArmUsbDevice0");
        param_list.push_back("0");

    }
    if(strcmp(lib,"serialnet_exch.dll") == 0) {

        enum_network();
        device_list.push_back("COM2");
        param_list.push_back("115200");
        param_list.push_back("57600");

    }
    if(strcmp(lib,"net_exch.dll") == 0) {

        enum_network();
        device_list.push_back("127.0.0.1");
        param_list.push_back("5025");

    }
    if(strcmp(lib,"serial_exch.dll") == 0) {

        enum_serial();
        param_list.push_back("115200");
        param_list.push_back("57600");
    }

    setup_device_list(device_list);
    setup_param_list(param_list);

    if(device_list.empty()) {
        ui->pbConnectDevice->setEnabled(false);
    } else {
        ui->pbConnectDevice->setEnabled(true);
    }
}

//-----------------------------------------------------------------------------

void configwidget::connectDevice(bool checked)
{
    QString libName = dir->path() + "/" + ui->cbIfcAvailable->currentText();

    free_library( libName );
    load_library( libName );
    connect_device( ui->cbDeviceName->currentText(), ui->cbDeviceParam->currentText() );

    interfaceChanged(ui->cbIfcAvailable->currentText());

    bar->showMessage(tr("Текущий интерфейс: ") + ui->cbIfcAvailable->currentText());

    if(dev.size()) {
        emit newDevice(dev.at(dev.size()-1));
    }
}

//-----------------------------------------------------------------------------

void configwidget::load_library( const QString &libName )
{
    if(!hlib) {

        hlib = LoadLibraryA(libName.toAscii().data());
        if(!hlib) {
            QString s = tr("Ошибка! Не могу загрузить библиотеку интерфейса связи с СУЛ: ") + libName;
            QMessageBox::information(this, tr("Настройка"), s);
            exit(333);
        }
        currentLib = libName;

        emit newInterface(libName);
    }
}

//-----------------------------------------------------------------------------

void configwidget::free_library( const QString &libName )
{
    // сменилась загружаемая библиотека
    if(currentLib != libName) {

        // освободим ресурсы из текущей библиотеки, если они были выделены
        if(hlib) {
            disconnect_devices();
            FreeLibrary(hlib);
            hlib = NULL;
            currentLib.clear();
        }
    }
}

//-----------------------------------------------------------------------------

void configwidget::connect_device( const QString &deviceName, const QString &param )
{
    if(!hlib) {
        QString s = tr("Ошибка! Библиотека интерфейса связи с СУЛ не загружена");
        QMessageBox::information(this, tr("Настройка"), s);
        exit(555);
        return;
    }

    dev_factory entry = (dev_factory)GetProcAddress(hlib,"create_io_device");
    if(!entry) {
        QString s = tr("Ошибка! Не могу получить адрес функции create_io_device() из библиотеки интерфейса связи с СУЛ!");
        QMessageBox::information(this, tr("Настройка"), s);
        FreeLibrary(hlib);
        hlib = NULL;
        exit(444);
    }

    device *d = entry(deviceName.toAscii().data(), FILE_FLAG_NO_BUFFERING, param.toInt());
    if(!d->device_is_open()) {
        QMessageBox::information(this, tr("Настройка"), tr("Ошибка! Устройство не может быть проинициализировано."));
        delete d;
        FreeLibrary(hlib);
        hlib = NULL;
        exit(555);
    }

    dev.push_back(d);
}

//-----------------------------------------------------------------------------

void configwidget::disconnect_devices()
{
    for(unsigned i=0; i<dev.size(); i++) {
        if(dev.at(i)) delete dev.at(i);
    }
}

//-----------------------------------------------------------------------------

void configwidget::WriteData()
{
    if(dev.empty()) {
        QMessageBox::information(this, tr("Настройка"), tr("Ошибка! Устройство не открыто!"));
        return;
    }

    static unsigned char counter = 0;

    unsigned char data[10];

    counter++;

    for(unsigned i=0; i<10; i++)
        data[i] = counter;

    data[0] = 0x55;
    data[9] = 0xAA;

    int res = dev[0]->device_data_write(data,10);

    tty << "configwidget::WriteData(): write " << res << " bytes \n";
}

//-----------------------------------------------------------------------------

void configwidget::ReadData()
{
    if(dev.empty()) {
        QMessageBox::information(this, tr("Настройка"), tr("Ошибка! Устройство не открыто!"));
        return;
    }

    if(dev.size() < 2) {
        QMessageBox::information(this, tr("Настройка"), tr("Ошибка! Открыто только одно устройство!"));
        return;
    }

    static unsigned char counter = 0;

    unsigned char data[10] = {0x55};

    for(unsigned i=0; i<10; i++)
        data[i] = 0;

    counter++;

    int res = dev[1]->device_data_read(data,10);
    tty << "configwidget::ReadData(): read " << res << " bytes \n";

    if(res > 0) {
        for(unsigned i=0; i<10; i++) {
            tty << i << ": " << int(data[i]) << "\n";
        }
    }
}
