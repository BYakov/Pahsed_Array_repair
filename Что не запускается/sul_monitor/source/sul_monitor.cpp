#include "sul_monitor.h"

//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------

#define     DW  60
#define     DH  40
#define     MDX 10
#define     MDY 40

//-----------------------------------------------------------------------------

sul_monitor::sul_monitor(const char *cfgFile, QWidget *parent, Qt::WindowFlags flags, bool mode)
: QWidget(parent, flags), advanced_mode(mode)
{
        //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

        ui.setupUi(this);
        setMouseTracking(true);
        setWindowFlags(Qt::Window);

        hlibDev = NULL;
        hlibSul = NULL;

        // вывод отладочных сообщений на панель
        bar = new QStatusBar();
        ui.barLayout->addWidget(bar);

        if(cfgFile)
            configFile = cfgFile;
        else
            configFile = SYSTEM_CONFIG_FILE;

        config_system();
        create_system();
        create_dispaly();
        connect_slots();
        setWindowIcon(QIcon("config//icon//monitor_icon.png"));
        update_screen();

        userChannelData.clear();
        vendorParamUpdate(1);
        last_started_task = task_unknown;

        cout << "sul_monitor::sul_monitor()" << endl;
}

//-----------------------------------------------------------------------------

sul_monitor::~sul_monitor()
{
    std::cout << "sul_monitor::~sul_monitor()" << endl;

    delete_system();
    delete_dispaly();

    userChannelData.clear();
}

//-----------------------------------------------------------------------------

void sul_monitor::create_dispaly()
{
        model1 = new QStandardItemModel(sizeof(struct host_mdr_dbg), 1);
        model2 = new QStandardItemModel(128, 1);
        model3 = new QStandardItemModel(128, 1);

        switch(sul->sul_flash_block_size()) {
        case 128: fmodel = new QStandardItemModel(8, 16); break;
        case 64:  fmodel = new QStandardItemModel(4, 16); break;
        case 4:  fmodel = new QStandardItemModel(1, 4); break;
        default: fmodel = new QStandardItemModel(8, 16); break;
        }
        switch(sul->sul_ram_block_size()) {
        case 128: rmodel = new QStandardItemModel(8, 16); break;
        case 64:  rmodel = new QStandardItemModel(4, 16); break;
        case 4:  rmodel = new QStandardItemModel(1, 4); break;
        default: rmodel = new QStandardItemModel(8, 16); break;
        }

        ftable = new SulTableView();
        rtable = new SulTableView();
        tableHdr = new SulTableView();
        tableOut = new SulTableView();
        tableIn = new SulTableView();

        ftable->setModel(fmodel);
        rtable->setModel(rmodel);
        tableHdr->setModel(model1);
        tableOut->setModel(model2);
        tableIn->setModel(model3);

        set_table_view(ftable);
        set_table_view(rtable);
        set_table_view(tableHdr,26,80);
        set_table_view(tableOut,26,80);
        set_table_view(tableIn,26,80);

        ui.toolBox->setCurrentIndex(0);
        ui.spbAbonentIndex->setValue(0);

        ui.spbFlashAbonentNumber->setMaximum(sul->sul_total_abonents()-1);
        ui.spbRamAbonentNumber->setMaximum(sul->sul_total_abonents()-1);

        ui.sul_flash_layout->addWidget(ftable);
        ui.sul_ram_layout->addWidget(rtable);
        ui.headerLayout->addWidget(tableHdr);
        ui.dataOutLayout->addWidget(tableOut);
        ui.dataInLayout->addWidget(tableIn);

        // заполним поля кодами команд
        for(unsigned i=0; i<exchange->total_commands(); i++) {
            ui.abonentCmd->addItem(QString(exchange->command_name(i)));
        }

        // заполним поля именами сегментов
        for(int i=0; i<sul->sul_flash_segment_count(); i++) {
            ui.cbFlashSegmentName->addItem(QString(sul->sul_flash_segment_name(i)));
        }

        for(unsigned i=0; i<litera.size(); i++) {
            QString s = "L" + QString::number(i);
            ui.cbZone->addItem(s);
        }
/*
        if(litera.size() > 3)
            ui.cbZone->setCurrentIndex(3);
        else
            ui.cbZone->setCurrentIndex(0);
*/
        litera_changed();

        // in advanced mode enable this capabilities
        ui.btnNewModuleSettings->setEnabled(advanced_mode);
        ui.btnSend->setEnabled(advanced_mode);
        ui.btnFlashErase->setEnabled(advanced_mode);
        ui.btnFlashLoad->setEnabled(advanced_mode);
        ui.btnRamErase->setEnabled(advanced_mode);
        ui.btnRamLoadAll->setEnabled(advanced_mode);


        //if(radar) {
        //    ArrayElementSizeChanged(10);
        //}
        cout << "sul_monitor::create_dispaly()" << endl;
 }

//-----------------------------------------------------------------------------

void sul_monitor::delete_dispaly()
{
        if(bar) delete bar;
        if(model1) delete model1;
        if(model2) delete model2;
        if(model3) delete model3;
        if(ftable) delete ftable;
        if(rtable) delete rtable;
        if(tableHdr) delete tableHdr;
        if(tableOut) delete tableOut;
        if(tableIn) delete tableIn;
        if(radar) {
            radar->close();
            delete radar;
        }

        std::cout << "sul_monitor::delete_dispaly()" << endl;
}

//-----------------------------------------------------------------------------

void sul_monitor::config_system()
{
        cout << "sul_monitor::config_system(" << configFile.toStdString().c_str() << ")" << endl;

        sul = NULL;
        timer = NULL;
        beamTimer = NULL;
        dbg_timer = NULL;
        display_timer = NULL;
        scan = NULL;
        dev = NULL;
        exchange = NULL;
        graph = NULL;
        analizer = NULL;
        worker = NULL;
        radar = NULL;

        settings = new QSettings( configFile, QSettings::IniFormat );

        QVariant libSul = settings->value("LIBSUL", "UNKNOWN");

        QVariant libDev = settings->value("LIBDEV", "UNKNOWN");
        QVariant ifc = settings->value("INTERFACE", "UNKNOWN");
        QVariant speed = settings->value("INTERFACE_SPEED", "115200");

        QVariant excel = settings->value("CONFIG_EXCEL", 0);
        QVariant flash = settings->value("CONFIG_FLASH", 0);
        QVariant ram = settings->value("CONFIG_RAM", 0);
        QVariant vid = settings->value("CONFIG_VID", 0);
        QVariant Abon = settings->value("ABONENTS", "0");
        QVariant Chan = settings->value("ABONENTS_CHANNELS", "128");
        QVariant dx_step1 = settings->value("STEP_DX1", "0");
        QVariant dy_step1 = settings->value("STEP_DY1", "0");
        QVariant dx_step2 = settings->value("STEP_DX2", "0");
        QVariant dy_step2 = settings->value("STEP_DY2", "0");

        libNameDev = libDev.toString();
        libNameSul = libSul.toString();

        // считаем значения из файла конфигурацци
        litera.clear();
        for(int i=1; i<=8; i++) {
            QString str("L");
            QString param = str + QString::number(i);
            QVariant val = settings->value(param, "12345.0");
            if(val.toDouble() != 12345.0) {
                litera.push_back(val.toDouble());
                cout << "L: " << val.toDouble() << endl;
            }
        }

        n_abonents = Abon.toInt();
        n_channels = Chan.toInt();

        grid_dX1 = dx_step1.toDouble();
        grid_dY1 = dy_step1.toDouble();
        grid_dX2 = dx_step2.toDouble();
        grid_dY2 = dy_step2.toDouble();

        ifcName = ifc.toString();
        ifcSpeed = speed.toInt();

        cfg_excel = excel.toString();
        cfg_flash = flash.toString();
        cfg_ram = ram.toString();
        cfg_vid = vid.toString();
/*
        QSettings *vid_settings = new QSettings( cfg_vid, QSettings::IniFormat );

        for(int i=1; i<=n_abonents; i++) {

            QString str("INDEX");
            QString param = str + QString::number(i);
            QVariant val = vid_settings->value(param, "0");

            if(val.toUInt()) {

                struct vendor_data v = {0};

                v.address = i;
                v.vendor_id = val.toInt();

                vdata.push_back(v);

                cout << "S/N: " << vdata.at(i-1).vendor_id
                     << ", address: " << int(vdata.at(i-1).address) << endl;

                ui.cbVendorTable->addItem(QString::fromUtf8("№ ") + QString::number( vdata.at(i-1).vendor_id ));
            }
        }

        delete vid_settings;
*/
        QString msg = QString::fromUtf8("Интерфейс: ") + ifcName
                      +  ",  " + QString::number(ifcSpeed) +
                      +  ",  " + libNameDev
                      +  ",  " + QString::fromUtf8("СУЛ: ") + libNameSul
                      +  ",  " + cfg_flash + ",  " + cfg_ram;

        bar->showMessage(msg);
}

//-----------------------------------------------------------------------------

