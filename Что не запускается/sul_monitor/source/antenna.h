#ifndef ANTENNA_H
#define ANTENNA_H

#include "sul_base.h"
#include "sul_channel_data.h"
#include "array_antenna.h"
#include "task_thread.h"
#include "setChannelPhase.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QMessageBox>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QGridLayout>
#include <QMainWindow>
#include <QLabel>
#include <QRadioButton>
#include <QTextCodec>
#include <QPushButton>
#include <QThread>
#include <QProgressBar>
#include <QToolBar>
#include <QGridLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QMessageBox>
#endif
#include <QTextCodec>
#include <QThread>

namespace Ui {
    class antenna;
}

//----------------------------------------------------------------------

struct param_t {
    int param_value;
    int text_value;
};

//----------------------------------------------------------------------

class antenna : public QMainWindow
{
    Q_OBJECT

public:
    explicit antenna(sul_base *sul, QWidget *parent = 0);
    ~antenna();

public slots:
    void setup_sul();
    void mouse_pressed(int X, int Y, QMouseEvent *event);
    void update_channel_info();
    void update_screen();

    void index_change(int index);
    void set_test_mode(bool mode);
    void select_test();
    void start_test();

    void task_complete();
    int  show_const_param();
    int  show_flash_param();
    int  show_ram_param();
    int  show_test_param();
    int  show_param();
    void debug_slot();

signals:
    void selected_channel(struct channel_t info);
    void repaint_antenna();

private:
    Ui::antenna *ui;
    sul_base *m_sul;
    array_antenna *m_array;
    struct channel_t m_channel;
    std::vector<double> m_parameters;
    QStatusBar *m_bar;
    int m_param_id;
    int m_test_id;
    task_thread *m_thread;
    set_channel_phase *m_legend;

    static int task(int command, void *param, int param_index);
};

//----------------------------------------------------------------------

#endif // ANTENNA_H
