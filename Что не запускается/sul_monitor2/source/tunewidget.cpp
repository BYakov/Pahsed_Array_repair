#include "tunewidget.h"
#include "ui_tunewidget.h"

//-----------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>
#include <cstring>
#include <cmath>
//-----------------------------------------------------------------------------

using namespace std;

//-----------------------------------------------------------------------------

tunewidget::tunewidget(console& log, sul_base* sul_system, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::tunewidget), tty(log), sul(sul_system)
{
    ui->setupUi(this);

    bar = statusBar();

    set_table_view(ui->ownPhase);
    set_table_view(ui->corrPhase);
    set_table_view(ui->addPhase);
    set_table_view(ui->sumPhase);

    ui->ownPhase->setEditTriggers(0);
    ui->corrPhase->setEditTriggers(0);
    ui->sumPhase->setEditTriggers(0);

    R_.clear();
    Rxy_.clear();
    fi0_.clear();
    x_.clear();
    y_.clear();
    s_.clear();
    fk_.clear();
    fa_.clear();
    phase_.clear();

    Xmax_ = 0;
    Ymax_ = 0;
    Xmin_ = 0;
    Ymin_ = 0;
    x0_ = 0;
    y0_ = 0;

    fi0_ = sul->sul_phase_data();
    x_ = sul->sul_x_data();
    y_ = sul->sul_y_data();

    tty << "fi0.size() = " << fi0_.size() << "\n";
    tty << "x_.size() = " << x_.size() << "\n";
    tty << "y_.size() = " << y_.size() << "\n";
    tty << "sul_total_channels() = " << sul->sul_total_channels() << "\n";

    for(int i=0; i<sul->sul_total_channels(); i++) {

        if(x_.at(i) >= Xmax_) Xmax_ = x_.at(i);
        if(x_.at(i) < Xmin_) Xmin_ = x_.at(i);

        if(y_.at(i) >= Ymax_) Ymax_ = y_.at(i);
        if(y_.at(i) < Ymin_) Ymin_ = y_.at(i);

        fa_.push_back(0);
    }

    x0_ = 0.5*(Xmax_-Xmin_);
    y0_ = 0.5*(Ymax_-Ymin_);

    tty << "tunewidget::tunewidget(): x0_ = " << x0_ << ", y0_ = " << y0_ << "\n";

    //! заполним количесвто модулей
    for(unsigned x=0; x < sul->sul_total_abonents(); x++) {
        ui->cbModuleNumber->addItem(QString::number(x));
    }

    array = new array_antenna(sul->sul_x_data(),sul->sul_y_data());
    ui->spbElementSize->setValue(14);
    array->elementSizeChange(ui->spbElementSize->value());
    ui->graphLayout->addWidget(array);
    ui->spbdX->setValue(sul->sul_x_step());
    ui->spbdY->setValue(sul->sul_y_step());

    connect(ui->spbElementSize,SIGNAL(valueChanged(int)),array,SLOT(elementSizeChange(int)));
    connect(ui->cbModuleNumber,SIGNAL(currentIndexChanged(int)),this,SLOT(ModuleNumberChanged(int)));
    connect(ui->cbDrawSelector,SIGNAL(currentIndexChanged(int)),this,SLOT(DrawSelectorChanged(int)));
    connect(ui->pbCalculateFik,SIGNAL(clicked()),this,SLOT(CalculatePhase()));
    connect(ui->spbdX,SIGNAL(valueChanged(double)),this,SLOT(CalculatePhase()));
    connect(ui->spbdY,SIGNAL(valueChanged(double)),this,SLOT(CalculatePhase()));
    connect(ui->spbFocus,SIGNAL(valueChanged(double)),this,SLOT(CalculatePhase()));
    connect(ui->spbLambda,SIGNAL(valueChanged(double)),this,SLOT(CalculatePhase()));
    connect(ui->rbViewCode,SIGNAL(clicked(bool)),this,SLOT(ViewCode(bool)));
    connect(ui->rbViewDegrees,SIGNAL(clicked(bool)),this,SLOT(ViewDegrees(bool)));

    //connect(ui->addPhase,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(addPhaseItemChanged(QTableWidgetItem*)));
    //connect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));
    //connect(ui->addPhaseDistribution,SIGNAL(currentIndexChanged(int)),this,SLOT(distributionChanged(int)));

    connect(ui->pbOwnPhaseLoad,SIGNAL(clicked()),this,SLOT(OwnPhaseLoad()));
    connect(ui->pbOwnPhaseSave,SIGNAL(clicked()),this,SLOT(OwnPhaseSave()));

    connect(ui->pbAddPhaseCalc,SIGNAL(clicked()),this,SLOT(addPhaseCalculate()));
    connect(ui->pbAddPhaseSave,SIGNAL(clicked()),this,SLOT(AddPhaseSave()));
    connect(ui->pbAddPhaseLoad,SIGNAL(clicked()),this,SLOT(AddPhaseLoad()));

    connect(ui->pbCorrPhaseSave,SIGNAL(clicked()),this,SLOT(CalcPhaseSave()));

    connect(ui->pbFullPhaseSave,SIGNAL(clicked()),this,SLOT(FullPhaseSave()));
    connect(ui->pbFullPhaseLoad,SIGNAL(clicked()),this,SLOT(FullPhaseLoad()));
    connect(ui->pbFullPhaseToSul,SIGNAL(clicked()),this,SLOT(FullPhaseToSul()));

    calculate_radius();
    DrawSelectorChanged(0);
    ModuleNumberChanged(0);
}

