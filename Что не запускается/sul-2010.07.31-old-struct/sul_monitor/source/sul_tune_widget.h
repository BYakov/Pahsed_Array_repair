#ifndef SUL_TUNE_WIDGET_H
#define SUL_TUNE_WIDGET_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QGridLayout>

#include "sul_base.h"

class sul_tune_widget : public QWidget
{
        Q_OBJECT

private:
        int n_sectors;
        QStatusBar  *bar;
	QDoubleSpinBox spbR[8];
	QDoubleSpinBox spbX[8];
	QDoubleSpinBox spbY[8];
	QDoubleSpinBox spbL[8];
	QCheckBox      cb[8];
        QPushButton    *btnCreate;

public:
        sul_tune_widget(int N, QWidget *parent = 0, Qt::WFlags flags = 0);
        virtual ~sul_tune_widget();

        void create_config_file();

};

#endif // SUL_TEST_H
