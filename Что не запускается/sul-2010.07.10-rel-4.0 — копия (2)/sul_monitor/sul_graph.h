#ifndef SUL_GRAPH_H
#define SUL_GRAPH_H

#include <QtGui>
#include <QtGui/QWidget>
#include <QTableView>
#include <QStatusBar>
#include <QSettings>
#include <QStandardItemModel>

//-----------------------------------------------------------------------------

#include "..\sul_src\scanner.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class sul_graph : public QWidget
{
	Q_OBJECT

private:
	scanner	*scan;

	QLabel *X;
	QLabel *Y;

public:
	sul_graph(scanner *scan = NULL, QWidget *parent = 0, Qt::WFlags flags = 0);
	~sul_graph();

signals:
	void set_beam_position(int X, int Y);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);

public:
	void repaint();

};

#endif // SUL_MONITOR_H