void sul_monitor::create_system()
{
        // таймер для отправки сообщений системе СУЛ
        timer = new QTimer();
        timer->setInterval(ui.period->value());

        // таймер для периодической установки луча СУЛ
        beamTimer = new QTimer();
        beamTimer->setInterval(ui.leBeamSetupTimerPeriod->text().toInt());

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

        load_dev_library();

        load_sul_library();

        exchange = sul->sul_exchange_protocol();
        if(!exchange) {
            cout << "Error: Can`t get sul prorocol" << endl;
        }

        int xr = geometry().x()+geometry().width();

        // виджет для отрисовки положения луча
        graph = new sul_graph(scan);
        graph->setGeometry(xr+2*MDX, geometry().y()+MDY, 250, 250);

        // создаем форму для выполнения контроля каналов у абонентов и отрисовки их состояния
        //test = new sul_test_widget(sul,NULL,Qt::WindowStaysOnTopHint);
        //test->setGeometry(xr+2*MDX, graph->geometry().bottom()+MDY, 250,80);

        // создаем форму для отрисовки состояния каналов антенной решетки
        radar = new antenna(sul);
        //radar->setup_sul(sul);
        connect(this,SIGNAL(RepaintAntennaWidget()),radar,SLOT(update_screen()));

        // виджет для отображения состояния каналов и данных
        analizer = new sul_channel_analizer(sul);
        analizer->setGeometry(geometry().x()+MDX, geometry().bottom()+2*MDY,1030,256);

        // рабочий поток для выполнения длительных задач
        worker = new worker_thread(sul);

        // создаем форму для просмотра параметров каналов и отрисовки их состояния
        //param = new sul_param_widget(sul,NULL,Qt::WindowStaysOnTopHint);
        //param->setGeometry(xr+2*MDX, geometry().y()+MDY, 250, 80);

        // создаем форму для отрисовки состояния каналов антенной решетки
        //ant_view = new antenna();
        //ant_view->setup_sul(sul);
        //ant_view->show();

        cout << "sul_monitor::create_system()" << endl;
}

//-----------------------------------------------------------------------------

void sul_monitor::load_sul_library()
{
    cout << "Load SUL library: " << libNameSul.toStdString().c_str() << endl;

#ifdef __linux__
    hlibSul = dlopen(libNameSul.toStdString().c_str(), RTLD_LAZY);
#else
    hlibSul = LoadLibraryA(libNameSul.toStdString().c_str());
#endif
    if(!hlibSul) {
        QString s = QString::fromUtf8("Ошибка! Не могу загрузить библиотеку СУЛ: ") + libNameSul;
        QMessageBox::information(this, QString::fromUtf8("Монитор СУЛ"), s);
        exit(111);
    }

#ifdef __linux__
    factorySul = (sul_factory)dlsym(hlibSul,"create_sul");
#else
    factorySul = (sul_factory)GetProcAddress(hlibSul,"create_sul");
#endif
    if(!factorySul) {
        QString s = QString::fromUtf8("Ошибка! Не могу получить адрес функции create_sul() из библиотеки: ") + libNameSul;
        QMessageBox::information(this, QString::fromUtf8("Монитор СУЛ"), s);
#ifdef __linux__
        dlclose(hlibSul);
#else
        FreeLibrary(hlibSul);
#endif
        exit(222);
    }

    cout << "Get factory address: create_sul() - Ok" << endl;

    sul = factorySul(dev,
                     cfg_excel.toStdString().c_str(),
                     cfg_flash.toStdString().c_str(),
                     cfg_ram.toStdString().c_str(),
                     cfg_vid.toStdString().c_str(),
                     grid_dX2,
                     grid_dY2 );
    if(!sul) {
        throw;
    } else {
        cout << "Create SUL object - Ok" << endl;
    }

    sul->sul_set_litera(litera);
}

//-----------------------------------------------------------------------------

void sul_monitor::load_dev_library()
{
    cout << "Load device library: " << libNameDev.toStdString().c_str() << endl;

#ifdef __linux__
    hlibDev = dlopen(libNameDev.toStdString().c_str(), RTLD_LAZY);
#else
    hlibDev = LoadLibraryA(libNameDev.toStdString().c_str());
#endif
    if(!hlibDev) {
        QString s = QString::fromUtf8("Ошибка! Не могу загрузить библиотеку связи с СУЛ: ") + libNameDev;
        QMessageBox::information(this, QString::fromUtf8("Монитор СУЛ"), s);
        exit(333);
    }

#ifdef __linux__
    factoryDev = (dev_factory)dlsym(hlibDev,"create_io_device");
#else
    factoryDev = (dev_factory)GetProcAddress(hlibDev,"create_io_device");
#endif
    if(!factoryDev) {
        QString s = QString::fromUtf8("Ошибка! Не могу получить адрес функции create_io_device() из библиотеки: ") + libNameDev;
        QMessageBox::information(this, QString::fromUtf8("Монитор СУЛ"), s);
#ifdef __linux__
        dlclose(hlibDev);
#else
        FreeLibrary(hlibDev);
#endif
        exit(444);
    }

    cout << "Get factory address: create_io_device() - Ok" << endl;

#ifdef __linux__
    dev = factoryDev(ifcName.toStdString().c_str(), O_RDWR|O_NOCTTY|O_NDELAY, ifcSpeed);
#else
    dev = factoryDev(ifcName.toStdString().c_str(), FILE_FLAG_NO_BUFFERING, ifcSpeed);
#endif

    if(!dev) {
        throw;
    } else {
        cout << "Create DEV object - Ok" << endl;
    }
}


//-----------------------------------------------------------------------------

void sul_monitor::delete_system()
{
        timer->stop();
        delete timer;
        timer = NULL;

        beamTimer->stop();
        delete beamTimer;
        beamTimer = NULL;

        dbg_timer->stop();
        delete dbg_timer;
        dbg_timer = NULL;

        display_timer->stop();
        delete display_timer;
        display_timer = NULL;

        if(scan) delete scan;
        if(graph) delete graph;
        if(analizer) delete analizer;
        if(worker) delete worker;
        if(radar) delete radar;
        if(sul) delete sul;
        if(dev) delete dev;

        sul = NULL;
        factorySul = NULL;
        factoryDev = NULL;
        scan = NULL;
        dev = NULL;
        exchange = NULL;
        graph = NULL;
        analizer = NULL;
        worker = NULL;
        radar = NULL;

        litera.clear();
        //vdata.clear();

#ifdef __linux__
        if(hlibSul)
            dlclose(hlibSul);
        if(hlibDev)
            dlclose(hlibDev);
#else
        FreeLibrary(hlibSul);
        FreeLibrary(hlibDev);
#endif

        std::cout << "sul_monitor::delete_system()" << endl;
}

//-----------------------------------------------------------------------------

void sul_monitor::processing_status(int status, int task_code)
{
    //cout << "sul_monitor::processing_status()" << endl;

    display_timer->stop();

    if(task_code == task_rescan_modules) {

        bar->showMessage(QString::fromUtf8("Выполнение: ОК. Время сканирования: ") +
                         QString::number(display_timer_counter/2) + QString::fromUtf8(" сек.") +
                         QString::fromUtf8("Обнаружено: ") + QString::number(status) + QString::fromUtf8(" модулей.")   );

        if(status) {

            if(sul->sul_active_abonents()) {

                ui.spbAbonentIndex->setEnabled(true);
                ui.spbAbonentIndex->setMaximum(sul->sul_total_abonents()-1);

            } else {

                ui.spbAbonentIndex->setEnabled(false);
                ui.spbAbonentIndex->setMaximum(0);
            }

	    ui.spbAbonentIndex->setMinimum(0);
	    ui.spbAbonentIndex->setValue(0);
	    ui.abonentIndex->setValue(0);
	    update_abonent_address(ui.spbAbonentIndex->value());
            update_abonent_firmware(ui.spbAbonentIndex->value());
            ui.lbActiveAbonents->setText(QString::number(sul->sul_active_abonents()));
            update_screen();
        }

        display_timer_counter = 0;

        return;
    }

    if(status == 0) {

        switch(task_code) {
            case task_setup_eeprom:
                sul->sul_beam_position(ui.value_x0->value(),
                                       ui.value_y0->value(),
                                       ui.cbZone->currentIndex(),
                                       RAY_NARROW,
                                       ui.cbSphere->isChecked());
                bar->showMessage(QString::fromUtf8("Параметры установлены из FLASH. Время усановки: ") + QString::number(display_timer_counter/2) + QString::fromUtf8(" сек"));
            break;
            case task_setup_ram:
                sul->sul_beam_position(ui.value_x0->value(),
                                       ui.value_y0->value(),
                                       0,
                                       RAY_NARROW,
                                       ui.cbSphere->isChecked());
                bar->showMessage(QString::fromUtf8("Параметры установлены из RAM. Время усановки: ") + QString::number(display_timer_counter/2) + QString::fromUtf8(" сек"));
            break;
            default:
                bar->showMessage(QString::fromUtf8("Выполнение: ОК. Время выполнения операции: ") + QString::number(display_timer_counter/2) + QString::fromUtf8(" сек"));
        }

    } else {
        bar->showMessage(QString::fromUtf8("Выполнение: Ошибка. Время выполнения операции: ") + QString::number(display_timer_counter/2) + QString::fromUtf8(" сек"));
    }

    switch(ui.toolBox->currentIndex()) {
            case 1: fill_flash(); break;
            case 2: fill_ram(); break;
    }

    display_timer_counter = 0;
}

