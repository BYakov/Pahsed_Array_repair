#ifndef SUL_MONITOR_H
#define SUL_MONITOR_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QMessageBox>
#include <QFileDialog>
#endif
#include <QSettings>
#include <QStandardItemModel>

//-----------------------------------------------------------------------------

#ifndef _SUL_BASE_H_
    #include "sul_base.h"
#endif
#ifndef _DEVICE_H_
    #include "device.h"
#endif
#ifndef _SUL_PROTOCOL_H_
    #include "sul_protocol.h"
#endif
#ifndef _SCANNER_H_
    #include "scanner.h"
#endif
#ifndef _ANGLE_CORRECT_H_
    #include "angle_correct.h"
#endif
#ifndef _VID_DATA_H_
    #include "vid_data.h"
#endif
#ifndef _CROSS_H_
    #include "cross.h"
#endif

//-----------------------------------------------------------------------------

#include "ui_sul_monitor.h"
#include "sul_graph.h"
#include "sul_analizer.h"
#include "sul_array.h"
#include "worker_thread.h"
#include "sulTestWidget.h"
#include "sulTableView.h"
#include "sulParamWidget.h"
#include "antenna.h"

//-----------------------------------------------------------------------------

#define SYSTEM_CONFIG_FILE ".\\config\\system.cfg"

//-----------------------------------------------------------------------------

enum sul_type {
        SUL_AVR,
        SUL_MDO,
        SUL_MDO72,
        SUL_BMK
};

//-----------------------------------------------------------------------------

enum ifc_type {
        COM1,
        COM2,
        COM3,
        COM4
};

//-----------------------------------------------------------------------------

class sul_monitor : public QWidget
{
        Q_OBJECT
public:
        sul_monitor(const char *cfgFile, QWidget *parent = 0, Qt::WindowFlags flags = 0, bool mode = false);
        ~sul_monitor();

private:
        Ui::sul_monitorClass            ui;

        HMODULE                         hlibDev;
        dev_factory                     factoryDev;

        HMODULE                         hlibSul;
        sul_factory                     factorySul;

        QStatusBar			*bar;
        QTimer				*timer;
        QTimer				*beamTimer;
        QTimer				*dbg_timer;
        QTimer				*display_timer;
        int                 display_timer_counter;
        QSettings			*settings;

        QStandardItemModel		*model1;
        QStandardItemModel		*model2;
        QStandardItemModel		*model3;

        QStandardItemModel		*fmodel;
        QStandardItemModel		*rmodel;

        SulTableView                    *ftable;
        SulTableView                    *rtable;
        SulTableView                    *tableHdr;
        SulTableView                    *tableOut;
        SulTableView                    *tableIn;

        antenna                         *radar;
        sul_graph			*graph;
        sul_channel_analizer            *analizer;
        worker_thread			*worker;

        //объекты СУЛ
        protocol			*exchange;
        scanner				*scan;
        device				*dev;
        sul_base			*sul;

        std::vector<double>			userChannelData;

        // имя конфигурационного файла
        QString				configFile;
        // имя загружаемой библиотеки реализующий интерфейс устройства обмена
        QString				libNameDev;
        // имя загружаемой библиотеки СУЛ
        QString				libNameSul;
        // имя интерфейса связи
        QString				ifcName;
        // скорость обмена по интерфейсу связи
        int				ifcSpeed;

        // Файл конфигурации EXCEL
        QString				cfg_excel;
        // Файл конфигурации FLASH
        QString				cfg_flash;
        // Файл конфигурации RAM
        QString				cfg_ram;
        // Файл конфигурации заводских номеров и адресов
        QString				cfg_vid;

        // Определяются из файла инициализации
        // количество абонентов СУЛ
        int				n_abonents;
        // количество каналов абонента
        int				n_channels;

        // количество каналов СУЛ
        int				n_sul_channels;
        // Шаг между элементами решетки вдоль Ох
        double				grid_dX1;
        // Шаг между элементами решетки вдоль Оy
        double				grid_dY1;
        // Шаг между элементами решетки вдоль Ох
        double				grid_dX2;
        // Шаг между элементами решетки вдоль Оy
        double				grid_dY2;
        // Литеры для рассчета углов отклонений
        std::vector<double>             litera;
        // параметры заводских номеров модулей и соответствующих им адресов
        //vector<struct vendor_data>      vdata;

        // Код задачи запущенной на выполнение в потоке worker
        int                             last_started_task;
        bool                            advanced_mode;

        void load_sul_library();
        void load_dev_library();

        void create_dispaly();
        void delete_dispaly();
        void connect_slots();
        void config_system();
        void create_system();
        void delete_system();
        void update_screen();

        void fill_abonent_form();
        void fill_table(QAbstractItemModel *model, const std::vector<double>& data);

        void fill_header_table();
        void fill_output_table();
        void fill_input_table();

        void set_table_view(QTableView *t, int rowh=23, int colw=43);

        void update_ram_dispaly();
        void update_flash_dispaly();

protected:
        void closeEvent(QCloseEvent * event);

        public slots:
                void start_scanner();
                void stop_scanner();
                void step_scanner();
                void set_scanner();
                void setup_beam();
                void update_scanner_info();

                void dr_change();
                void x0_change(double X);
                void y0_change(double Y);
                void angle_change();
                void sector_max_change();
                void axis_change();

                void timer_event();

                void tool_change(int index=0);

                void prepare_abonent_request();
                void dbg_timer_event();
                void send_abonent_request();

                void fill_flash();
                void open_flash();
                void erase_flash();
                void load_flash();
                void save_flash();

                void fill_ram();
                void set_ram();
                void inc_ram_value();
                void dec_ram_value();
                void open_ram();
                void erase_ram();
                void load_ram_all();
                void save_ram_all();
                void save_ram_abonent();
                void read_ram_abonent();

                void show_beam_position();

                void processing_status(int status, int task_code);
                void display_timer_event();

                void set_antenna_params_flash();
                void set_antenna_params_ram();
                void set_dbgtimer(int val);

                void update_abonent_address(int index);
                void update_abonent_firmware(int index);

                void update_beam_position(double X, double Y);

                void flashItemChanged( int value, int offset );
                void ramItemChanged( int value, int offset );

                void measureSetParam();

                void vendorSetParam();
                void vendorParamUpdate(int value);

                void beamSetupTimerOn(bool checked);

                void ramItemChanged( const QModelIndex &index );
                void show_user_data();

                void CalcualteCorrectionCodes();
                void SaveCorrectionCodes();
                void LoadCorrectionCodes();

                void interface_update();
                void debug_button();
                void litera_changed();
                QString getFileName(QString filter);

private slots:
                void RescanModule();
                void show_antenna();
signals:
                void RepaintAntennaWidget();
};

//-----------------------------------------------------------------------------

#endif // SUL_MONITOR_H