//-----------------------------------------------------------------------------

tunewidget::~tunewidget()
{
    close();

    delete ui;

    R_.clear();
    Rxy_.clear();
    fi0_.clear();
    s_.clear();
    x_.clear();
    y_.clear();
    fk_.clear();
    fa_.clear();
    phase_.clear();

    tty << "tunewidget::~tunewidget()\n";
}

//-----------------------------------------------------------------------------

int tunewidget::set_table_view(QTableWidget *table)
{
    table->setRowCount(8);
    table->setColumnCount(16);

    QAbstractItemModel *m = table->model();
    if(!m)
        return -1;

    for (int nCol = 0; nCol < m->columnCount(); ++nCol) {
        table->setColumnWidth(nCol,50);
    }
    for (int nRow = 0; nRow < m->rowCount(); ++nRow) {
        table->setRowHeight(nRow,20);
    }

    return 0;
}

//-----------------------------------------------------------------------------

int tunewidget::set_table_data(QTableWidget *table, const vector<double>& data)
{
    QAbstractItemModel *model = table->model();
    if(!model)
        return -3;

    if(data.empty())
        return -1;

    if(data.size() <= (unsigned)model->rowCount()*model->columnCount()) {
        bar->showMessage(tr("Неправильный размер данных для отображения."));
        return -2;
    }

    int idx = 0;
    int offset = sul->sul_module_channel_offset(ui->cbModuleNumber->currentIndex());
    int max_idx = sul->sul_abonent_channels(ui->cbModuleNumber->currentIndex());

    bar->showMessage(tr("Смещение: ") + QString::number(offset));

    for (int nRow = 0; nRow < model->rowCount(); ++nRow) {

        for (int nCol = 0; nCol < model->columnCount(); ++nCol) {

            QModelIndex index = model->index(nRow, nCol);

            if(idx < max_idx) {
                double value = data.at(offset + idx++);
                model->setData( index, value );

            } else {
                model->setData( index, 0 );
            }
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

int tunewidget::get_table_data(QTableWidget *table, vector<double>& data)
{
    QAbstractItemModel *model = table->model();
    if(!model)
        return -3;

    if(!data.empty())
        return -1;

    int idx = 0;
    int offset = sul->sul_module_channel_offset(ui->cbModuleNumber->currentIndex());
    int max_idx = sul->sul_abonent_channels(ui->cbModuleNumber->currentIndex());

    bar->showMessage(tr("Смещение: ") + QString::number(offset));

    double value = 0;

    for (int nRow = 0; nRow < model->rowCount(); ++nRow) {

        for (int nCol = 0; nCol < model->columnCount(); ++nCol) {

            if(idx < max_idx) {

                // получим данные из таблицы
                QModelIndex index = model->index(nRow, nCol);
                value = model->data(index).toDouble();

                // сохраним текущий элемент в векторе
                data.at(offset + idx++) = value;
            }
        }
    }

    return data.size();
}

//-----------------------------------------------------------------------------

int tunewidget::save_table_data(QTableWidget *table)
{
    vector<double> data;

    if( get_table_data(table, data) == 0)
        return -1;


    return data.size();
}

//-----------------------------------------------------------------------------

void tunewidget::ModuleNumberChanged(int index)
{
    set_table_data(ui->ownPhase, fi0_);
    set_table_data(ui->corrPhase,fk_);
    set_table_data(ui->addPhase,fa_);
    set_table_data(ui->sumPhase,phase_);
}

//-----------------------------------------------------------------------------

void tunewidget::DrawSelectorChanged(int index)
{
    if(!array)
        return;

    switch(index) {
    case 0:
        array->setParameters(&fi0_);
        break;
    case 1:
        array->setParameters(&fk_);
        break;
    case 2:
        array->setParameters(&fa_);
        break;
    case 3:
        array->setParameters(&phase_);
        break;
    case 4:
        calculate_radius();
        array->setParameters(&R_);
        break;
    }
}

//-----------------------------------------------------------------------------

int tunewidget::calculate_sphere(double R, double L)
{
    double Scale = 360.0/L;
    double val = 0;
    double x = 0;

    fk_.clear();

    for(unsigned item = 0; item < Rxy_.size(); item++) {

        x = Rxy_.at(item)*Rmax_;
        val = fmod(7200.0 - Scale*(sqrt(x*x + R*R) - R), 360.0);
        fk_.push_back(val);
    }

    return fk_.size();
}

//-----------------------------------------------------------------------------

int tunewidget::calculate_phase()
{
    double arg = 0;
    phase_.clear();

    for(unsigned item = 0; item < fk_.size(); item++) {

        arg = fmod(720.0 + fk_.at(item) - fi0_.at(item) + fa_.at(item), 360.0);
        //arg = fmod(720.0 + fk_.at(item) + fa_.at(item), 360.0);
        //arg = fmod(720.0 + fk_.at(item) + fa_.at(item), 255.0);
        phase_.push_back(arg);
    }

    return phase_.size();
}

//-----------------------------------------------------------------------------

int tunewidget::calculate_radius()
{
/*
    double dX = sul->sul_x_step();
    double dY = sul->sul_y_step();

    R_.clear();
    Rxy_.clear();
    Rmin_ = 0;
    Rmax_ = 0;

    for(int i = 0; i < sul->sul_total_channels(); i++) {

        double xc = (x_.at(i) - x0_)*dX;
        double yc = (y_.at(i) - y0_)*dY;

        double val  = sqrt(xc*xc + yc*yc);

        R_.push_back(0);
        Rxy_.push_back(val);

        if(val >= Rmax_) {
            Rmax_ = val;
        }
    }

    for(int i = 0; i < sul->sul_total_channels(); i++) {
        Rxy_[i] /= Rmax_;
        R_[i] = Rxy_[i]*360;
    }

    return Rxy_.size();
*/
    double dX = sul->sul_x_step();
    double dY = sul->sul_y_step();

    R_.clear();
    Rxy_.clear();
    Rmin_ = 0;
    Rmax_ = 0;

    for(unsigned i = 0; i < sul->sul_total_abonents(); i++) {

        struct sul_device M;
        if( sul->sul_abonent_details(i, M) < 0 ) {
            break;
        }

        for(unsigned j=0; j<M.X.size(); j++) {

            struct connector_t& X = M.X.at(j);

            for(unsigned k=0; k<X.channels.size(); k++) {

                struct channel_t& C = X.channels.at(k);

                double xc = (C.entry.x_grid - x0_)*dX;
                double yc = (C.entry.y_grid - y0_)*dY;
                double val  = sqrt(xc*xc + yc*yc);

                if(val >= Rmax_) {
                    Rmax_ = val;
                }

                Rxy_.push_back(val);
            }
        }

    }

    for(unsigned i = 0; i < Rxy_.size(); i++) {
        Rxy_[i] /= Rmax_;
        R_.push_back(Rxy_[i]*360);
    }

    return Rxy_.size();
}

//-----------------------------------------------------------------------------

void tunewidget::CalculatePhase()
{
    int size = calculate_radius();
    if(size < 0) {
        tty << "tunewidget::CalculateFik(): calculate_radius() - " << size << "\n";
        return;
    }
    tty << "tunewidget::CalculateFik(): calculate_radius() - " << size << "\n";

    size = calculate_sphere(ui->spbFocus->value(),ui->spbLambda->value());
    if(size < 0) {
        tty << "tunewidget::CalculateFik(): calculate_sphere() -  Error" << "\n";
        return;
    }
    tty << "tunewidget::CalculateFik(): calculate_sphere() - " << size << "\n";

    size = calculate_phase();
    if(size < 0) {
        tty << "tunewidget::CalculateFik(): calculate_phase() -  Error" << "\n";
        return;
    }
    tty << "tunewidget::CalculateFik(): calculate_phase() -  " << size << "\n";

    set_table_data(ui->corrPhase,fk_);
    set_table_data(ui->sumPhase,phase_);

    disconnect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));
    set_table_data(ui->addPhase,fa_);
    connect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));

    DrawSelectorChanged(ui->cbDrawSelector->currentIndex());
}

