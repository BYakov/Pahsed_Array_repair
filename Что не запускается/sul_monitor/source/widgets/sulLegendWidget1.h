#ifndef SUL_LEGEND_WIDGET1_H
#define SUL_LEGEND_WIDGET1_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGridLayout>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QGridLayout>
#endif
#include <QSettings>


#ifndef _SUL_BASE_H_
    #include "sul_base.h"
#endif
#ifndef _SUL_CHANNEL_DATA_H_
    #include "sul_channel_data.h"
#endif

class sul_legend_widget1 : public QWidget
{
        Q_OBJECT

private:
        sul_base            *sul;
        std::vector<QLabel*>      lp;
        std::vector<QLabel*>      lv;

public:
        sul_legend_widget1(sul_base *system, QWidget *parent = 0, Qt::WindowFlags flags = 0);
        virtual ~sul_legend_widget1();

public slots:
        void updateScreen(struct channel_info& data);
};

#endif // SUL_LEGEND_WIDGET1_H
