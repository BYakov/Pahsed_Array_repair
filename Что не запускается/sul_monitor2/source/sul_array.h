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

#ifndef SUL_CHANNEL_DATA_H
#include "sul_channel_data.h"
#endif
#ifndef _SUL_BASE_
#include "sul_base.h"
#endif
#ifndef CONSOLE_H
#include "console.h"
#endif
#ifndef LEGEND_WIDGET_H
#include "legendwidget.h"
#endif

class sul_array : public QWidget
{
    Q_OBJECT
public:
    sul_array(console& log,
              sul_base *sul_system,
              QWidget *parent = NULL,
              Qt::WindowFlags flags = 0);
    virtual ~sul_array();

private:
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
    int                     colorStep;
    console&                tty;
    sul_base                     *sul;
    std::vector<double>          X;
    std::vector<double>          Y;
    std::vector<double>          R;
    const std::vector<double>    *userData_;
    legend_widget		 *legend;

    void paint_grid(QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:

    //! устанавливает размер элемента
    void setArrayElementSize(int size);

    //! устанавливает шаг палитры
    void setColorStep(int step);

    //! устанавливает данные для отображения
    void setUserData(const std::vector<double> *data);
};

#endif // SUL_ARRAY_H
