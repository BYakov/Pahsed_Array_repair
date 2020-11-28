#include <QtGui/QApplication>
#include <QObject>
#include "mainwindow.h"

using namespace std;

//--------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //std::streambuf* native_ = std::cout.rdbuf();
    //std::ofstream logfile("console.log");
    //logfile.copyfmt(std::cout);
    //std::cout.rdbuf(logfile.rdbuf());

    MainWindow *w = 0;

    if(argc == 2) {
        w = new MainWindow(argv[1]);
    } else {
        w = new MainWindow();
    }

    w->show();
    a.exec();

    delete w;

    //std::cout.flush();
    //std::cout.rdbuf(native_);

    return 0;
}
