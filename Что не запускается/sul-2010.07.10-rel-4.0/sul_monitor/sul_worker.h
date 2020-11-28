#ifndef SUL_MONITOR_H
#define SUL_MONITOR_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QStandardItemModel>

#include "ui_sul_monitor.h"

#include "..\sul_src\sul_mdo.h"
#include "..\sul_src\sul_avr.h"
#include "..\sul_src\serial.h"
#include "..\sul_src\scanner.h"
#include "..\sul_src\packet485.h"
#include "..\sul_src\angle_correct.h"

#define SYSTEM_CONFIG_FILE ".\\config\\system.cfg"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class sul_channel_analizer : public QWidget
{
        Q_OBJECT

private:
        QAbstractItemModel  *m;
        QStatusBar          *bar;
        int                 square_size;

public:
        sul_channel_analizer(QAbstractItemModel *m, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~sul_channel_analizer();

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);

public:
        void set_model(QAbstractItemModel *m);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class sul_graph : public QWidget
{
	Q_OBJECT

private:
	scanner	*scan;

	QLabel *X;
	QLabel *Y;

public:
	sul_graph(scanner *scan = NULL, QWidget *parent = 0, Qt::WFlags flags = 0);
	~sul_graph();


protected:
	void paintEvent(QPaintEvent *event);

public:
	void repaint();

};

//-----------------------------------------------------------------------------

enum sul_type {
	SUL_AVR,
	SUL_MDO,
};

//-----------------------------------------------------------------------------

enum ifc_type {
	IFC_RS232_1,
	IFC_RS232_2,
	IFC_RS485_1,
	IFC_RS485_2,
};

//-----------------------------------------------------------------------------
class worker_thread : public QThread {

    explicit worker_thread::worker_thread(void *sul);
    virtual ~worker_thread();

private:
    void run();

public:
    int start_task();
    int stop_task();
};
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
	QSettings			*settings;

	QStandardItemModel		*model1;
	QStandardItemModel		*model2;
	QStandardItemModel		*model3;

        QStandardItemModel		*fmodel[5];
        QStandardItemModel		*rmodel[5];

        QTableView                      *ftable[5];
        QTableView                      *rtable[5];

	sul_graph			*graph;
        sul_channel_analizer            *channel;

	//объекты СУЛ
	packet485			*p485;
	scanner				*scan;
	device				*dev;
	angle				*ang;
	sul_base			*sul;

	// тип системы СУЛ
        sul_type			sul_t;
	// тип интерфейса связи
        ifc_type			ifc_t;
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

	void fill_abonent_form();
        void fill_table(QAbstractItemModel *model, unsigned char *data, int n);
	
	void fill_header_table();
	void fill_output_table();
	void fill_input_table();

        void set_table_view(QTableView *t, int rowh=22, int colw=35);

protected:
	void closeEvent(QCloseEvent * event);  

	public slots:
		void start_scanner();
		void stop_scanner();
		void step_scanner();
		void reset_scanner();

		void dr_change();
		void x0_change();
		void y0_change();
		void angle_change();
		void sector_change();
		void sector_max_change();
		void axis_change();

		void timer_event();

		void iface_change();
		void draw_grid();

		void tool_change(int index=0);
		void fill_ram(int index=0);
		void fill_flash(int index=0);

                void detect_abonent_list();
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

                void show_view();
};

//-----------------------------------------------------------------------------

#endif // SUL_MONITOR_H

