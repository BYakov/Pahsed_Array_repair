#ifndef SUL_ANALIZER_H
#define SUL_ANALIZER_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>

//-----------------------------------------------------------------------------

class data_plot : public QWidget
{
        Q_OBJECT

private:
        QStatusBar          *bar;
        int                 square_size;
        int		    X;
        int		    N;
        unsigned short      *buffer;

public:
        data_plot(unsigned short *data, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~data_plot();

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);

public slots:
        void show_data();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // SUL_ANALIZER_H

