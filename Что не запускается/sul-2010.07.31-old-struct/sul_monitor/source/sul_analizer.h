#ifndef SUL_ANALIZER_H
#define SUL_ANALIZER_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>

#include "sul_base.h"
#include "process_type.h"

//-----------------------------------------------------------------------------

class sul_channel_analizer : public QWidget
{
        Q_OBJECT

private:
        QStatusBar          *bar;
        int                 square_size;
        bool                fi0;
        processing_type	    type;
        int		    X;
        int		    N;
        int		    abonent;
        sul_base	    *sul;

public:
        sul_channel_analizer(sul_base *sul, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~sul_channel_analizer();

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);

public slots:
        void set_abonent_number(int devn);
	void show_pulses();
        void show_channels();
        void show_calculators(bool Fi0);
        void show_fi0();
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // SUL_ANALIZER_H