//-----------------------------------------------------------------------------

void sul_monitor::display_timer_event()
{
    ++display_timer_counter;

    QString taskDescription;

    switch(last_started_task) {
    case task_rescan_modules:
    case task_erase_eeprom:
    case task_erase_ram:
    case task_load_ram:
    case task_load_ram_codes: {
        taskDescription = QString::fromUtf8(" Выполнение ... ") + QString::number(display_timer_counter/2) + tr(" сек");
    } break;
    case task_load_eeprom: {
        const struct flash_loading_status& fs = sul->sul_flash_loading_status();
        taskDescription = QString::fromUtf8(" Абонент: ") + QString::number(fs.module) +
                          QString::fromUtf8(" Сегмент: ") + QString::number(fs.data_segment) +
                          QString::fromUtf8(" Блок: ") + QString::number(fs.data_block) +
                          QString::fromUtf8(" Ошибок: ") + QString::number(fs.total_error);
    } break;
    case task_setup_eeprom: {
        taskDescription = QString::fromUtf8(" Инициализация из FLASH ... ") + QString::number(display_timer_counter/2) + QString::fromUtf8(" сек");
    } break;
    case task_setup_ram: {
        taskDescription = QString::fromUtf8(" Инициализация из RAM ... ") + QString::number(display_timer_counter/2) + QString::fromUtf8(" сек");
    } break;
    }

    if((display_timer_counter % 1) == 0) {
        bar->showMessage(taskDescription);
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::set_dbgtimer(int val)
{
    dbg_timer->setInterval(val);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//		    Запуск и останов сканирования
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void sul_monitor::start_scanner()
{
        if(timer->isActive()) {

                stop_scanner();

        } else {

                set_scanner();

                timer->setInterval(ui.period->value());
                timer->start();

                ui.btnStart->setText(QString::fromUtf8("Стоп"));
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::update_scanner_info()
{
    double dFx = 0;
    double dFy = 0;

    sul->sul_phase_incursion(dFx,dFy);

    unsigned uFx = 0;
    unsigned uFy = 0;

    sul->sul_phase_incursion(uFx,uFy);

    ui.currentX->setText(QString::number(scan->get_x()));
    ui.currentY->setText(QString::number(scan->get_y()));

    ui.currentXcode->setText("0x"+QString::number(uFx,16));
    ui.currentYcode->setText("0x"+QString::number(uFy,16));

    ui.phaseIncursionX->setText(QString::number(dFx));
    ui.phaseIncursionY->setText(QString::number(dFy));
}

//-----------------------------------------------------------------------------

void sul_monitor::stop_scanner()
{
        if(timer->isActive()) {

                timer->stop();
                scan->stop();

                ui.btnStart->setText(QString::fromUtf8("Старт"));
        }

        update_scanner_info();

        if(graph) graph->repaint();
        if(radar) radar->update_screen();
}

//-----------------------------------------------------------------------------

void sul_monitor::step_scanner()
{
    if(scan->step()) {

        if( sul->sul_beam_position( scan->get_x(),
                                    scan->get_y(),
                                    ui.cbZone->currentIndex(),
                                    RAY_NARROW,
                                    ui.cbSphere->isChecked()) < 0 )
        {
        }

    }

    update_scanner_info();

    if(graph) graph->repaint();
    if(radar) radar->update_screen();
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

        update_scanner_info();

        if(graph) graph->repaint();
        if(radar) radar->update_screen();
}

//-----------------------------------------------------------------------------

void sul_monitor::setup_beam()
{
    std::cout << "sul_monitor::setup_beam()" << std::endl;

    scan->set_x(ui.value_x0->value());
    scan->set_y(ui.value_y0->value());

    if( sul->sul_beam_position(scan->get_x(),
                               scan->get_y(),
                               ui.cbZone->currentIndex(),
                               RAY_NARROW,
                               ui.cbSphere->isChecked()) < 0)
    {
        bar->showMessage(QString::fromUtf8("Ошибка установки луча."));
    } else {
        bar->showMessage(QString::fromUtf8("Луч установлен."));
    }

    update_scanner_info();

    if(graph) graph->repaint();
    if(radar) radar->update_screen();
}

//-----------------------------------------------------------------------------

void sul_monitor::update_beam_position(double X, double Y)
{
    ui.value_x0->setValue(X);
    ui.value_y0->setValue(Y);

    setup_beam();
}


/////////////////////////////////////////////////////////////////////
//              Изменение параметров сканирования
/////////////////////////////////////////////////////////////////////

void sul_monitor::x0_change(double X)
{
    if(ui.cbTrackMode->isChecked())
        setup_beam();
}

//-----------------------------------------------------------------------------

void sul_monitor::y0_change(double Y)
{
    if(ui.cbTrackMode->isChecked())
        setup_beam();
}

//-----------------------------------------------------------------------------

void sul_monitor::dr_change()
{
        const double pi = 3.1415926535;
        scan->set_dr(ui.step_dr->value());
        ui.value_x0->setSingleStep(ui.step_dr->value()*cos(ui.scanAngle->value()*pi/180.0));
        ui.value_y0->setSingleStep(ui.step_dr->value()*sin(ui.scanAngle->value()*pi/180.0));
}

//-----------------------------------------------------------------------------

void sul_monitor::angle_change()
{
        const double pi = 3.1415926535;
        scan->set_angle(ui.scanAngle->value());
        ui.value_x0->setSingleStep(ui.step_dr->value()*cos(ui.scanAngle->value()*pi/180.0));
        ui.value_y0->setSingleStep(ui.step_dr->value()*sin(ui.scanAngle->value()*pi/180.0));
}

//-----------------------------------------------------------------------------

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
        angle_change();
}

/////////////////////////////////////////////////////////////////////
//          Прерывание таймера при сканировании
/////////////////////////////////////////////////////////////////////

void sul_monitor::timer_event()
{
    if(ui.cbTrackMode->isChecked()) {

        setup_beam();

    } else {

        if(!scan->step()) {
                stop_scanner();
                return;
        }

        if( sul->sul_beam_position( scan->get_x(),
                                    scan->get_y(),
                                    ui.cbZone->currentIndex(),
                                    RAY_NARROW,
                                    ui.cbSphere->isChecked()) < 0)
        {
            bar->showMessage(QString::fromUtf8("Ошибка установки луча."));
        } else {
            bar->showMessage(QString::fromUtf8("Луч установлен."));
        }
    }

    ui.progressBar->setValue(scan->get_index());

    update_scanner_info();

    if(graph) graph->repaint();
    if(radar) radar->update_screen();
}

/////////////////////////////////////////////////////////////////////
//              � исование положения луча и состояния каналов
/////////////////////////////////////////////////////////////////////

void sul_monitor::show_beam_position()
{
    if(graph) graph->show();
}

///////////////////////////////////////////////////////////////////////
//		Заполнение таблиц данными из RAM/FLASH
///////////////////////////////////////////////////////////////////////

void sul_monitor::tool_change(int index)
{
        //cout << "sul_monitor::tool_change()" << endl;
        switch(index) {
                case 1: fill_flash(); break;
                case 2: fill_ram(); break;
                case 3: fill_abonent_form(); break;
        }
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_ram()
{
    int abonent_index = ui.spbRamAbonentNumber->value();
    int block = abonent_index;

    //cout << "sul_monitor::fill_ram(" << block << ")" << endl;

    const vector<double>& data_ = sul->sul_ram_block(0,block);
    if(data_.empty()){
        bar->showMessage(QString::fromUtf8("Ошибка! Не могу выделить память для абонента ") + QString::number(abonent_index));
        return;
    }

    rtable->changeSignal(false);
    fill_table(rtable->model(), data_);
    rtable->changeSignal(true);

    update_ram_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_flash()
{
    int abonent_index = ui.spbFlashAbonentNumber->value();
    int segment = sul->sul_flash_find_segment(ui.cbFlashSegmentName->currentText().toStdString().c_str());
    int block = abonent_index;

    cout << "sul_monitor::fill_flash(): start" << endl;

    const vector<double>& data_ = sul->sul_flash_block(segment,block);
    if(data_.empty()){
        bar->showMessage(QString::fromUtf8("Ошибка! Вектор данных пуст. Абонент ") + QString::number(abonent_index));
        return;
    }

    ftable->changeSignal(false);
    fill_table(ftable->model(), data_);
    ftable->changeSignal(true);

    cout << "sul_monitor::fill_flash(): fin" << endl;

    update_flash_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::fill_table(QAbstractItemModel *model, const vector<double>& data)
{
    if(data.empty()) return;

    if(data.size() != (unsigned)model->rowCount()*model->columnCount()) {
        bar->showMessage(QString::fromUtf8("Неправильный размер данных для отображения."));
        return;
    }

    int idx = 0;
    int value = 0;

    //cout << "sul_monitor::fill_table(): vector size = " << data.size() << endl;
    //cout << "sul_monitor::fill_table(): rowCount = " << model->rowCount() << endl;
    //cout << "sul_monitor::fill_table(): columnCount = " << model->columnCount() << endl;

    for (int nRow = 0; nRow < model->rowCount(); ++nRow) {

            for (int nCol = 0; nCol < model->columnCount(); ++nCol) {

                    QModelIndex index = model->index(nRow, nCol);

                    value = data[idx];

                    //cout << "sul_monitor::fill_table(): idx = " <<
                    // idx << " val = " << value;

                    model->setData( index, value );

                    //cout << " ok" << endl;

                    idx++;
            }
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::open_flash()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = getFileName(QString::fromUtf8("config files (*.cfg)"));
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл конфигурации"));
        return;
    } else {
        bar->showMessage(QString::fromUtf8("Файл конфигурации: ") + fileName);
    }

    if( sul->sul_flash_reconfig( fileName.toStdString().c_str() ) < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка реконфигурации СУЛ"));
        return;
    }

    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::erase_flash()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_erase_eeprom);

    last_started_task = task_erase_eeprom;

    display_timer->start();

    fill_flash();
}

//-----------------------------------------------------------------------------

void sul_monitor::load_flash()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_load_eeprom);

    last_started_task = task_load_eeprom;

    display_timer->start();
}

//-----------------------------------------------------------------------------

void sul_monitor::save_flash()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = getFileName(QString::fromUtf8("config files (*.cfg)"));
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(QString::fromUtf8("Файл для сохранения конфигурации: ") + fileName);
    }

    if( sul->sul_flash_save(fileName.toStdString().c_str()) < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка сохранения данных RAM"));
        return;
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::update_flash_dispaly()
{
    cout << "sul_monitor::update_flash_dispaly()" << endl;

    int abonent_index = ui.spbFlashAbonentNumber->value();
    int abonent_space_crc = sul->sul_flash_space_crc(abonent_index);
    int abonent_device_crc = sul->sul_flash_crc(abonent_index);

    ui.gbFlashData->setTitle(  QString::fromUtf8(" Модуль ") + QString::number(abonent_index) +
                               QString::fromUtf8(" Адрес 0x") + QString::number(sul->sul_abonent_address(abonent_index),16) +
                               QString::fromUtf8(". CRC данных: 0x") +
                               QString::number(abonent_space_crc,16) +
                               QString::fromUtf8(" CRC модуля: 0x") +
                               QString::number(abonent_device_crc,16) );

    int total_space_crc = sul->sul_flash_space_crc();
    //int total_device_crc = sul->sul_flash_crc();
    //int total_device_crc = 0xFFFF;
    ui.lblFileCRC->setText(QString::fromUtf8("0x")+QString::number(total_space_crc,16));
    //ui.lblHwCRC->setText(QString::fromUtf8("0x")+QString::number(total_device_crc,16));
    cout << "sul_monitor::update_flash_dispaly(): complete" << endl;
}

//-----------------------------------------------------------------------------

void sul_monitor::flashItemChanged( int value, int offset  )
{
    cout << "flashItemChanged(): value = " << value << " offset = " << offset << endl;

    double  data(value);

    int segment = sul->sul_flash_find_segment(ui.cbFlashSegmentName->currentText().toStdString().c_str());
    int abonent_index = ui.spbFlashAbonentNumber->value();

    if( sul->sul_flash_set_element(segment, abonent_index, offset, data) < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка обновления данных конфигурации FLASH"));
        return;
    }

    update_flash_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::ramItemChanged( const QModelIndex &index )
{
    const QAbstractItemModel *m = index.model();

    cout << "sul_monitor::ramItemChanged(): row = " << index.row()  << " col = " << index.column() << endl;

    double  value(m->data(index).toInt());
    int abonent_index = ui.spbRamAbonentNumber->value();
    int offset = index.row()*m->columnCount() + index.column();

    cout << "sul_monitor::ramItemChanged(): value = " << value << " offset = " << offset << endl;

    if( sul->sul_ram_set_element(0,
                             abonent_index,
                             offset,
                             value) < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка обновления данных конфигурации RAM"));
        return;
    }

    if( sul->sul_ram_load(NULL,abonent_index) < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка записи данных конфигурации RAM"));
        return;
    }

    Sleep(1);

    int res = sul->sul_setup_from_ram(abonent_index);
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка передача данных из RAM в ПЛИС."));
        return;
    }

    Sleep(1);

    if( sul->sul_beam_position() < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка установки луча"));
        return;
    }

    bar->showMessage(QString::fromUtf8("Абонент ") + QString::number(abonent_index) +
                     QString::fromUtf8(", канал: ") + QString::number(offset) +
                     QString::fromUtf8(", данные: ") + QString::number(value) );

    Sleep(1);

    update_ram_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::ramItemChanged( int value, int offset )
{
    cout << "ramItemChanged(): value = " << value << " offset = " << offset << endl;

    double  data(value);
    int abonent_index = ui.spbRamAbonentNumber->value();

    if( sul->sul_ram_set_element(0,
                             abonent_index,
                             offset,
                             data) < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка обновления данных конфигурации RAM"));
        return;
    }

    if( sul->sul_ram_load(NULL,abonent_index) < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка записи данных конфигурации RAM"));
        return;
    }

    Sleep(1);

    int res = sul->sul_setup_from_ram(abonent_index);
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка передача данных из RAM в ПЛИС."));
        return;
    }

    Sleep(1);

    if( sul->sul_beam_position() < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка установки луча"));
        return;
    }

    bar->showMessage(QString::fromUtf8("Абонент ") + QString::number(abonent_index) +
                     QString::fromUtf8(", канал: ") + QString::number(offset) +
                     QString::fromUtf8(", данные: ") + QString::number(value) );

    Sleep(1);

    update_ram_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::update_ram_dispaly()
{
/*
    cout << "sul_monitor::update_ram_dispaly()" << endl;

    int abonent_index = ui.spbRamAbonentNumber->value();

    ui.gbRamData->setTitle(  QString::fromUtf8(" Абонент ") + QString::number(abonent_index) +
                             QString::fromUtf8(" Адрес 0x") + QString::number(sul->sul_abonent_address(abonent_index),16) +
                             QString::fromUtf8(". CRC данных: 0x") +
                             QString::number(sul->sul_ram_space_crc(abonent_index),16) +
                             QString::fromUtf8(" CRC абонента: 0x") +
                             QString::number(sul->sul_ram_crc(abonent_index),16) );
*/
    cout << "sul_monitor::update_ram_dispaly()" << endl;

    int abonent_index = ui.spbRamAbonentNumber->value();
    int abonent_space_crc = sul->sul_ram_space_crc(abonent_index);
    int abonent_device_crc = sul->sul_ram_crc(abonent_index);

    ui.gbRamData->setTitle(  QString::fromUtf8(" Модуль ") + QString::number(abonent_index) +
                               QString::fromUtf8(" Адрес 0x") + QString::number(sul->sul_abonent_address(abonent_index),16) +
                               QString::fromUtf8(". CRC данных: 0x") +
                               QString::number(abonent_space_crc,16) +
                               QString::fromUtf8(" CRC модуля: 0x") +
                               QString::number(abonent_device_crc,16) );

    //int total_space_crc = sul->sul_ram_space_crc();
    //int total_device_crc = sul->sul_flash_crc();
    //int total_device_crc = 0xFFFF;
    //ui.lblFileCRC->setText(QString::fromUtf8("0x")+QString::number(total_space_crc,16));
    //ui.lblHwCRC->setText(QString::fromUtf8("0x")+QString::number(total_device_crc,16));
    cout << "sul_monitor::update_ram_dispaly(): complete" << endl;
}

//-----------------------------------------------------------------------------

void sul_monitor::set_ram()
{
    //cout << "sul_monitor::set_ram()" << endl;

    int abonent_index = ui.spbRamAbonentNumber->value();
    int segment = ui.cbFlashSegmentName->currentIndex();
    int block = abonent_index;
    double pattern = 0;

    // заполняем конфигурационное пространство RAM
    // в соответствии с выбранным типом заполнения
    if(ui.rbtFillRamFlash->isChecked()) {

        const vector<double>& flashData_ = sul->sul_flash_block(segment,block);
        sul->sul_ram_fill_user(0,block,flashData_);

    } else {

        if(ui.rbtFillRamPattern->isChecked()) {

            pattern = ui.patternFixValue->value();
            sul->sul_ram_fill_pattern(0, block, pattern);

        } else {

            if(ui.rbtFillRamRandom->isChecked()) {
                pattern = ui.patternRndValue->value();
                sul->sul_ram_fill_random(0, block, pattern);
            }
        }
    }

    fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::inc_ram_value()
{
    QTableView *t = rtable;
    QModelIndex index = t->currentIndex();

    if(!index.isValid())
        return;

    QAbstractItemModel *m = t->model();

    double val = index.data().toInt() & ui.patternRndValue->value();
    val += ui.spbRamStepValue->value();

    if(val > ui.patternRndValue->value()) {
        val = 0;
    }

    m->setData(index,val);

    int offset = index.row()*m->columnCount() + index.column();
    int abonent_index = ui.spbRamAbonentNumber->value();
    int block = abonent_index;

    sul->sul_ram_set_element(0,block,offset,val);

    // загружаем блок данных для абонента
    sul->sul_ram_load(NULL,abonent_index);

    // команду на установку данных из RAM
    sul->sul_setup_from_ram(abonent_index);

    // устанавливаем луч
    sul->sul_beam_position();

    Sleep(1);

    // обновим картинку
    update_ram_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::dec_ram_value()
{
    QTableView *t = rtable;
    QModelIndex index = t->currentIndex();

    if(!index.isValid())
        return;

    QAbstractItemModel *m = t->model();

    double val = index.data().toInt();
    val -= ui.spbRamStepValue->value();

    if(val < 0) {
        val = ui.patternRndValue->value();
    }

    m->setData(index, val);

    int offset = index.row()*m->columnCount() + index.column();
    int abonent_index = ui.spbRamAbonentNumber->value();
    int block = abonent_index;

    sul->sul_ram_set_element(0,block,offset,val);

    // загружаем блок данных для абонента
    sul->sul_ram_load(NULL,abonent_index);

    // команду на установку данных из RAM
    sul->sul_setup_from_ram(abonent_index);

    // устанавливаем луч
    sul->sul_beam_position();

    Sleep(1);

    // обновим картинку
    update_ram_dispaly();
}

//-----------------------------------------------------------------------------

void sul_monitor::open_ram()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = getFileName(QString::fromUtf8("config files (*.cfg)"));
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл конфигурации"));
        return;
    } else {
        bar->showMessage(QString::fromUtf8("Файл конфигурации: ") + fileName);
    }

    if( sul->sul_ram_reconfig( fileName.toStdString().c_str() ) < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка реконфигурации СУЛ"));
        return;
    }

    fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::erase_ram()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    worker->start_task(task_erase_ram);

    last_started_task = task_erase_ram;

    display_timer->start();

    //fill_ram();
}

//-----------------------------------------------------------------------------

void sul_monitor::load_ram_all()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    if(!ui.cbUpdateRamAll->isChecked()) {
        worker->start_task(task_load_ram);
        last_started_task = task_load_ram;
        display_timer->start();
    } else {

        std::vector<double> data;

        QAbstractItemModel *m = rtable->model();
        for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
            for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
                        QModelIndex index = m->index(nRow, nCol);
                        data.push_back(m->data(index).toDouble());
            }
        }

        int res = 0;
        for(unsigned i=0; i<sul->sul_total_abonents(); i++) {
            res = sul->sul_ram_write(i,data);
            if(res < 0) {
                bar->showMessage(QString::fromUtf8("Ошибка загрузки RAM для абонента ") + QString::number(i));
            } else {
                bar->showMessage(QString::fromUtf8("RAM для абонента ") + QString::number(i) + QString::fromUtf8(" загружена"));
            }
        }
        bar->showMessage(QString::fromUtf8("Загрузка RAM завершена"));
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::save_ram_all()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = getFileName(QString::fromUtf8("config files (*.cfg)"));
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(QString::fromUtf8("Файл для сохранения конфигурации: ") + fileName);
    }

    if( sul->sul_ram_save(fileName.toStdString().c_str()) < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка сохранения данных RAM"));
        return;
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::save_ram_abonent()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    QString add = QString::fromUtf8("-")+QString::number(ui.spbRamAbonentNumber->value());
    QString fileName = getFileName(QString::fromUtf8("config files (*.abn)"));
    QString baseName;
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл для сохранения конфигурации"));
        return;
    } else {

        for(int i=0; i<fileName.length()-4; i++) {

            baseName[i] = fileName.at(i);
        }

        baseName += add;
        baseName += QString::fromUtf8(".abn");

        bar->showMessage(QString::fromUtf8("Файл для сохранения конфигурации: ") + baseName);
    }

    // сохранить данные из таблицы в файл (напрямую)
    fstream  ofs;
    string   str;

    ofs.open( baseName.toStdString().c_str(), ios::out );

    if (!ofs.is_open()) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу открыть файл."));
            return;
    }

    ofs << endl;
    ofs << "; Abonent " << QString::number(ui.spbRamAbonentNumber->value()).toStdString().c_str() << endl;

    QAbstractItemModel *m = rtable->model();
    for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
        for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
                    QModelIndex index = m->index(nRow, nCol);
                    ofs << dec << setw(3) << m->data( index ).toInt() << " ";
        }
        ofs << endl;
    }

    ofs.close();

    return;
}

