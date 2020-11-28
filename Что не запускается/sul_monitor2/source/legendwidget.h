#ifndef LEGEND_WIDGET_H
#define LEGEND_WIDGET_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QGridLayout>

class legend_widget : public QWidget
{
        Q_OBJECT

private:
	std::vector<QLabel*>      paramName;
	std::vector<QLabel*>      paramValue;

public:
	legend_widget(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~legend_widget();

public slots:
	void updateParam(unsigned param_id, QString name, QString value);
};

#endif // SUL_LEGEND_WIDGET_H
