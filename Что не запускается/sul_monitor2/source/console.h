#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>
#include <QPlainTextEdit>

class console : public QObject
{
public:
    explicit console();
    virtual ~console();

    void addWidget(void *widget);
    void print(const QString str);
    void print(const std::string str);
    void print(const char *str);
    void clear();

    console& operator << (const char *str);
    console& operator << (const int val);
    console& operator << (const unsigned long val);
    console& operator << (const double val);
    console& operator << (const size_t val);
    console& operator << (const std::string str);

private:
    QPlainTextEdit *ttyWidget;

signals:

};

#endif // CONSOLE_H