//-----------------------------------------------------------------------------

void sul_monitor::read_ram_abonent()
{
    if(!sul) {
        bar->showMessage(QString::fromUtf8("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = getFileName(QString::fromUtf8("config files (*.abn)"));
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл конфигурации"));
        return;
    } else {
        bar->showMessage(QString::fromUtf8("Файл конфигурации: ") + fileName);
    }

    // прочитать данные из файла в таблицу для текущего абонента
    fstream  ifs;
    string   str;

    ifs.open( fileName.toStdString().c_str(), ios::in );

    if (!ifs.is_open()) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу открыть файл."));
            return;
    }

    QAbstractItemModel *m = rtable->model();
    int nRow = 0;
    int nCol = 0;
    int offset = 0;
    int abonent_index = ui.spbRamAbonentNumber->value();
    int block = abonent_index;
    double val = 0;

    while(!ifs.eof()) {

        getline( ifs, str );

        if(!str.length()) continue;

        int p = 0;
        if(str.at(0) == ' ') {
            p = str.find_first_not_of(" ",0);
        }

        if(p < 0) continue;

        if((str.at(p) == ';')||(str.at(p) == '\n')) continue;

        int start = 0;
        int stop = 0;
        unsigned idx = 0;

        do {
                start = str.find_first_not_of(" ", stop);
                stop = str.find_first_of(" ", start);

                if(start == -1) break;

                string s = str.substr(start,stop - start);

                val = (double)atof(s.c_str());

                QModelIndex index = m->index(nRow, nCol);
                offset = nRow*m->columnCount() + nCol;

                // обновим данные в конфигурационном пространстве
                sul->sul_ram_set_element(0,block,offset,val);

                // обновим данные в таблице
                m->setData( index, QVariant(s.c_str()) );

                nCol++;

                if(nCol == m->columnCount()) {
                    nCol = 0;
                    nRow++;
                }

        } while ( idx < str.length() );
    }

    ifs.close();

    return;
}

///////////////////////////////////////////////////////////////////////
//			� абота с абонентами
///////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------

void sul_monitor::prepare_abonent_request()
{
        //cout << "prepare_abonent_request()" << endl;

        if(!exchange) {
            bar->showMessage(QString::fromUtf8("Ошибка! Протокл обмена не определен!"));
            return;
        }

        int abonent = ui.abonentIndex->value();
        int cmd = exchange->command_value(ui.abonentCmd->currentIndex());
        int bn = ui.msgBlockNum->value();
        int size = exchange->cmd_to_size(cmd);

        unsigned char *buffer = (unsigned char*)malloc(size);
        userChannelData.clear();

        if(cmd == exchange->command_value("host_set_vendor") ||
           cmd == exchange->command_value("host_set_address") ||
           cmd == exchange->command_value("target_address") ||
           cmd == exchange->command_value("target_vendor")) {
            bn = 14;
            ui.msgBlockNum->setValue(bn);
        }

        ui.msgBlockSize->setValue(size);

        memset(buffer,0,size);

        // Обнуление таблицы принимаемых данных
        tableIn->changeSignal(false);
        QAbstractItemModel *m3 = tableIn->model();
        for (int nCol = 0; nCol < m3->columnCount(); ++nCol) {
                for (int nRow = 0; nRow < m3->rowCount(); ++nRow) {
                        QModelIndex index = m3->index(nRow, nCol);
                        model3->setData( index, 0 );
                }
        }
        tableIn->changeSignal(true);

        // Заполнение таблицы передаваемых данных
        tableOut->changeSignal(false);
        QAbstractItemModel *m2 = tableOut->model();
        for (int nCol = 0; nCol < m2->columnCount(); ++nCol) {
                for (int nRow = 0; nRow < size; ++nRow) {
                        QModelIndex index = m2->index(nRow, nCol);
                        //m2->setData( index, nRow );
                        buffer[nRow] = m2->data( index ).toInt();
                }
        }
        tableOut->changeSignal(true);

        struct host_mdr_dbg hdr = exchange->fill_host_mdr_dbg(abonent,cmd,bn,size);

        // Заполнение таблицы заголовка
        tableHdr->changeSignal(false);
        QAbstractItemModel *m1 = tableHdr->model();
        for (int nCol = 0; nCol < m1->columnCount(); ++nCol) {
                for (unsigned nRow = 0; nRow < sizeof(struct host_mdr_dbg); ++nRow) {
                        QModelIndex index1 = m1->index(nRow, nCol);
                        m1->setData( index1, *((unsigned char*)&hdr + nRow) );
                }
        }
        tableHdr->changeSignal(true);

        if(analizer) {
            analizer->repaint();
        }

        free(buffer);
}

//-----------------------------------------------------------------------------

void sul_monitor::dbg_timer_event()
{
        if(!exchange) {
            bar->showMessage(QString::fromUtf8("Ошибка! Протокл обмена не определен!"));
            return;
        }

        int abonent = ui.abonentIndex->value();
        int cmd = exchange->command_value(ui.abonentCmd->currentIndex());
        int bn = ui.msgBlockNum->value();
        unsigned char data[256];
        int size = exchange->cmd_to_size(cmd);
        ui.msgBlockSize->setValue(size);
        userChannelData.clear();

        memset(data,0,sizeof(data));

        // заполнение данными
        if(exchange->cmd_to_type(cmd) == to_target) {
            QAbstractItemModel *model2 = tableOut->model();
            for (int nCol = 0; nCol < model2->columnCount(); ++nCol) {
                for (int nRow = 0; nRow < size; ++nRow) {
                    QModelIndex index = model2->index(nRow, nCol);
                    data[nRow] = model2->data( index ).toInt();
                }
            }
        }

        if( exchange->dbg_request(abonent,cmd,bn,data,size) < 0 ) {

            bar->showMessage(QString::fromUtf8("Ошибка выполнения запроса"));
            return;
        }

        // Заполнение таблицы принимаемых данных
        if(exchange->cmd_to_type(cmd) == to_host) {
            tableIn->changeSignal(false);
                QAbstractItemModel *model3 = tableIn->model();
                for (int nCol = 0; nCol < model3->columnCount(); ++nCol) {
                    for (int nRow = 0; nRow < size; ++nRow) {
                                QModelIndex index = model3->index(nRow, nCol);
                                model3->setData( index, data[nRow] );
                                userChannelData.push_back(double(data[nRow]));
                    }
                }
                tableIn->changeSignal(true);
        }


        bar->showMessage(QString::fromUtf8("Запрос выполнен."));

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
                        ui.btnSend->setText(QString::fromUtf8("Старт"));
                } else {
                        dbg_timer->setInterval(ui.dbgPeriod->value());
                        ui.btnSend->setChecked(true);
                        ui.btnSend->setText(QString::fromUtf8("Стоп"));
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

                for (int nRow = 0; nRow < n_channels; ++nRow) {

                        QModelIndex index2 = model2->index(nRow, nCol);
                        QModelIndex index3 = model3->index(nRow, nCol);

                        //model2->setData( index2, nRow );
                        model2->setData( index2, 0 );
                        model3->setData( index3, 0 );
                }
        }

        prepare_abonent_request();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_table_view(QTableView *t, int rowh, int colw)
{
/*
        QAbstractItemModel *m = t->model();

        for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
                t->setColumnWidth(nCol,colw);
        }
        for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
                t->setRowHeight(nRow,rowh);
        }
*/
    t->resizeColumnsToContents();
    t->resizeRowsToContents();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_antenna_params_flash()
{
    cout << "sul_monitor::set_antenna_params_flash()" << endl;

    sul->sul_set_levels(ui.spbTopLevel->value(), ui.spbLowLevel->value());

    if( sul->sul_set_scale(ui.spbScaleValue->value(),
                           ui.spbResetDuration->value(),
                           ui.spbPauseDuration->value()) < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка установки параметров длительности и сброса!"));
        Sleep(500);
    }

    worker->start_task(task_setup_eeprom);
    last_started_task = task_setup_eeprom;
    display_timer->start();
}

//-----------------------------------------------------------------------------

void sul_monitor::set_antenna_params_ram()
{
    cout << "sul_monitor::set_antenna_params_ram()" << endl;

    sul->sul_set_levels(ui.spbTopLevel->value(), ui.spbLowLevel->value());

    if( sul->sul_set_scale(ui.spbScaleValue->value(),
                           ui.spbResetDuration->value(),
                           ui.spbPauseDuration->value()) < 0 ) {
        bar->showMessage(QString::fromUtf8("Ошибка установки параметров СУЛ!"));
        return;
    }

    worker->start_task(task_setup_ram);
    last_started_task = task_setup_ram;
    display_timer->start();
}

//-----------------------------------------------------------------------------

void sul_monitor::update_abonent_address(int index)
{
    if(sul->sul_active_abonents()) {

        ui.lbAbonentAddr->setText(QString::number(sul->sul_abonent_address(index)));

    } else {

        ui.lbAbonentAddr->setText(QString::fromUtf8("Нет модулей"));
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::update_abonent_firmware(int index)
{
    if(sul->sul_active_abonents()) {

        unsigned char cpu;
        unsigned char fpga;

        int res = sul->sul_firmware_version(index,&fpga,&cpu);
        if(res == 0) {
            ui.lbCPUVer->setText("CPU: 0x"+QString::number(int(cpu),16));
            ui.lbFPGAVer->setText("PLD: 0x"+QString::number(int(fpga),16));
        } else {
            ui.lbCPUVer->setText(QString::fromUtf8("CPU: 0xff"));
            ui.lbFPGAVer->setText(QString::fromUtf8("PLD: 0xff"));
        }


    } else {

        ui.lbCPUVer->setText(QString::fromUtf8("CPU: 0xff"));
        ui.lbFPGAVer->setText(QString::fromUtf8("PLD: 0xff"));
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::update_screen()
{
    const double pi = 3.1415926535;

    if(!sul) return;

    cout << "sul_monitor::update_screen() - started" << endl;

    ui.value_x0->setSingleStep(ui.step_dr->value()*cos(ui.scanAngle->value()*pi/180.0));
    ui.value_y0->setSingleStep(ui.step_dr->value()*sin(ui.scanAngle->value()*pi/180.0));

    ui.lbActiveAbonents->setText(QString::number(sul->sul_active_abonents()));
    ui.cbFlashSegmentName->setCurrentIndex(0);

    if(radar->isVisible()) radar->update_screen();
//////////////// реализовать в виде функции
    if(sul->sul_active_abonents()) {

        ui.spbAbonentIndex->setEnabled(true);
        ui.spbAbonentIndex->setMaximum(sul->sul_total_abonents()-1);

    } else {

        ui.spbAbonentIndex->setEnabled(false);
        ui.spbAbonentIndex->setMaximum(0);
    }

    ui.spbAbonentIndex->setMinimum(0);
    ui.spbAbonentIndex->setValue(0);
    ui.abonentIndex->setValue(0);

    update_abonent_address(ui.spbAbonentIndex->value());
    update_abonent_firmware(ui.spbAbonentIndex->value());
///////////////////
    cout << "sul_monitor::update_screen() - finished" << endl;
}

//-----------------------------------------------------------------------------
//#include "..\\sul_mdo\\sul_mdo_cmd.h"
//-----------------------------------------------------------------------------
/*
void sul_monitor::vendorSetParam()
{
        int res = 0;
	unsigned char address = ui.spbNewAddress->value();
	unsigned long t_vid = ui.cbVendorTable->currentText().toInt(NULL,16);
        unsigned long h_vid = 0;
        unsigned char checked_addr = 255;

        res = exchange->request(address,"target_address",0,&checked_addr,sizeof(checked_addr));
        if(res == 0) {
            if(address == checked_addr) {

                res = exchange->request(checked_addr,"target_vendor",14,&h_vid,sizeof(h_vid));
                if(res < 0) {
                    bar->showMessage(QString::fromUtf8("Ошибка! Не могу прочитать заводской номер из модуля."));
                    return;
                }

                // перепрограммировать в случае различия заводских номеров
                if(h_vid == t_vid) {

                    res = exchange->request(address,"target_block_msg",0,NULL,0);
                    if(res < 0) {
                        bar->showMessage(QString::fromUtf8("Ошибка! Прием групповых сообщений не заблокирован."));
                        return;
                    }

                    bar->showMessage(QString::fromUtf8("Заводской номер: ") + QString::number(int(h_vid)) +
                                     QString::fromUtf8(" Адрес: ") + QString::number(int(checked_addr)) +
                                     QString::fromUtf8(" - Успешно установлен. Подключите следующий модуль СУЛ."));
                    return;
                }
            }
        } else {
            checked_addr = 255;
        }

        res = exchange->request(checked_addr,"host_set_vendor",14,&t_vid,sizeof(t_vid));
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу записать заводской номер в модуль."));
	    //return;
        }

        Sleep(1);

        res = exchange->request(checked_addr,target_vendor,14,&h_vid,sizeof(h_vid));
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу прочитать заводской номер из модуля."));
            return;
        }

        if(h_vid != t_vid) {
            bar->showMessage(QString::fromUtf8("Ошибка! Заводской номер из модуля не совпадает с табличным."));
            return;
        }

        Sleep(1);

        struct vendor_data data = {0};

        data.vendor_id = t_vid;
        data.address = address;

        res = exchange->request(checked_addr,"host_set_address",14,&data,sizeof(struct vendor_data));
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу установить логический адрес модуля."));
	    //return;
        }

	Sleep(5);

        address = 0;

        res = exchange->request(data.address,"target_address",0,&address,sizeof(address));
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу прочитать логический адрес модуля."));
	    //return;
        }

        if(address != data.address) {
            bar->showMessage(QString::fromUtf8("Ошибка! Логический адрес модуля не установлен."));
	    //return;
        }

        Sleep(1);

        res = exchange->request(address,"target_block_msg",0,NULL,0);
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Прием групповых сообщений не заблокирован."));
	    //return;
        }

        bar->showMessage(QString::fromUtf8("Заводской номер: ") + QString::number(int(data.vendor_id)) +
                         QString::fromUtf8(" Адрес: ") + QString::number(int(data.address)) +
                         QString::fromUtf8(" - Успешно установлен. Подключите следующий модуль СУЛ."));
}
*/
//-----------------------------------------------------------------------------

void sul_monitor::vendorParamUpdate(int value)
{
    unsigned long t_vid = (value << 24) | (value << 16) | (value << 8) | value;
    ui.leVendorID->setText( "0x" + QString::number(t_vid,16) );
}

//-----------------------------------------------------------------------------

void sul_monitor::vendorSetParam()
{
        int res = 0;
        unsigned char address = ui.spbNewAddress->value();
        unsigned long t_vid = (address << 24) | (address << 16) | (address << 8) | address;
        unsigned long h_vid = 0;
        unsigned char checked_addr = 255;

        res = sul->sul_set_vendor(t_vid, checked_addr);
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу записать заводской номер в модуль."));
            return;
        }

        Sleep(200);

        res = sul->sul_get_vendor(h_vid, checked_addr);
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу прочитать заводской номер из модуля."));
            return;
        }

	std::cout << hex << "vendorSetParam(): t_vid " << t_vid << endl;
	std::cout << hex << "vendorSetParam(): h_vid " << h_vid << endl;

        if(h_vid != t_vid) {
            bar->showMessage(QString::fromUtf8("Ошибка! Заводской номер из модуля не совпадает с табличным."));
            return;
        }

        Sleep(200);

        struct vendor_data data;

	data.vendor_id = h_vid;
        data.address = address;

        res = sul->sul_set_abonent_address(h_vid,address);
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу записать логический адрес модуля."));
            return;
        }

        Sleep(200);

	std::cout << hex << "vendorSetParam(): host address " << int(address) << endl;

        address = sul->sul_get_abonent_address(checked_addr);
        if(address == 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Не могу прочитать логический адрес модуля."));
            return;
        }

        std::cout << hex << "vendorSetParam(): target address 0x" << int(address) << endl;

        if(address != data.address) {
            bar->showMessage(QString::fromUtf8("Ошибка! Логический адрес модуля не установлен."));
	    return;
        }
/*
        Sleep(5);

        res = exchange->dbg_request(address,"target_block_msg",0,NULL,0);
        if(res < 0) {
            bar->showMessage(QString::fromUtf8("Ошибка! Прием групповых сообщений не заблокирован."));
            return;
        }
*/
        bar->showMessage(QString::fromUtf8("Заводской номер: 0x") + QString::number(int(data.vendor_id),16) +
                         QString::fromUtf8(" Адрес: ") + QString::number(int(data.address)) +
                         QString::fromUtf8(" - Успешно установлен. Подключите следующий модуль СУЛ."));

}

//-----------------------------------------------------------------------------

void sul_monitor::measureSetParam()
{
/*
    int res = 0;

    unsigned char *ram = (unsigned char *)malloc(sul->sul_ram_block_size());
    if(!ram) {
        bar->showMessage(QString::fromUtf8("Ошибка! Не могу выделить память для блока RAM."));
        return;
    }

    unsigned char *mask = (unsigned char *)malloc(sul->sul_ram_block_size());
    if(!mask) {
        bar->showMessage(QString::fromUtf8("Ошибка! Не могу выделить память для маски каналов RAM."));
        return;
    }

    memset(ram,0,sul->sul_ram_block_size());
    memset(mask,0,sul->sul_ram_block_size());

    int channel = ui.measureChannel->value() - 1;
    int abonent = ui.spbPhaseAbonentNum->value();
    unsigned char phaseCode = ui.measurePhaseCode->value();

    ram[channel] = phaseCode;
    mask[channel] = 1;

    res = exchange->request(abonent,"host_ram_data",0,ram,sul->sul_ram_block_size());
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка! Не могу передать блок RAM."));
        return;
    }

    Sleep(1);

    res = exchange->request(abonent,"target_ram_to_plm",0,NULL,0);
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка передача данных из RAM во FLASH."));
        return;
    }

    Sleep(1);

    res = exchange->request(abonent,"host_set_channel",0,mask,sul->sul_ram_block_size());
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка установки маски каналов."));
        return;
    }

    bar->showMessage(QString::fromUtf8("Код фазы: ") + QString::number(phaseCode) + QString::fromUtf8(" - установлен."));

    if(ui.autoMeasureFlag->isChecked()) {

        if(ui.autoMeasureInc->isChecked()) {
            ui.measurePhaseCode->setValue(phaseCode + ui.autoMeasureIncVal->value());
        } else {
            ui.measurePhaseCode->setValue(phaseCode - ui.autoMeasureDecVal->value());
        }
    }

    res = exchange->request(abonent,"target_reset_channel",0,NULL,0);
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка установки маски каналов."));
        return;
    }
*/
    int res = -1;
    int channel = ui.measureChannel->value();
    int index = ui.spbPhaseAbonentNum->value();
    unsigned char code = ui.measurePhaseCode->value();
    unsigned char data = 0;

    res = sul->sul_set_channel_phase(index,channel,code,&data);
    if(res < 0) {
        bar->showMessage(QString::fromUtf8("Ошибка установки фазы в канале!"));
    } else {
        bar->showMessage(QString::fromUtf8("Установленная фаза: ") + QString::number(int(data)));
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::closeEvent(QCloseEvent * event)
{
    if(graph) graph->close();

    if(radar) radar->close();

    if(analizer) analizer->close();
}

//-----------------------------------------------------------------------------

void sul_monitor::connect_slots()
{
        cout << "sul_monitor::connect_slots()" << endl;

        // событие таймера
        connect(timer,SIGNAL(timeout()),this,SLOT(timer_event()));
        connect(dbg_timer,SIGNAL(timeout()),this,SLOT(dbg_timer_event()));
        connect(ui.period,SIGNAL(valueChanged(int)),this,SLOT(set_dbgtimer(int)));

        // смена направления сканирования
        connect(ui.rbtAxisX,SIGNAL(clicked()),this,SLOT(axis_change()));
        connect(ui.rbtAxisY,SIGNAL(clicked()),this,SLOT(axis_change()));
        connect(ui.rbtAxisXY,SIGNAL(clicked()),this,SLOT(axis_change()));

        // запуск/останов периодического таймера
        connect(ui.btnStart,SIGNAL(clicked()),this,SLOT(start_scanner()));
        connect(ui.btnSetBeam,SIGNAL(clicked()),this,SLOT(setup_beam()));
        connect(graph,SIGNAL(set_beam_position(double,double)),this,SLOT(update_beam_position(double,double)));

        // изменение шага сканирования по Х или Y
        connect(ui.step_dr,SIGNAL(editingFinished()),this,SLOT(dr_change()));

        // изменение значения по Х или Y
        connect(ui.value_x0,SIGNAL(valueChanged(double)),this,SLOT(x0_change(double)));
        connect(ui.value_y0,SIGNAL(valueChanged(double)),this,SLOT(y0_change(double)));

        // изменение угла
        connect(ui.scanAngle,SIGNAL(editingFinished()),this,SLOT(angle_change()));

        // изменение литеры
        connect(ui.cbZone,SIGNAL(currentIndexChanged(int)),this,SLOT(litera_changed()));
        connect(ui.cbUseFi0,SIGNAL(clicked()),this,SLOT(litera_changed()));

        // изменение границ
        connect(ui.scanSectorMax,SIGNAL(editingFinished()),this,SLOT(sector_max_change()));

        // заполнение таблиц
        connect(ui.toolBox,SIGNAL(currentChanged(int)),this,SLOT(tool_change(int)));

        // заполнение данных FLASH
        connect(ui.spbFlashAbonentNumber,SIGNAL(valueChanged(int)),this,SLOT(fill_flash()));
        connect(ui.cbFlashSegmentName,SIGNAL(currentIndexChanged(int)),this,SLOT(fill_flash()));
        connect(ui.btnFlashFileOpen,SIGNAL(clicked()),this,SLOT(open_flash()));
        connect(ui.btnFlashErase,SIGNAL(clicked()),this,SLOT(erase_flash()));
        connect(ui.btnFlashLoad,SIGNAL(clicked()),this,SLOT(load_flash()));
        connect(ui.btnFlashSave,SIGNAL(clicked()),this,SLOT(save_flash()));

        // заполнение данных RAM
        connect(ui.spbRamAbonentNumber,SIGNAL(valueChanged(int)),this,SLOT(fill_ram()));
        connect(ui.btnFillRam,SIGNAL(clicked()),this,SLOT(set_ram()));
        connect(ui.btnIncRamValue,SIGNAL(clicked()),this,SLOT(inc_ram_value()));
        connect(ui.btnDecRamValue,SIGNAL(clicked()),this,SLOT(dec_ram_value()));
        connect(ui.btnRamOpen,SIGNAL(clicked()),this,SLOT(open_ram()));
        connect(ui.btnRamErase,SIGNAL(clicked()),this,SLOT(erase_ram()));
        connect(ui.btnRamLoadAll,SIGNAL(clicked()),this,SLOT(load_ram_all()));
        connect(ui.btnRamSaveAll,SIGNAL(clicked()),this,SLOT(save_ram_all()));
        connect(ui.btnSaveAbonentRamFile,SIGNAL(clicked()),this,SLOT(save_ram_abonent()));
        connect(ui.btnReadAbonentRamFile,SIGNAL(clicked()),this,SLOT(read_ram_abonent()));

        // рисование
        connect(ui.btnDraw,SIGNAL(clicked()),this,SLOT(show_beam_position()));
        connect(ui.btnShowView,SIGNAL(clicked()),this,SLOT(show_user_data()));

        // работа с абонентами
        connect(ui.btnSend,SIGNAL(clicked()),this,SLOT(send_abonent_request()));
        connect(ui.abonentCmd,SIGNAL(currentIndexChanged(int)),this,SLOT(prepare_abonent_request()));
        connect(ui.abonentIndex,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));
        connect(ui.msgBlockNum,SIGNAL(valueChanged(int)),this,SLOT(prepare_abonent_request()));

        connect(tableHdr,SIGNAL(cellChanged(int,int)),this,SLOT(prepare_abonent_request()));
        connect(tableOut,SIGNAL(cellChanged(int,int)),this,SLOT(prepare_abonent_request()));
        connect(tableHdr,SIGNAL(cellChanged(QModelIndex)),this,SLOT(prepare_abonent_request()));
        connect(tableOut,SIGNAL(cellChanged(QModelIndex)),this,SLOT(prepare_abonent_request()));

        connect(ui.btnGridArray,SIGNAL(clicked()),this,SLOT(show_antenna()));

        // отрисовка результатов проверки в анализаторе
        //connect(test,SIGNAL(abonent_test_complete(int)),analizer,SLOT(show_abonent_test(int)));
        //connect(test,SIGNAL(abonent_changed(int)),analizer,SLOT(set_abonent_number(int)));

        // установка коэффициента масштаба, длительности сигнала сброса и паузы для всей решетки
        connect(ui.btnSetScaleFlash,SIGNAL(clicked()),this,SLOT(set_antenna_params_flash()));

        // установка коэффициента масштаба, длительности сигнала сброса и паузы для всей решетки
        connect(ui.btnSetScaleRam,SIGNAL(clicked()),this,SLOT(set_antenna_params_ram()));

        // информация об активных абонентах
        connect(ui.spbAbonentIndex,SIGNAL(valueChanged(int)),this,SLOT(update_abonent_address(int)));
        connect(ui.spbAbonentIndex,SIGNAL(valueChanged(int)),this,SLOT(update_abonent_firmware(int)));

        // изменение данных в таблице для FLASH и RAM
        connect(ftable,SIGNAL(cellChanged(int,int)),this,SLOT(flashItemChanged(int,int)));
        connect(rtable,SIGNAL(cellChanged(const QModelIndex&)),this,SLOT(ramItemChanged(const QModelIndex&)));

        // обработка событий для измерений фазы
        connect(ui.measureSetParam,SIGNAL(clicked()),this,SLOT(measureSetParam()));

        // измененние заводского номера модуля
        connect(ui.btnNewModuleSettings,SIGNAL(clicked()),this,SLOT(vendorSetParam()));
        connect(ui.spbNewAddress,SIGNAL(valueChanged(int)),SLOT(vendorParamUpdate(int)));

        // обработка сигналов потока
        connect(worker,SIGNAL(task_status(int,int)),this,SLOT(processing_status(int,int)));

        // запуск таймера принудительной установки луча
        connect(ui.cbBeamSetupTimerOn,SIGNAL(clicked(bool)),this,SLOT(beamSetupTimerOn(bool)));

        connect(ui.pbRescanModule,SIGNAL(clicked()),this,SLOT(RescanModule()));

        connect(ui.pbCalculateCorrectionPhase,SIGNAL(clicked()),this,SLOT(CalcualteCorrectionCodes()));
        connect(ui.pbCorrPhaseSaveToFile,SIGNAL(clicked()),this,SLOT(SaveCorrectionCodes()));
        connect(ui.pbCorrPhaseLoadToSUL,SIGNAL(clicked()),this,SLOT(LoadCorrectionCodes()));

        connect(ui.pbInterfaceUpdate,SIGNAL(clicked()),this,SLOT(interface_update()));

        connect(ui.pbDebug,SIGNAL(clicked()),this,SLOT(debug_button()));
}

//-----------------------------------------------------------------------------

void sul_monitor::beamSetupTimerOn(bool checked)
{
    if(!beamTimer) {
        bar->showMessage(QString::fromUtf8("Ошибка! Таймер не создан."));
        return;
    }

    if(checked) {
        beamTimer->setInterval(ui.leBeamSetupTimerPeriod->text().toInt());
        connect(beamTimer, SIGNAL(timeout()), this, SLOT(setup_beam()));
        beamTimer->start();
        bar->showMessage(QString::fromUtf8("Таймер установлен."));
    } else {
        beamTimer->stop();
        disconnect(beamTimer,SIGNAL(timeout()),this,SLOT(setup_beam()));
        bar->showMessage(QString::fromUtf8("Таймер отключен."));
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::show_user_data()
{
    if(analizer) {
        analizer->paint_user_data(&userChannelData);
        analizer->show();
    }
}

//-----------------------------------------------------------------------------

void sul_monitor::CalcualteCorrectionCodes()
{
    sul->sul_calculate_correction_codes(ui.spbWaveLength->value(),ui.spbFocusValue->value(),ui.cbUseFi0->isChecked());
    emit RepaintAntennaWidget();
}

//-----------------------------------------------------------------------------

void sul_monitor::SaveCorrectionCodes()
{
    QString filter = (ui.cbAddToFile->isChecked() ? QString::fromUtf8("config files (*.cfg)") : QString::fromUtf8("phase files (*.phase)"));
    QString fileName = getFileName(filter);
    if(fileName.isEmpty()) {
        bar->showMessage(QString::fromUtf8("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(QString::fromUtf8("Файл для сохранения конфигурации: ") + fileName);
    }

    fstream  ofs;
    ofs.open( fileName.toStdString().c_str(), (ui.cbAddToFile->isChecked() ? (ios::out|ios::app) : ios::out) );

    if (!ofs.is_open()) {
        bar->showMessage(QString::fromUtf8("Ошибка! Не могу открыть файл."));
        return;
    }

    ofs << endl;
    ofs << "[ F " << ui.spbFocusValue->value() << ",  L " << ui.spbWaveLength->value() << " ]" << endl;
    ofs << endl;

    sul->sul_save_correction_codes(ofs);

    ofs.close();
}

//-----------------------------------------------------------------------------

void sul_monitor::LoadCorrectionCodes()
{
    std::cout << "sul_monitor::LoadCorrectionCodes()" << endl;

    worker->start_task(task_load_ram_codes);

    last_started_task = task_load_ram_codes;

    display_timer->start();
}

//-----------------------------------------------------------------------------

void sul_monitor::RescanModule()
{
    if(!sul)
        return;

    worker->start_task(task_rescan_modules);

    last_started_task = task_rescan_modules;

    display_timer->start();
}

//-----------------------------------------------------------------------------

void sul_monitor::show_antenna()
{
    if(radar) {
        radar->show();
        return;
    }

    radar->show();
}

//---------------------------------------------------------------------------------------

void sul_monitor::interface_update()
{
    if(dev) {
        delete dev;
        dev = NULL;
    }

#ifdef __linux__
    dev = factoryDev(ifcName.toStdString().c_str(), O_CREAT|O_EXCL, O_RDWR );
#else
    dev = factoryDev(ifcName.toStdString().c_str(), FILE_FLAG_NO_BUFFERING, ifcSpeed);
#endif
    if(dev) {
        sul->sul_connect_device(dev);
    }

    QString msg = QString::fromUtf8("Интерфейс: ") + ifcName;

    bar->showMessage(msg);
}

//---------------------------------------------------------------------------------------

void sul_monitor::debug_button()
{
    std::cout << __FUNCTION__ << "()" << endl;
/*
    if(sul->sul_active_abonents()) {

        unsigned char cpu;
        unsigned char fpga;

        int res = sul->sul_firmware_version(0,&fpga,&cpu);
        if(res == 0) {
            ui.lbCPUVer->setText("CPU: 0x"+QString::number(int(cpu),16));
            ui.lbFPGAVer->setText("PLD: 0x"+QString::number(int(fpga),16));
        } else {
            ui.lbCPUVer->setText( QString::fromUtf8("CPU: 0xff"));
            ui.lbFPGAVer->setText( QString::fromUtf8("PLD: 0xff"));
        }
    }
*/
    sul->sul_enable_transmission(ui.pbDebug->isChecked());
}

//---------------------------------------------------------------------------------------

void sul_monitor::litera_changed()
{
    std::cout << __FUNCTION__ << "()" << endl;

    ui.spbWaveLength->setValue(litera.at(ui.cbZone->currentIndex()));

    sul->sul_calculate_correction_codes(ui.spbWaveLength->value(),
                                        ui.spbFocusValue->value(),
                                        ui.cbUseFi0->isChecked());
}

//---------------------------------------------------------------------------------------

QString sul_monitor::getFileName(QString filter)
{
    QFileDialog *fileDialog = new QFileDialog();
    QString fileName = fileDialog->getSaveFileName(this, tr("��������� ����"),".",filter);
    delete fileDialog;
    return fileName;
}