//-----------------------------------------------------------------------------

void tunewidget::ViewDegrees(bool checked)
{
}

//-----------------------------------------------------------------------------

void tunewidget::ViewCode(bool checked)
{
}

//-----------------------------------------------------------------------------

double tunewidget::to_code(double degrees)
{
    return floor(degrees*255.0/360.0);
}

//-----------------------------------------------------------------------------

double tunewidget::to_degrees(double code)
{
    return floor(code*360.0/255.0);
}

//-----------------------------------------------------------------------------

void tunewidget::addPhaseItemChanged(QTableWidgetItem* item)
{
    //tty << item->column() << ", " << item->row() << ": " << item->data().toDouble() << "\n";
}

//-----------------------------------------------------------------------------

void tunewidget::addPhaseCellChanged(int row, int column)
{
    QAbstractItemModel *model = ui->addPhase->model();
    QModelIndex index = model->index(row,column);
    double data = model->data(index).toDouble();

    int offset = sul->sul_module_channel_offset(ui->cbModuleNumber->currentIndex());
    int max_idx = sul->sul_abonent_channels(ui->cbModuleNumber->currentIndex());
    int idx = row*ui->addPhase->columnCount() + column;

    // сохраним текущий элемент в векторе
    if(idx < max_idx) {
        fa_.at(offset + idx) = data;
    }

    tty << "tunewidget::addPhaseCellChanged(" << row << ", " << column << ") = " << data << "\n";

    if(ui->cbDrawSelector->currentIndex() == 3)
        array->repaint();

    return;
}

