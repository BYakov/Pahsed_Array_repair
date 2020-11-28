#ifndef SUL_MONITOR_H
#define SUL_MONITOR_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QStandardItemModel>

#include "ui_sul_monitor.h"
#include "sul_graph.h"
#include "sul_analizer.h"
#include "sul_array.h"
#include "worker_thread.h"
#include "sul_test.h"
#include "sul_tune_widget.h"

#include "process_type.h"
#include "sul_tune.h"
#include "sul_mdo.h"
#include "sul_bmk.h"
#include "serial.h"
#include "scanner.h"
#include "packet485.h"
#include "angle_correct.h"

//-----------------------------------------------------------------------------

#define SYSTEM_CONFIG_FILE ".\\config\\system.cfg"

//-----------------------------------------------------------------------------

#define ENTRY_ON_PAGE	    5
#define PAGE_NUMEBER	    MAX_ABONENT_NUMBER/ENTRY_ON_PAGE

//-----------------------------------------------------------------------------

enum sul_type {
        SUL_AVR,
        SUL_MDO,
        SUL_BMK,
};

//-----------------------------------------------------------------------------

enum ifc_type {
        COM1,
        COM2,
        COM3,
        COM4,
};

//-----------------------------------------------------------------------------

class worker_thread;

//-----------------------------------------------------------------------------

class sul_monitor : public QWidget
{
        Q_OBJECT
public:
        sul_monitor(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~sul_monitor();

private:
        Ui::sul_monitorClass            ui;
        QStatusBar			*bar;
        QTimer				*timer;
        QTimer				*dbg_timer;
        QTimer				*display_timer;
        int				display_timer_counter;
        QSettings			*settings;

        QStandardItemModel		*model1;
        QStandardItemModel		*model2;
        QStandardItemModel		*model3;

        QStandardItemModel		*fmodel;
        QStandardItemModel		*rmodel;

        sul_array                       *grid;
        sul_test_widget			*test;
        sul_graph			*graph;
        sul_channel_analizer            *analizer;
        worker_thread			*worker;
        sul_tune_widget			*tune;

        //объекты СУЛ
        packet485			*p485;
        scanner				*scan;
        device				*dev;
        angle				*ang;
        sul_base			*sul;

        // Определяются из файла инициализации
        // количество абонентов СУЛ
        int				n_abonents;
        // количество каналов одного абонента
        int				n_channels;
        // количество каналов СУЛ
        int				n_sul_channels;
        // тип СУЛ
        sul_type			sul_t;
        // тип интерфейса связи
        QString				ifc_t;
        // Файл конфигурации FLASH
        QString				cfg_flash;
        // Файл конфигурации RAM
        QString				cfg_ram;


        void create_dispaly();
        void delete_dispaly();
        void connect_slots();
        void config_system();
        void create_system();
        void delete_system();
        void update_screen();

        void fill_abonent_form();
        void fill_table(QAbstractItemModel *model, unsigned char *data, int n);

        void fill_header_table();
        void fill_output_table();
        void fill_input_table();

        void set_table_view(QTableView *t, int rowh=23, int colw=41);

protected:
        void closeEvent(QCloseEvent * event);

        public slots:
                void start_scanner();
                void stop_scanner();
                void step_scanner();
                void set_scanner();
                void setup_beam();

                void dr_change();
                void angle_change();
                void sector_max_change();
                void axis_change();

                void timer_event();

                void iface_change();

                void tool_change(int index=0);
                void fill_ram();
                void fill_flash();

                void prepare_abonent_request();
                void dbg_timer_event();
                void send_abonent_request();

                void zone_change();

                void open_flash();
                void erase_flash();
                void load_flash();
                void check_flash();

                void set_ram();
                void inc_ram_value();
                void dec_ram_value();
                void open_ram();
                void erase_ram();
                void load_ram();
                void save_ram();

                void show_beam_position();
                void test_widget();

                void processing_status(int status);
                void display_timer_event();

                void set_antenna_params();
                void set_dbgtimer(int val);

                void update_abonent_address(int val);
                void new_cfg_file_create();

                void update_beam_position(int X, int Y);
                void restart_system();
};

//-----------------------------------------------------------------------------

class worker_thread : public QThread
{
    Q_OBJECT

public:
    worker_thread();
    worker_thread(sul_base *Sul);
    virtual ~worker_thread();

private:
    sul_base *sul;
    bool exit_ok;
    bool paused;
    int  task_code;
    int	 pulse_count;

    virtual void run();

public:
    void set_task(int task);
    void start_task(int task);
    void stop_task();
    void pause_task(bool state);

signals:
    void task_status(int status);
};

//-----------------------------------------------------------------------------

#endif // SUL_MONITOR_H

