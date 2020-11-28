#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include "device.h"
#include "console.h"

#include <QMainWindow>
#include <QDir>
#include <QRadioButton>
#include <QMessageBox>
#include <vector>

namespace Ui {
    class configwidget;
}

/*!
  ������ ��� ������ � ������������ ���������� ������.
  ��������� ������� ��������� ��������� � ����� ���������� � ������
  std::vector<device*> dev. ����� ����� ���������� ��������� ������������
  ��������� ��������� � ������������ ������ ������. ��� �������
  ��������������, ��� dev[0] ������������ ��� ������, �
  dev[1] - ��� ������ ������ �� ����������������� �����.
*/

class configwidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit configwidget(const QString &path, console& log, QWidget *parent = 0);
    ~configwidget();

private:
    Ui::configwidget *ui;
    QStatusBar *bar;
    QDir *dir;
    console& tty;

    std::vector<QString> interface_list;
    std::vector<QString> device_list;
    std::vector<QString> param_list;

    QString currentLib;
    HMODULE hlib;

    //! < ������ ��������� ������������ ��� ������� (����� �� ������ � �� ������)
    std::vector<device*> dev;

    int enum_serial();
    int enum_usb();
    int enum_network();

    void setup_interface_list(std::vector<QString> &ifc_list);
    void setup_device_list(std::vector<QString> &dev_list);
    void setup_param_list(std::vector<QString> &param_list);

    void load_library(const QString &libName);
    void free_library(const QString &libName);
    void connect_device(const QString &deviceName, const QString &param);
    void disconnect_devices();

private slots:
    void ReadData();
    void WriteData();
    void connectDevice(bool checked);
    void interfaceChanged(QString ifc);

signals:
    void newDevice(device *newDevice);
    void newInterface(QString newInterface);
};

#endif // CONFIGWIDGET_H