//-----------------------------------------------------------------------------

void tunewidget::ownPhaseCellChanged(int row, int column)
{
    QAbstractItemModel *model = ui->addPhase->model();
    QModelIndex index = model->index(row,column);
    double data = model->data(index).toDouble();

    int offset = sul->sul_module_channel_offset(ui->cbModuleNumber->currentIndex());
    int max_idx = sul->sul_abonent_channels(ui->cbModuleNumber->currentIndex());
    int idx = row*ui->addPhase->columnCount() + column;

    // сохраним текущий элемент в векторе
    if(idx < max_idx) {
        fi0_.at(offset + idx) = data;
    }

    tty << "tunewidget::addPhaseCellChanged(" << row << ", " << column << ") = " << data << "\n";

    if(ui->cbDrawSelector->currentIndex() == 1)
        array->repaint();

    return;
}

//-----------------------------------------------------------------------------

void tunewidget::addPhaseCalculate()
{
    switch(ui->addPhaseDistribution->currentIndex()) {
    case 0: {
            for(unsigned i=0; i<Rxy_.size(); i++) {
                fa_[i] = 360.0*Rxy_[i];
            }
        } break;
    case 1: {
            for(unsigned i=0; i<Rxy_.size(); i++) {
                fa_[i] = 360.0 - 360.*Rxy_[i];
            }
        } break;
    case 2: {
            for(unsigned i=0; i<Rxy_.size(); i++) {
                double x = Rxy_[i];
                fa_[i] =  360.0*(1.0 - (1.0-0.1)*x*x);
            }
        } break;
    case 3: {
            for(unsigned i=0; i<Rxy_.size(); i++) {
                double x = Rxy_[i];
                fa_[i] =  360.0*cos(0.5*M_PI*x);
            }
        } break;
    case 4: {
            for(unsigned i=0; i<Rxy_.size(); i++) {
                double x = Rxy_[i];
                double y = cos(0.5*M_PI*x);
                fa_[i] =  360.0*y*y;
            }
        } break;
    }

    disconnect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));
    set_table_data(ui->addPhase,fa_);
    connect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));

    array->repaint();
}

