#ifndef TUNEWIDGET_H
#define TUNEWIDGET_H

#include "sul_base.h"
#include "console.h"
#include "array_antenna.h"
#include <QMainWindow>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidget>
#include <QFileDialog>

namespace Ui {
    class tunewidget;
}

class tunewidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit tunewidget(console& log, sul_base *sul_system, QWidget *parent = 0);
    ~tunewidget();

private:
    Ui::tunewidget *ui;
    console& tty;

    sul_base            *sul;
    std::vector<double> R_;         //!< Вектор радиусов от центра антенны к элементу
    std::vector<double> Rxy_;       //!< Вектор радиусов от центра антенны к элементу
    std::vector<double> fi0_;       //!< Вектор начальных фаз элементов
    std::vector<double> x_;         //!< Вектор номеров элементов вдоль X
    std::vector<double> y_;         //!< Вектор номеров элементов вдоль Y
    std::vector<double> s_;         //!< Вектор крутизны элементов
    std::vector<double> fk_;        //!< Вектор рассчитанных значений коррекции
    std::vector<double> fa_;        //!< Вектор фазовых подставок
    std::vector<double> phase_;     //!< Вектор результирующих фаз

    double Xmax_;
    double Ymax_;
    double Xmin_;
    double Ymin_;
    double Rmin_;
    double Rmax_;
    double x0_;
    double y0_;

    std::vector<struct channel_t> channels_list;

    array_antenna *array;               //!< Модуль для отрисовки фазового состояния

    QStatusBar *bar;

    int set_table_view(QTableWidget *table);
    int set_table_data(QTableWidget *table, const std::vector<double>& data);
    int get_table_data(QTableWidget *table, std::vector<double>& data);
    int save_table_data(QTableWidget *table);

    int calculate_sphere(double R, double L);
    int calculate_phase();
    int calculate_radius();

    double to_code(double degrees);
    double to_degrees(double code);

    void phaseVectorSave(std::fstream& ofs, const std::vector<double>& data, bool asFlashBlock = true );
    void phaseVectorLoad(std::vector<double>& data);
    void phaseVectorSaveAsColumn(std::fstream &ofs, const std::vector<double> &data);

private slots:
    void OwnPhaseLoad();
    void OwnPhaseSave();
    void ownPhaseCellChanged(int row, int column);
    void FullPhaseSave();
    void FullPhaseLoad();
    void FullPhaseToSul();
    void AddPhaseSave();
    void AddPhaseLoad();
    void CalcPhaseSave();
    void addPhaseCalculate();
    void addPhaseCellChanged(int row, int column);
    void addPhaseItemChanged(QTableWidgetItem* item);
    void ViewDegrees(bool checked);
    void ViewCode(bool checked);
    void CalculatePhase();
    void DrawSelectorChanged(int index);
    void ModuleNumberChanged(int index);
    QString getFileName();
};

#endif // TUNEWIDGET_H
