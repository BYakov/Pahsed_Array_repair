#ifndef SUL_GRAPH_H
#define SUL_GRAPH_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QLabel>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QLabel>
#endif
#include <QSettings>
#include <QStandardItemModel>

//-----------------------------------------------------------------------------

#ifndef _SCANNER_H_
    #include "scanner.h"
#endif

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
        sul_graph(scanner *scan = NULL, QWidget *parent = 0, Qt::WindowFlags flags = 0);
        ~sul_graph();

signals:
        void set_beam_position(double X, double Y);

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);

public:
        void repaint();

};

#endif // SUL_MONITOR_H

