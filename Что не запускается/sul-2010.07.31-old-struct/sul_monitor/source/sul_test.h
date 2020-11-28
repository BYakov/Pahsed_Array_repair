#ifndef SUL_TEST_H
#define SUL_TEST_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QStandardItemModel>

#include "sul_base.h"

class sul_test_widget : public QWidget
{
        Q_OBJECT

private:
        sul_base *sul;

        QLabel          *label;
        QSpinBox        *box;
        QRadioButton    *rbtTestSingle;
        QRadioButton    *rbtTestTotal;
        QRadioButton    *rbtViewFull;
        QRadioButton    *rbtViewPart;
        QPushButton     *btnChannelTest;
        QPushButton     *btnCalculatorTest;
	QPushButton     *btnPulseTest;
        QPushButton     *btnFi0Test;
        QStatusBar      *bar;

public:
        sul_test_widget(sul_base *s, QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual ~sul_test_widget();

signals:
        void abonent_changed(int);

        // отобразить в анализаторе каналов
        void show_analizer_channels();
        void show_analizer_calculators(bool fi0 = false);
	void show_analizer_pulses();

        // отобразить на решетке
        void show_grid_channels();
        void show_grid_calculators(bool fi0 = false);
	void show_grid_pulses();

        void show_fi0();

public slots:
        void test_channels();
        void test_calculators();
	void test_pulses();
        void test_fi0();

        void abonent_number_changed(int abonent);
};

#endif // SUL_TEST_H
