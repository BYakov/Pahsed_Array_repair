#include "sul_monitor.h"

//-----------------------------------------------------------------------------

#define     DW  60
#define     DH  40
#define     MDX 10
#define     MDY 40

//-----------------------------------------------------------------------------

sul_monitor::sul_monitor(QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
        QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
        ui.setupUi(this);
        setMouseTracking(true);

        // вывод отладочных сообщений на панель
        bar = new QStatusBar();
        ui.barLayout->addWidget(bar);

        config_system();
        create_system();
        create_dispaly();
        connect_slots();
        setGeometry(MDX, MDY, geometry().width(), geometry().height());
        setFixedSize(geometry().width(),geometry().height());
        setWindowIcon(QIcon("icon\\monitor_icon.png"));
        set_antenna_params();
        update_screen();
}

//-----------------------------------------------------------------------------

sul_monitor::~sul_monitor()
{
}

//-----------------------------------------------------------------------------

void sul_monitor::create_dispaly()
{
        model1 = new QStandardItemModel(128, 1);
        model2 = new QStandardItemModel(128, 1);
        model3 = new QStandardItemModel(128, 1);

        ui.tblHdrOut->setModel(model1);
        ui.tblDataOut->setModel(model2);
        ui.tblDataIn->setModel(model3);

        switch(sul->flash_block_size()) {
        case 128: fmodel = new QStandardItemModel(8, 16); break;
        case 64:  fmodel = new QStandardItemModel(4, 16); break;
        case 4:  fmodel = new QStandardItemModel(1, 4); break;
        }
        switch(sul->ram_block_size()) {
        case 128: rmodel = new QStandardItemModel(8, 16); break;
        case 64:  rmodel = new QStandardItemModel(4, 16); break;
        case 4:  rmodel = new QStandardItemModel(1, 4); break;
        }

        ui.ftable->setModel(fmodel);
        ui.rtable->setModel(rmodel);

        set_table_view(ui.ftable);
        set_table_view(ui.rtable);

        ui.toolBox->setCurrentIndex(0);
        ui.spbAbonentIndex->setValue(1);

        ui.spbFlashAbonentNumber->setMaximum(sul->sul_total_abonents());
        ui.spbRamAbonentNumber->setMaximum(sul->sul_total_abonents());
 }

//-----------------------------------------------------------------------------

void sul_monitor::delete_dispaly()
{
        if(bar) delete bar;
        if(model1) delete model1;
        if(model2) delete model2;
        if(model3) delete model3;
}

//-----------------------------------------------------------------------------

void sul_monitor::closeEvent(QCloseEvent * event)
{
        delete_system();
}

//-----------------------------------------------------------------------------

