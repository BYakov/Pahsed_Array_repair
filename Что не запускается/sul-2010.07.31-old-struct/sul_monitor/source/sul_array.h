#ifndef SUL_ARRAY_H
#define SUL_ARRAY_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "sul_base.h"
#include "process_type.h"

class sul_array : public QWidget
{
    Q_OBJECT
public:
    sul_array(sul_base *Sul, QWidget *parent, Qt::WFlags flags);
    virtual ~sul_array();

private:
    sul_base                *sul;
    QStatusBar              *bar;
    processing_type	    type;
    bool                    fi0;
    u8                      *x;
    u8                      *y;
    float                   *R;
    float                   Rmax;
    float                   cS;
    u8                      maxX;
    u8                      maxY;
    int                     Radius;
    int                     abonent;
    struct phase_shifter    shifter;

    void paint_grid(QPaintEvent *event);
    void paint_grid_channels(QPaintEvent *event);
    void paint_grid_calculators(QPaintEvent *event);
    void paint_grid_phases(QPaintEvent *event);
    void paint_grid_pulses(QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:

        // абонент для которого идет обработка
        void set_abonent_number(int devn);

        // показывает аннтенную решетку
        void show_grid();

        // показывает состояние каналов аннтенной решетки
        void show_channels();

        // показывает расчитанные вычислителей с начальной фазой
        void show_calculators(bool Fi0);

	// показывает установленный импульс на фазовращатель
	void show_pulses();

        // показывает начальные фазы
        void show_fi0();
};

#endif // SUL_ARRAY_H
