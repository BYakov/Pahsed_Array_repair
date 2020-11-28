#ifndef POSITION_GRAPH_H
#define POSITION_GRAPH_H

#include <QtGui>
#include <QWidget>
#include <QLabel>

//-----------------------------------------------------------------------------

#ifndef _SCANNER_H_
#include "scanner.h"
#endif

//-----------------------------------------------------------------------------

class position_graph : public QWidget
{
    Q_OBJECT

private:
    QLabel *X;
    QLabel *Y;
    scanner *scan;

public:
    explicit position_graph(scanner *s, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    position_graph(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~position_graph();

    void set_scanner(scanner *s);
    void set_position(double X, double Y);

    void repaint();

signals:
    void new_position(double X, double Y);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // POSITION_GRAPH_H
