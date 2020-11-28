#ifndef _SULTESTWIDGET_H
#define _SULTESTWIDGET_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QTableView>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QLabel>
#else
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QGridLayout>
#include <QSpinBox>
#include <QRadioButton>
#include <QLabel>
#endif
#include <QSettings>
#include <QStandardItemModel>

#include "sul_base.h"

class sul_test_widget : public QWidget
{
        Q_OBJECT

private:
        sul_base *sul;

        QLabel          *labelAddr;
        QSpinBox        *box;
        QRadioButton    *rbtTestSingle;
        QRadioButton    *rbtTestTotal;
        QRadioButton    *rbtViewFull;
        QRadioButton    *rbtViewPart;

        std::vector<QRadioButton*> rbSelectedTest;
        QPushButton     *pbStartTest;

        QStatusBar      *bar;

public:
        sul_test_widget(sul_base *s, QWidget *parent = 0, Qt::WindowFlags flags = 0);
        virtual ~sul_test_widget();

signals:
        void abonent_changed(int);

        // отобразить данные одного модуля
        void abonent_test_complete( int test_number );

        // отобразить данн6ые на полотне ФАР
        void array_test_complete( int test_number );

public slots:
        void start_test();
        void abonent_number_changed(int abnent_index);
};

#endif // _SULTESTWIDGET_H