//-----------------------------------------------------------------------------

void tunewidget::phaseVectorLoad(vector<double> &data)
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл конфигурации: ") + fileName);
    }

    // прочитать данные из файла в таблицу для текущего абонента
    fstream  ifs;
    string   str;

    ifs.open( fileName.toStdString().c_str(), ios::in );

    if (!ifs.is_open()) {
        bar->showMessage(tr("Ошибка! Не могу открыть файл."));
        return;
    }

    double val = 0;

    data.clear();

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

        do {
            start = str.find_first_not_of(" ", stop);
            stop = str.find_first_of(" ", start);

            if(start == -1)
                break;

            string s = str.substr(start,stop - start);

            val = (double)atof(s.c_str());

            // обновим данные в векторе
            data.push_back(val);

        } while ( 1 );
    }

    tty << "tunewidget::phaseVectorLoad() read " << data.size() << " elements" << "\n";

    ifs.close();
}

//-----------------------------------------------------------------------------

void tunewidget::phaseVectorSave(std::fstream &ofs, const std::vector<double> &data, bool asFlashBlock)
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    int channel_index = 0;

    for(unsigned i=0; i<sul->sul_total_abonents(); i++) {

        ofs << endl;
        ofs << "; MODULE " << i << " CHANNELS " << sul->sul_abonent_channels(i) << endl;
        ofs << endl;

        for(int j=0; j<sul->sul_abonent_channels(i); j++, channel_index++) {

            int val = 0;
            if(ui->rbViewCode->isChecked())
                val = sul->sul_convert_phase(data.at(channel_index));
            else
                val = (int)data.at(channel_index);

            if((j%16) == 0) {
                ofs << endl;
            }

            ofs << dec << setw(3) << val << " ";


        }
        if(asFlashBlock) {
            for(int j=sul->sul_abonent_channels(i); j<sul->sul_flash_block_size(); j++) {

                if((j%16) == 0) {
                    ofs << endl;
                }

                ofs << dec << setw(3) << 0 << " ";
            }
        }
        ofs << endl;
        ofs << endl;
    }

    return;
}

//-----------------------------------------------------------------------------

void tunewidget::phaseVectorSaveAsColumn(std::fstream &ofs, const std::vector<double> &data)
{
    if(!sul) {
        bar->showMessage(tr("Не выбрана система СУЛ"));
        return;
    }

    int channel_index = 0;

    for(unsigned i=0; i<sul->sul_total_abonents(); i++) {

        for(int j=0; j<sul->sul_abonent_channels(i); j++, channel_index++) {

            int val = 0;
            if(ui->rbViewCode->isChecked())
                val = sul->sul_convert_phase(data.at(channel_index));
            else
                val = (int)data.at(channel_index);

            ofs << dec << setw(3) << val << endl;

        }
    }

    return;
}

//-----------------------------------------------------------------------------