void sul_monitor::connect_slots()
{
        // переинициализация системы
        connect(ui.btnRestartSystem,SIGNAL(clicked()),this,SLOT(restart_system()));

        // событие таймера
        connect(timer,SIGNAL(timeout()),this,SLOT(timer_event()));
        connect(dbg_timer,SIGNAL(timeout()),this,SLOT(dbg_timer_event()));
        connect(ui.period,SIGNAL(valueChanged(int)),this,SLOT(set_dbgtimer(int)));

        // смена интерфейса обмена
        connect(ui.rbtCOM1,SIGNAL(clicked()),this,SLOT(iface_change()));
        connect(ui.rbtCOM2,SIGNAL(clicked()),this,SLOT(iface_change()));
        connect(ui.rbtRS4851,SIGNAL(clicked()),this,SLOT(iface_change()));
        connect(ui.rbtRS4852,SIGNAL(clicked()),this,SLOT(iface_change()));

        // смена направления сканирования
        connect(ui.rbtAxisX,SIGNAL(clicked()),this,SLOT(axis_change()));
        connect(ui.rbtAxisY,SIGNAL(clicked()),this,SLOT(axis_change()));
        connect(ui.rbtAxisXY,SIGNAL(clicked()),this,SLOT(axis_change()));

        // запуск/останов периодического таймера
        connect(ui.btnStart,SIGNAL(clicked()),this,SLOT(start_scanner()));
        connect(ui.btnSetBeam,SIGNAL(clicked()),this,SLOT(setup_beam()));
        connect(graph,SIGNAL(set_beam_position(int,int)),this,SLOT(update_beam_position(int,int)));

        // изменение шага сканирования по Х или Y
        connect(ui.step_dr,SIGNAL(editingFinished()),this,SLOT(dr_change()));

        // изменение угла
        connect(ui.scanAngle,SIGNAL(editingFinished()),this,SLOT(angle_change()));

        // изменение границ
        connect(ui.scanSectorMax,SIGNAL(editingFinished()),this,SLOT(sector_max_change()));

        // заполнение таблиц
        connect(ui.toolBox,SIGNAL(currentChanged(int)),this,SLOT(tool_change(int)));
        connect(ui.spbRamAbonentNumber,SIGNAL(valueChanged(int)),this,SLOT(fill_ram()));
        connect(ui.spbFlashAbonentNumber,SIGNAL(valueChanged(int)),this,SLOT(fill_flash()));

        // заполнение данных FLASH
        connect(ui.spbSegmentNumber,SIGNAL(valueChanged(int)),this,SLOT(zone_change()));
        connect(ui.btnFlashFileOpen,SIGNAL(clicked()),this,SLOT(open_flash()));
        connect(ui.btnFlashErase,SIGNAL(clicked()),this,SLOT(erase_flash()));
        connect(ui.btnFlashLoad,SIGNAL(clicked()),this,SLOT(load_flash()));
        connect(ui.btnFlashCheck,SIGNAL(clicked()),this,SLOT(check_flash()));

        // заполнение данных RAM
        connect(ui.btnFillRam,SIGNAL(clicked()),this,SLOT(set_ram()));
        connect(ui.btnIncRamValue,SIGNAL(clicked()),this,SLOT(inc_ram_value()));
        connect(ui.btnDecRamValue,SIGNAL(clicked()),this,SLOT(dec_ram_value()));

        // обработка событий изменения значений элементов RAM
        connect(ui.btnRamOpen,SIGNAL(clicked()),this,SLOT(open_ram()));
        connect(ui.btnRamErase,SIGNAL(clicked()),this,SLOT(erase_ram()));
        connect(ui.btnRamLoad,SIGNAL(clicked()),this,SLOT(load_ram()));
        connect(ui.btnRamSave,SIGNAL(clicked()),this,SLOT(save_ram()));

        // отладочное рисование
        connect(ui.btnDraw,SIGNAL(clicked()),this,SLOT(show_beam_position()));
        connect(ui.btnShowView,SIGNAL(clicked()),analizer,SLOT(show_channels()));

        // работа с абонентами
        connect(ui.btnSend,SIGNAL(clicked()),this,SLOT(send_abonent_request()));
        connect(ui.abonentCmd,SIGNAL(currentIndexChanged(int)),this,SLOT(prepare_abonent_request()));
        connect(ui.abonentIndex,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));
        connect(ui.msgBlockNum,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));
        connect(ui.msgBlockSize,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));
        connect(ui.tblDataOut,SIGNAL(clicked(const QModelIndex&)),this,SLOT(prepare_abonent_request()));
        connect(ui.tblDataOut,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(prepare_abonent_request()));
        connect(ui.tblDataOut,SIGNAL(pressed(const QModelIndex&)),this,SLOT(prepare_abonent_request()));
        connect(ui.tblDataOut,SIGNAL(entered(const QModelIndex&)),this,SLOT(prepare_abonent_request()));
        connect(ui.tblDataOut,SIGNAL(activated(QModelIndex)),this,SLOT(prepare_abonent_request()));

        // создание формы для отрисовки решетки с каналами
        connect(ui.btnSysCtrl,SIGNAL(clicked()),this,SLOT(test_widget()));

        // отображение структуры антенной решетки
        connect(ui.btnGridArray,SIGNAL(clicked()),grid,SLOT(show_grid()));

        // отроисовка результатов проверки в анализаторе
        connect(test,SIGNAL(show_analizer_channels()),analizer,SLOT(show_channels()));
        connect(test,SIGNAL(show_analizer_calculators(bool)),analizer,SLOT(show_calculators(bool)));
        connect(test,SIGNAL(show_analizer_pulses()),analizer,SLOT(show_pulses()));
        connect(test,SIGNAL(show_fi0()),analizer,SLOT(show_fi0()));
        connect(test,SIGNAL(abonent_changed(int)),analizer,SLOT(set_abonent_number(int)));

        // отроисовка результатов проверки на полотне решетки
        connect(test,SIGNAL(show_grid_channels()),grid,SLOT(show_channels()));
        connect(test,SIGNAL(show_grid_calculators(bool)),grid,SLOT(show_calculators(bool)));
        connect(test,SIGNAL(show_grid_pulses()),grid,SLOT(show_pulses()));
        connect(test,SIGNAL(show_fi0()),grid,SLOT(show_fi0()));
        connect(test,SIGNAL(abonent_changed(int)),grid,SLOT(set_abonent_number(int)));

        // установка коэффициента масштаба, длительности сигнала сброса и паузы для всей решетки
        connect(ui.btnSetScale,SIGNAL(clicked()),this,SLOT(set_antenna_params()));

        // информация об активных абонентах
        connect(ui.spbAbonentIndex,SIGNAL(valueChanged(int)),this,SLOT(update_abonent_address(int)));

        // создание нового файла конфигурации
        connect(ui.btnNewConfig,SIGNAL(clicked()),this,SLOT(new_cfg_file_create()));
}

