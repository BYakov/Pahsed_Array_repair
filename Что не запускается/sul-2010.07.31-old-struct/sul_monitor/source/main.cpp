#include <QtGui/QApplication>
#include "sul_monitor.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	sul_monitor w;
	w.show();
	return a.exec();
}
