#ifndef SUL_ANALIZER_H
#define SUL_ANALIZER_H

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

#ifndef _SUL_BASE_H_
    #include "sul_base.h"
#endif
#ifndef _SUL_CHANNEL_DATA_H_
    #include "sul_channel_data.h"
#endif

//-----------------------------------------------------------------------------

class sul_channel_analizer : public QWidget
{
        Q_OBJECT

private:
        QStatusBar          *bar;
        int                 square_size;
        bool                fi0;
        //processing_type	    type;
        int		    X;
        int		    N;
        int		    abonent;
        sul_base	    *sul;
        const std::vector<double> *data_;

        void show_pulses();
        void show_channels();
        void show_calculators(bool Fi0);
        void show_fi0();

public:
        sul_channel_analizer(sul_base *sul, QWidget *parent = 0, Qt::WindowFlags flags = 0);
        ~sul_channel_analizer();

protected:
        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);

public slots:
        void set_abonent_number(int devn);
        void show_abonent_test();
        void show_abonent_test(int test_number);
        void paint_user_data(const std::vector<double> *data);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif // SUL_ANALIZER_H