/////////////////////////////////////////////////////////////////////
//	    Конфигурирование программы мониторинга СУЛ
/////////////////////////////////////////////////////////////////////

void sul_monitor::config_system()
{
        sul = NULL;
        timer = NULL;
        dbg_timer = NULL;
        display_timer = NULL;
        ang = NULL;
        scan = NULL;
        dev = NULL;
        p485 = NULL;
        graph = NULL;
        analizer = NULL;
        worker = NULL;
        test = NULL;
        grid = NULL;
        tune = NULL;

        settings = new QSettings( SYSTEM_CONFIG_FILE, QSettings::IniFormat );

        /*
        settings->setValue("INTERFACE", "COM1");
        settings->setValue("SUL", "MDO");
        settings->setValue("CONFIG_RAM", ".\\config\\ram_mdo.cfg");
        settings->setValue("CONFIG_FLASH", ".\\config\\sul_mdo.cfg");
        */

        QVariant ifc = settings->value("INTERFACE", "COM1");
        QVariant sys = settings->value("SUL", "MDO");
        QVariant flash = settings->value("CONFIG_FLASH", ".\\config\\sul_mdo.cfg");
        QVariant ram = settings->value("CONFIG_RAM", ".\\config\\ram_mdo.cfg");
        QVariant Abon = settings->value("ABONENTS", "5");
        QVariant Chan = settings->value("ABONENTS_CHANNELS", "128");
        QVariant sChan = settings->value("SUL_CHANNELS", "637");

        n_abonents = Abon.toInt();
        n_channels = Chan.toInt();
        n_sul_channels = sChan.toInt();

        QString sul_name = sys.toString();

        ifc_t = ifc.toString();

        cfg_flash = flash.toString();
        cfg_ram = ram.toString();

        if(sul_name == "MDO"){
            sul_t = SUL_MDO;
        }
        if(sul_name == "BMK"){
            sul_t = SUL_BMK;
        }

        QString msg = tr("Интерфейс: ") + ifc_t + ",  " + tr("СУЛ: ") + sul_name
                + ",  " + cfg_flash + ",  " + cfg_ram;

        bar->showMessage(msg);
}

//-----------------------------------------------------------------------------

void sul_monitor::create_system()
{
        // таймер для отправки сообщений системе СУЛ
        timer = new QTimer();
        timer->setInterval(ui.period->value());

        // таймер для отправки отладочных сообщений системе СУЛ
        dbg_timer = new QTimer();
        dbg_timer->setInterval(ui.dbgPeriod->value());

        // таймер для отрисовки состояния длительных операций
        display_timer = new QTimer();
        display_timer->setInterval(500);
        display_timer_counter = 0;
        connect(display_timer,SIGNAL(timeout()),this,SLOT(display_timer_event()));

        // объект сканера
        scan = new scanner( ui.scanSectorMax->value(),
                            ui.scanAngle->value(),
                            ui.step_dr->value() );

        dev = new serial(ifc_t.toAscii(),FILE_FLAG_NO_BUFFERING);

        if(!dev->is_open()) {
                bar->showMessage(tr("Ошибка! Не могу открыть интерфейс связи с СУЛ"));
                delete dev;
                dev = NULL;
        }

        switch(sul_t) {
            case SUL_MDO:
                sul = new sul_mdo(dev,cfg_flash.toAscii().data(),cfg_ram.toAscii().data(), n_abonents, n_channels);
            break;
        case SUL_BMK:
            sul = new sul_bmk(dev,cfg_flash.toAscii().data(),cfg_ram.toAscii().data(), n_abonents, n_channels);
        break;
            case SUL_AVR:
                sul = NULL;
                bar->showMessage(tr("Ошибка! Неизвестная система СУЛ"));
            break;
        }

        p485 = new packet485(dev);

        int xr = geometry().x()+geometry().width();

        // виджет для отрисовки положения луча
        graph = new sul_graph(scan,NULL,Qt::WindowStaysOnTopHint);
        graph->setGeometry(xr+2*MDX, geometry().y()+MDY, 250, 250);

        // создаем форму для выполнения контроля каналов у абонентов и отрисовки их состояния
        test = new sul_test_widget(sul,NULL,Qt::WindowStaysOnTopHint);
        test->setGeometry(xr+2*MDX, graph->geometry().bottom()+MDY, 250,80);

        // создаем форму для отрисовки состояния каналов антенной решетки
        grid = new sul_array(sul,NULL,Qt::WindowStaysOnTopHint);
        grid->setGeometry(xr+2*MDX, geometry().y()+MDY, geometry().height(),geometry().height());

        // виджет для отображения состояния каналов и данных
        analizer = new sul_channel_analizer(sul, NULL, Qt::WindowStaysOnTopHint);
        analizer->setGeometry(geometry().x()+MDX, geometry().bottom()+2*MDY,1030,256);

        // рабочий поток для выполнения длительных задач
        worker = new worker_thread(sul);
        connect(worker,SIGNAL(task_status(int)),this,SLOT(processing_status(int)));

        ang = new angle_correct(5.08,4.464,1.0,1.0);

        tune = new sul_tune_widget(8);
        tune->setGeometry(xr+2*MDX,graph->geometry().bottom()+MDY,250,200);
}

