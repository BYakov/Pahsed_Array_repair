#include <QtCore>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets/QApplication>
#else
#include <QApplication>
#endif
#include "sul_monitor.h"

int main(int argc, char *argv[])
{
    //std::streambuf* native_ = std::cout.rdbuf();
    //std::ofstream logfile("console.log");
    //logfile.copyfmt(std::cout);
    //std::cout.rdbuf(logfile.rdbuf());

    QApplication a(argc, argv);

    if(argc < 2) {
        QMessageBox::warning(NULL, QString::fromUtf8("Ошибка"), QString::fromUtf8("Не указан файл конфигурации СУЛ!"));
        exit(-1);
    }

    bool mode = false;
    if(argc == 3) {
        mode = atol(argv[2]);
    }

    sul_monitor *w = new sul_monitor(argv[1],NULL,0,mode);
    w->show();
    a.exec();

    delete w;

    //std::cout.flush();
    //std::cout.rdbuf(native_);

    return 0;
}
