#ifndef SUL_ARRAY_H
#define SUL_ARRAY_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#endif
#include <QSettings>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

//using namespace std;

#ifndef _SUL_BASE_H_
#include "sul_base.h"
#endif
#ifndef _SUL_CHANNEL_DATA_H_
#include "sul_channel_data.h"
#endif
#ifndef SUL_LEGEND_WIDGET1_H
#include "sulLegendWidget1.h"
#endif
#ifndef SUL_LEGEND_WIDGET2_H
#include "sulLegendWidget2.h"
#endif

class sul_array : public QWidget
{
    Q_OBJECT
public:
    sul_array(sul_base *Sul, QWidget *parent, Qt::WindowFlags flags);
    virtual ~sul_array();

private:
    sul_base                *sul;
    sul_legend_widget1      *legend1;
    sul_legend_widget2      *legend2;
    bool                    fi0;
    unsigned short          *x;
    unsigned short          *y;
    float                   *R;
    float                   Rmax;
    float                   cS;
    float                   maxX;
    float                   maxY;
    float                   minX;
    float                   minY;
    float                   scaleScreenX;
    float                   scaleScreenY;
    int                     elementSize;
    int                     selectedChannel;
    int                     abonent;
    struct channel_t        channel;
    int                     viewParameter;
    int                     viewSpaceParameter;
    int                     numberOfPhases;
    int                     numberOfGains;
    int                     numberOfExtras;
    //struct parameter_t*     m_param;

    void paint_grid(QPaintEvent *event);
    void paint_space_param(QPaintEvent *event);
    void paint_paramter(QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:

    // абонент для которого идет обработка
    void set_abonent_number(int devn);

    // показывает состояние параметра антенной решетки
    void show_phase_array(int param_number);

    // показывает антенную решетку
    void show_phase_array();

    // показывает антенную решетку с параметрами конфигурации
    void show_space_array(int spaceParameter);

    // устанавливает размер элемента
    void setArrayElementSize(int size);
};

#endif // SUL_ARRAY_H