//-----------------------------------------------------------------------------

void sul_monitor::processing_status(int status)
{
    display_timer->stop();

    if(status == 0) {
        bar->showMessage(tr("Выполнение: ОК. Время выполнения операции: ") + QString::number(display_timer_counter/2) + tr(" сек"));
    } else {
        bar->showMessage(tr("Выполнение: Ошибка. Время выполнения операции: ") + QString::number(display_timer_counter/2) + tr(" сек"));
    }
    display_timer_counter = 0;
}

//-----------------------------------------------------------------------------

void sul_monitor::display_timer_event()
{
    ++display_timer_counter;

    if((display_timer_counter % 1) == 0) {
        bar->showMessage(tr("Выполнение ... ")
                         +QString::number(display_timer_counter/2)
                         +tr(" сек"));
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::set_dbgtimer(int val)
{
    dbg_timer->setInterval(val);
}

//-----------------------------------------------------------------------------

void sul_monitor::delete_system()
{
        if(timer->isActive()) {
                timer->stop();
                delete timer;
                timer = NULL;
        }

        if(dbg_timer->isActive()) {
                dbg_timer->stop();
                delete dbg_timer;
                dbg_timer = NULL;
        }

        if(display_timer->isActive()) {
                display_timer->stop();
                delete display_timer;
                display_timer = NULL;
        }

        if(ang) delete ang;
        if(scan) delete scan;
        if(dev) delete dev;
        if(p485) delete p485;
        if(sul) delete sul;
        if(graph) delete graph;
        if(analizer) delete analizer;
        if(worker) delete worker;
        if(test) delete test;
        if(grid) delete grid;
        if(tune) delete tune;

        sul = NULL;
        ang = NULL;
        scan = NULL;
        dev = NULL;
        p485 = NULL;
        graph = NULL;
        analizer = NULL;
        worker = NULL;
        test = NULL;
        grid = NULL;
        tune = NULL;
}

void sul_monitor::restart_system()
{
    if(sul) delete sul;

    switch(sul_t) {
        case SUL_MDO:
            sul = new sul_mdo(dev,cfg_flash.toAscii().data(),cfg_ram.toAscii().data());
        break;
    case SUL_BMK:
        sul = new sul_bmk(dev,cfg_flash.toAscii().data(),cfg_ram.toAscii().data(), 16, 4);
    break;
        case SUL_AVR:
            sul = NULL;
            bar->showMessage(tr("Ошибка! Неизвестная система СУЛ"));
        break;
    }

    set_antenna_params();
    update_screen();
}

/////////////////////////////////////////////////////////////////////
//		    Запуск и останов сканирования
/////////////////////////////////////////////////////////////////////

void sul_monitor::start_scanner()
{
        if(timer->isActive()) {

                stop_scanner();

        } else {

                set_scanner();

                timer->setInterval(ui.period->value());
                timer->start();

                ui.btnStart->setText(tr("Стоп"));
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::stop_scanner()
{
        if(timer->isActive()) {

                timer->stop();
                scan->stop();

                ui.btnStart->setText(tr("Старт"));
        }

        ui.currentX->setText(QString::number(scan->get_x()));
        ui.currentY->setText(QString::number(scan->get_y()));
        ui.currentXcode->setText(QString::number(ang->to_hcode(scan->get_x(), scan->get_y()),16));
        ui.currentYcode->setText(QString::number(ang->to_vcode(scan->get_x(), scan->get_y()),16));

        graph->repaint();
}

//-----------------------------------------------------------------------------

void sul_monitor::step_scanner()
{
    if(scan->step()) {

        if( sul->sul_beam_position( ang->to_hcode(scan->get_x(), scan->get_y()),
                                    ang->to_vcode(scan->get_x(), scan->get_y()),
                                    ui.spbZone->value(),RAY_NARROW) < 0 );

    }

    ui.currentX->setText(QString::number(scan->get_x()));
    ui.currentY->setText(QString::number(scan->get_y()));
    ui.currentXcode->setText(QString::number(ang->to_hcode(scan->get_x(), scan->get_y()),16));
    ui.currentYcode->setText(QString::number(ang->to_vcode(scan->get_x(), scan->get_y()),16));

    graph->repaint();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_scanner()
{
        timer->stop();

        scan->stop();

        scan->set_angle(ui.scanAngle->value());
        scan->set_rm(ui.scanSectorMax->value());
        scan->set_dr(ui.step_dr->value());

        scan->start();

        ui.progressBar->reset();
        ui.progressBar->setRange(0, scan->get_n());
        ui.progressBar->setValue(scan->get_index());

        ui.currentX->setText(QString::number(scan->get_x()));
        ui.currentY->setText(QString::number(scan->get_y()));
        ui.currentXcode->setText(QString::number(ang->to_hcode(scan->get_x(), scan->get_y()),16));
        ui.currentYcode->setText(QString::number(ang->to_vcode(scan->get_x(), scan->get_y()),16));

        graph->repaint();
}

//-----------------------------------------------------------------------------

void sul_monitor::setup_beam()
{
    scan->set_x(ui.value_x0->value());
    scan->set_y(ui.value_y0->value());

    if( sul->sul_beam_position( ang->to_hcode(scan->get_x(), scan->get_y()),
                                ang->to_vcode(scan->get_x(), scan->get_y()), ui.spbZone->value(),RAY_NARROW) < 0)
    {
        bar->showMessage(tr("Ошибка установки луча."));
    } else {
        bar->showMessage(tr("Луч установлен."));
    }

    ui.currentX->setText(QString::number(scan->get_x()));
    ui.currentY->setText(QString::number(scan->get_y()));
    ui.currentXcode->setText(QString::number(ang->to_hcode(scan->get_x(), scan->get_y()),16));
    ui.currentYcode->setText(QString::number(ang->to_vcode(scan->get_x(), scan->get_y()),16));

    graph->repaint();
}

//-----------------------------------------------------------------------------

void sul_monitor::update_beam_position(int X, int Y)
{
    ui.value_x0->setValue(X);
    ui.value_y0->setValue(Y);

    setup_beam();
}


/////////////////////////////////////////////////////////////////////
//              Изменение параметров сканирования
/////////////////////////////////////////////////////////////////////

void sul_monitor::dr_change()
{
        scan->set_dr(ui.step_dr->value());
}
void sul_monitor::angle_change()
{
        scan->set_angle(ui.scanAngle->value());
}
void sul_monitor::sector_max_change()
{
        scan->set_rm(ui.scanSectorMax->value());
}

//-----------------------------------------------------------------------------

void sul_monitor::axis_change()
{
        if( ui.rbtAxisX->isChecked() ) {
                ui.scanAngle->setValue(0);
        }
        if( ui.rbtAxisY->isChecked() ) {
                ui.scanAngle->setValue(90);
        }
        if( ui.rbtAxisXY->isChecked() ) {
                ui.scanAngle->setValue(45);
        }
        scan->set_angle(ui.scanAngle->value());
}

/////////////////////////////////////////////////////////////////////
//          Прерывание таймера при сканировании
/////////////////////////////////////////////////////////////////////

void sul_monitor::timer_event()
{
        if(!scan->step()) {
                stop_scanner();
                return;
        }

        if( sul->sul_beam_position( ang->to_hcode(scan->get_x(), scan->get_y()),
                                    ang->to_vcode(scan->get_x(), scan->get_y()),
                                    ui.spbZone->value(),RAY_NARROW) < 0)
        {
            bar->showMessage(tr("Ошибка установки луча."));
        } else {
            bar->showMessage(tr("Луч установлен."));
        }

        ui.progressBar->setValue(scan->get_index());

        ui.currentX->setText(QString::number(scan->get_x()));
        ui.currentY->setText(QString::number(scan->get_y()));
        ui.currentXcode->setText(QString::number(ang->to_hcode(scan->get_x(), scan->get_y()),16));
        ui.currentYcode->setText(QString::number(ang->to_vcode(scan->get_x(), scan->get_y()),16));

        if(graph) graph->repaint();
}

/////////////////////////////////////////////////////////////////////
//			Изменение параметров интерфейса связи с СУЛ
/////////////////////////////////////////////////////////////////////

void sul_monitor::iface_change()
{
        device *new_device = NULL;

        if( ui.rbtCOM1->isChecked() ) {
                new_device = new serial("COM1");
        }
        if( ui.rbtCOM2->isChecked() ) {
                new_device = new serial("COM2");
        }
        if( ui.rbtRS4851->isChecked() ) {
                new_device = new serial("COM3");
        }
        if( ui.rbtRS4852->isChecked() ) {
                new_device = new serial("COM4");
        }

        if(!new_device->is_open()) {
            bar->showMessage(tr("Ошибка! Не могу открыть устройство"));
            return;
        }

        if(sul) sul->sul_connect_device(new_device);
        if(p485) p485->reconnect_device(new_device);

        delete dev;
}

/////////////////////////////////////////////////////////////////////
//              Рисование положения луча и состояния каналов
/////////////////////////////////////////////////////////////////////

void sul_monitor::show_beam_position()
{
    if(graph) graph->show();
}

///////////////////////////////////////////////////////////////////////
//			Заполнение таблиц данными из RAM/FLASH
///////////////////////////////////////////////////////////////////////

void sul_monitor::tool_change(int index)
{
        switch(index) {
                case 1: fill_flash(); break;
                case 2: fill_ram(); break;
                case 3: fill_abonent_form(); break;
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::zone_change()
{
    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_ram()
{
    int abonent = ui.spbRamAbonentNumber->value();

    unsigned char *data = new unsigned char[sul->ram_block_size()];
    if(!data){
            bar->showMessage(tr("Ошибка! Не могу выделить память для абонента ") + QString::number(abonent));
            return;
    }

    int block = abonent - 1;

    for(int i=0; i<sul->ram_block_size(); i++) {
            if( sul->sul_ram_get_element(0,block,i,data[i]) < 0) {
                    bar->showMessage(tr("Ошибка! Не могу получить данные абонента ") + QString::number(abonent));
                    delete [] data;
                    return;
            }
    }

    ui.gbRamData->setTitle(  tr(" Абонент ") + QString::number(abonent) +
                             tr(". CRC данных: 0x") +
                             QString::number(sul->sul_ram_space_crc(abonent),16) +
                             tr(" CRC абонента: 0x") +
                             QString::number(sul->sul_ram_crc(abonent),16) );

    fill_table(ui.rtable->model(), data, sul->ram_block_size());


    delete [] data;
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_flash()
{
        int abonent = ui.spbFlashAbonentNumber->value();

        unsigned char *data = new unsigned char[sul->flash_block_size()];
        if(!data){
                bar->showMessage(tr("Ошибка! Не могу выделить память для абонента ") + QString::number(abonent));
                return;
        }

        int zone = ui.spbSegmentNumber->value();
        int block = abonent - 1;

        for(int i=0; i<sul->flash_block_size(); i++) {
                if( sul->sul_flash_get_element(zone,block,i,data[i]) < 0) {
                        bar->showMessage(tr("Ошибка! Не могу получить данные абонента ") + QString::number(abonent));
                        delete [] data;
                        return;
                }
        }

        fill_table(ui.ftable->model(), data, sul->flash_block_size());

        int abonent_space_crc = sul->sul_flash_space_crc(abonent);
        int abonent_device_crc = sul->sul_flash_crc(abonent);

        ui.gbFlashData->setTitle(  tr(" Абонент ") + QString::number(abonent) +
                                   tr(". CRC данных: 0x") +
                                   QString::number(abonent_space_crc,16) +
                                   tr(" CRC абонента: 0x") +
                                   QString::number(abonent_device_crc,16) );

        int total_space_crc = sul->sul_flash_space_crc();
        int total_device_crc = sul->sul_flash_crc();

        ui.lblFileCRC->setText(QString::number(total_space_crc,16));
        ui.lblHwCRC->setText(QString::number(total_device_crc,16));


        delete [] data;
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_table(QAbstractItemModel *model, unsigned char *data, int n)
{
        if(!data) return;

        if(n != model->rowCount()*model->columnCount()) {
            bar->showMessage(tr("Неправильный размер данных для отображения."));
            return;
        }

        for (int nRow = 0; nRow < model->rowCount(); ++nRow) {

                for (int nCol = 0; nCol < model->columnCount(); ++nCol) {

                        QModelIndex index = model->index(nRow, nCol);

                        QString strPos = QString("%1").arg(data[nRow*model->columnCount()+nCol]);

                        model->setData( index, strPos );
                }
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::open_flash()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(0, tr("Открыть файл"),".",tr("config files (*.cfg)"));

    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл конфигурации: ") + fileName);
    }

    if( sul->sul_flash_reconfig( fileName.toAscii().data() ) < 0 ) {
        bar->showMessage(tr("Ошибка реконфигурации СУЛ"));
        return;
    }

    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::erase_flash()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_erase_eeprom);
    display_timer->start();

    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::load_flash()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_load_eeprom);
    display_timer->start();

    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::check_flash()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_ram()
{
    int abonent = ui.spbRamAbonentNumber->value();
    int block = abonent - 1;

    space_fill_type type = ui.rbtFillRamPattern->isChecked() ? FILL_PATTERN : FILL_RANDOM;

    sul->sul_ram_fill(0, block, type, ui.lePatternValue->value());

    fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::inc_ram_value()
{
    QTableView *t = ui.rtable;
    QModelIndex index = t->currentIndex();

    if(!index.isValid())
        return;

    QAbstractItemModel *m = t->model();

    int val = index.data().toInt() & 0x1f;
    val += ui.spbRamStepValue->value();

    if(val > 31) {
        val = 0;
    }

    m->setData(index,val);

    int offset = index.row()*m->columnCount() + index.column();
    int abonent = ui.spbRamAbonentNumber->value();
    int block = abonent - 1;
    sul->sul_ram_set_element(0,block,offset,reinterpret_cast<u8&>(val));

    ui.gbRamData->setTitle( tr(" Абонент ") + QString::number(abonent) +
                            tr(". CRC данных: 0x") +
                            QString::number(sul->sul_ram_space_crc(abonent),16) +
                            tr(" CRC абонента: 0x") +
                            QString::number(sul->sul_ram_crc(abonent),16) );

}

//-----------------------------------------------------------------------------

void sul_monitor::dec_ram_value()
{
    QTableView *t = ui.rtable;
    QModelIndex index = t->currentIndex();

    if(!index.isValid())
        return;

    QAbstractItemModel *m = t->model();

    int val = index.data().toInt();
    val -= ui.spbRamStepValue->value();

    if(val < 0) {
        val = 31;
    }

    m->setData(index, val);

    m->setData(index,val);

    int offset = index.row()*m->columnCount() + index.column();
    int abonent = ui.spbRamAbonentNumber->value();
    int block = abonent - 1;
    sul->sul_ram_set_element(0,block,offset,reinterpret_cast<u8&>(val));

    ui.gbRamData->setTitle( tr(" Абонент ") + QString::number(abonent) +
                            tr(". CRC данных: 0x") +
                            QString::number(sul->sul_ram_space_crc(abonent),16) +
                            tr(" CRC абонента: 0x") +
                            QString::number(sul->sul_ram_crc(abonent),16) );
}

//-----------------------------------------------------------------------------

void sul_monitor::open_ram()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = QFileDialog::getOpenFileName(0, tr("Открыть файл"),".",tr("config files (*.cfg)"));

    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл конфигурации: ") + fileName);
    }

    if( sul->sul_ram_reconfig( fileName.toAscii().data() ) < 0 ) {
        bar->showMessage(tr("Ошибка реконфигурации СУЛ"));
        return;
    }

    fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::erase_ram()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_erase_ram);
    display_timer->start();

    fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::load_ram()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_load_ram);
    display_timer->start();

    fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::save_ram()
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл"),".",tr("config files (*.cfg)"));

    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл для сохранения конфигурации: ") + fileName);
    }

    if( sul->sul_ram_save(fileName.toAscii().data()) < 0) {
        bar->showMessage(tr("Ошибка сохранения данных RAM"));
        return;
    }
}

///////////////////////////////////////////////////////////////////////
//			Работа с абонентами
///////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------

void sul_monitor::prepare_abonent_request()
{
        int abonent = ui.abonentIndex->value();
        int cmd = ui.abonentCmd->currentIndex()+1;
        int bn = ui.msgBlockNum->value();
        unsigned char data[256];
        int size = p485->cmd_to_size(cmd);
        ui.msgBlockSize->setValue(size);

        memset(data,0,sizeof(data));

        // Заполнение таблицы передаваемых данных
        QAbstractItemModel *m2 = ui.tblDataOut->model();
        for (int nCol = 0; nCol < m2->columnCount(); ++nCol) {
                for (int nRow = 0; nRow < size; ++nRow) {
                        QModelIndex index = m2->index(nRow, nCol);
                        data[nRow] = m2->data( index ).toInt();
                }
        }

        p485->create_packet485(abonent,cmd,bn,data,size);
        const packet p = p485->get_packet();

        // Заполнение таблицы заголовка
        QAbstractItemModel *m1 = ui.tblHdrOut->model();
        for (int nCol = 0; nCol < m1->columnCount(); ++nCol) {
                for (unsigned nRow = 0; nRow < sizeof(struct host_dbg_header); ++nRow) {
                        QModelIndex index1 = m1->index(nRow, nCol);
                        m1->setData( index1, p.paddr[nRow] );
                }
        }

        // Обнуление таблицы принимаемых данных
        QAbstractItemModel *m3 = ui.tblDataIn->model();
        for (int nCol = 0; nCol < m3->columnCount(); ++nCol) {
                for (int nRow = 0; nRow < m3->rowCount(); ++nRow) {
                        QModelIndex index = m3->index(nRow, nCol);
                        model3->setData( index, 0 );
                }
        }

        if(analizer) {
            analizer->repaint();
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::dbg_timer_event()
{
        int abonent = ui.abonentIndex->value();
        int cmd = ui.abonentCmd->currentIndex()+1;
        int bn = ui.msgBlockNum->value();
        unsigned char data[256];
        int size = p485->cmd_to_size(cmd);
        ui.msgBlockSize->setValue(size);

        memset(data,0,sizeof(data));

        // заполнение данными
        if(p485->cmd_to_type(cmd) == to_target) {
                QAbstractItemModel *model2 = ui.tblDataOut->model();
                for (int nCol = 0; nCol < model2->columnCount(); ++nCol) {
                        for (int nRow = 0; nRow < size; ++nRow) {
                                QModelIndex index = model2->index(nRow, nCol);
                                data[nRow] = model2->data( index ).toInt();
                        }
                }
        }

        if( p485->request(abonent,cmd,bn,data,size) < 0 ) {

                bar->showMessage(tr("Ошибка выполнения запроса"));
                return;
        }

        // Заполнение таблицы принимаемых данных
        if(p485->cmd_to_type(cmd) == to_host) {
                QAbstractItemModel *model3 = ui.tblDataIn->model();
                for (int nCol = 0; nCol < model3->columnCount(); ++nCol) {
                    for (int nRow = 0; nRow < size; ++nRow) {
                                QModelIndex index = model3->index(nRow, nCol);
                                model3->setData( index, data[nRow] );
                    }
                }
        }

        bar->showMessage(tr("Запрос выполнен."));

        if(analizer) {
            analizer->repaint();
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::send_abonent_request()
{
        if( ui.dbgPeriod->value() > 0 ) {

                if(dbg_timer->isActive()) {
                        dbg_timer->stop();
                        ui.btnSend->setChecked(false);
                        ui.btnSend->setText(tr("Старт"));
                } else {
                        dbg_timer->setInterval(ui.dbgPeriod->value());
                        ui.btnSend->setChecked(true);
                        ui.btnSend->setText(tr("Стоп"));
                        dbg_timer->start();
                }
        } else {
                ui.btnSend->setChecked(false);
                dbg_timer_event();
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_abonent_form()
{
        for (int nCol = 0; nCol < 1; ++nCol) {

                for (int nRow = 0; nRow < 10; ++nRow) {

                        QModelIndex index1 = model1->index(nRow, nCol);
                        model1->setData( index1, 0 );
                }
        }

        for (int nCol = 0; nCol < 1; ++nCol) {

                for (int nRow = 0; nRow < 128; ++nRow) {

                        QModelIndex index2 = model2->index(nRow, nCol);
                        QModelIndex index3 = model3->index(nRow, nCol);

                        model2->setData( index2, nRow );
                        model3->setData( index3, 0 );
                }
        }

        prepare_abonent_request();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_table_view(QTableView *t, int rowh, int colw)
{
        QAbstractItemModel *m = t->model();

        for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
                t->setColumnWidth(nCol,colw);
        }
        for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
                t->setRowHeight(nRow,rowh);
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::test_widget()
{
    if(test) test->show();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_antenna_params()
{
    if( sul->sul_set_scale(0, ui.spbScaleValue->value(),
                           ui.spbResetDuration->value(),
                           ui.spbPauseDuration->value()) < 0 ) {
        bar->showMessage(tr("Ошибка установки параметров СУЛ!"));
        return;
    }

    if( sul->sul_init() ) {
        bar->showMessage(tr("Ошибка инициализации СУЛ!"));
        return;
    }

    if( sul->sul_beam_position(0,0,0,RAY_NARROW) ) {
        bar->showMessage(tr("Ошибка установки луча!"));
        return;
    }

    sul->sul_set_top_level(ui.spbTopLevel->value());
    sul->sul_set_low_level(ui.spbLowLevel->value());

    bar->showMessage(tr("Параметры установлены."));
}

//-----------------------------------------------------------------------------

void sul_monitor::update_abonent_address(int val)
{
    ui.lbAbonentAddr->setText(QString::number(sul->sul_abonent_address(val)));
}

//-----------------------------------------------------------------------------

void sul_monitor::update_screen()
{
    if(!sul) return;

    ui.lbActiveAbonents->setText(QString::number(sul->sul_active_abonents()));
    ui.spbSegmentNumber->setMaximum(sul->flash_zone_count()-1);
    ui.spbSegmentNumber->setMinimum(0);
    ui.spbSegmentNumber->setValue(0);

    if(grid) grid->repaint();

    if(sul->sul_active_abonents()) {

        ui.spbAbonentIndex->setMaximum(sul->sul_active_abonents());
        ui.spbAbonentIndex->setMinimum(1);
        ui.spbAbonentIndex->setValue(1);

        ui.abonentIndex->setMaximum(sul->sul_active_abonents());
        ui.abonentIndex->setMinimum(1);
        ui.abonentIndex->setValue(1);

    } else {

        ui.spbAbonentIndex->setMaximum(sul->sul_active_abonents());
        ui.spbAbonentIndex->setMinimum(0);
        ui.spbAbonentIndex->setValue(0);

        ui.abonentIndex->setMaximum(sul->sul_active_abonents());
        ui.abonentIndex->setMinimum(0);
        ui.abonentIndex->setValue(0);
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::new_cfg_file_create()
{
    tune->show();
}
