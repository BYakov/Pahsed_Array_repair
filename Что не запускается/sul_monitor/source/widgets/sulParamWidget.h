#ifndef _SULPARAMWIDGET_H
#define _SULPARAMWIDGET_H

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
#include <QStandardItemModel>

#ifndef _SUL_BASE_H_
    #include "sul_base.h"
#endif
#ifndef _SUL_CHANNEL_DATA_H_
    #include "sul_channel_data.h"
#endif

class sul_param_widget : public QWidget
{
        Q_OBJECT

private:
        sul_base *sul;

        std::vector<QRadioButton*> channelParam;
        std::vector<QRadioButton*> spaceParam;
        QStatusBar      *bar;

public:
        sul_param_widget(sul_base *s, QWidget *parent = 0, Qt::WindowFlags flags = 0);
        virtual ~sul_param_widget();

signals:
        // отобразить данные на полотне ФАР
        void show_array_parameter( int param_number );

        // отобразить данные конфигурации на полотне ФАР
        void show_space_parameter( int space_param_number );

public slots:
        void show_parameter();
        void space_parameter();
};

#endif // _SULPARAMWIDGET_H