void tunewidget::AddPhaseLoad()
{
    phaseVectorLoad(fa_);

    disconnect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));
    set_table_data(ui->addPhase,fa_);
    connect(ui->addPhase,SIGNAL(cellChanged(int,int)),this,SLOT(addPhaseCellChanged(int,int)));

    if(ui->cbDrawSelector->currentIndex() == 3)
        array->repaint();
}

//-----------------------------------------------------------------------------

void tunewidget::AddPhaseSave()
{
    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл для сохранения конфигурации: ") + fileName);
    }

    // сохранить данные из таблицы в файл (напрямую)
    fstream  ofs;
    ofs.open( fileName.toStdString().c_str(), ios::out );

    if (!ofs.is_open()) {
        bar->showMessage(tr("Ошибка! Не могу открыть файл."));
        return;
    }

    ofs << endl;
    ofs << "[PHASE_ADD]" << endl;
    ofs << endl;

    phaseVectorSave(ofs, fa_);

    ofs.close();
}

//-----------------------------------------------------------------------------

void tunewidget::CalcPhaseSave()
{
    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл для сохранения конфигурации: ") + fileName);
    }

    // сохранить данные из таблицы в файл (напрямую)
    fstream  ofs;
    ofs.open( fileName.toStdString().c_str(), ios::out );

    if (!ofs.is_open()) {
        bar->showMessage(tr("Ошибка! Не могу открыть файл."));
        return;
    }

    ofs << endl;
    ofs << "[CALC_PHASE]" << endl;
    ofs << endl;

    phaseVectorSave(ofs, fk_);

    ofs.close();
}

//-----------------------------------------------------------------------------

void tunewidget::OwnPhaseLoad()
{
    phaseVectorLoad(fi0_);

    disconnect(ui->ownPhase,SIGNAL(cellChanged(int,int)),this,SLOT(ownPhaseCellChanged(int,int)));
    set_table_data(ui->ownPhase,fi0_);
    connect(ui->ownPhase,SIGNAL(cellChanged(int,int)),this,SLOT(ownPhaseCellChanged(int,int)));

    if(ui->cbDrawSelector->currentIndex() == 1)
        array->repaint();
}

//-----------------------------------------------------------------------------

void tunewidget::OwnPhaseSave()
{
    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл для сохранения конфигурации: ") + fileName);
    }

    // сохранить данные из таблицы в файл (напрямую)
    fstream  ofs;
    ofs.open( fileName.toStdString().c_str(), ios::out );

    if (!ofs.is_open()) {
        bar->showMessage(tr("Ошибка! Не могу открыть файл."));
        return;
    }

    ofs << endl;
    ofs << "[PHASE_OWN]" << endl;
    ofs << endl;

    phaseVectorSaveAsColumn(ofs, fi0_);

    ofs.close();
}

//-----------------------------------------------------------------------------

void tunewidget::FullPhaseSave()
{
    QString fileName = getFileName();
    if(fileName.isEmpty()) {
        bar->showMessage(tr("Не выбран файл для сохранения конфигурации"));
        return;
    } else {
        bar->showMessage(tr("Файл для сохранения конфигурации: ") + fileName);
    }

    // сохранить данные из таблицы в файл (напрямую)
    fstream  ofs;
    ofs.open( fileName.toStdString().c_str(), ios::out );

    if (!ofs.is_open()) {
        bar->showMessage(tr("Ошибка! Не могу открыть файл."));
        return;
    }

    ofs << endl;
    ofs << "[ F" << ui->spbFocus->value() << " - L" << ui->spbLambda->value() << " ]" << endl;
    ofs << endl;

    phaseVectorSave(ofs, phase_);

    ofs.close();
}

//-----------------------------------------------------------------------------

void tunewidget::FullPhaseLoad()
{
    phaseVectorLoad(phase_);
    array->repaint();
}

//-----------------------------------------------------------------------------

void tunewidget::FullPhaseToSul()
{
}

//-----------------------------------------------------------------------------

QString tunewidget::getFileName()
{
    QFileDialog *fileDialog = new QFileDialog();
    QString fileName = fileDialog->getSaveFileName(this, tr("Сохранить файл"),".",tr("config files (*.phase)"));
    delete fileDialog;
    return fileName;
}
