#include "console.h"

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

using namespace std;

//------------------------------------------------------------------

console::console()
{
    ttyWidget = NULL;
}

//------------------------------------------------------------------

console::~console()
{
    if(ttyWidget)
        ttyWidget->close();
}

//------------------------------------------------------------------

void console::addWidget(void *widget)
{
    ttyWidget = (QPlainTextEdit *)widget;
}

//------------------------------------------------------------------

void console::print(const QString str)
{
    if(ttyWidget) {
        //ttyWidget->cursorForPosition(QPoint(0,0)).insertText(str);
        ttyWidget->textCursor().insertText(str);
    } else {
        std::cout << str.toAscii().data() << endl;
    }
}

//------------------------------------------------------------------

void console::print(const std::string str)
{
    if(ttyWidget) {
        //ttyWidget->cursorForPosition(QPoint(0,0)).insertText(QString(str.data()));
        ttyWidget->textCursor().insertText(QString(str.data()));
    } else {
        std::cout << str.data() << endl;
    }
}

//------------------------------------------------------------------

void console::print(const char *str)
{
    if(ttyWidget) {
        //ttyWidget->cursorForPosition(QPoint(0,0)).insertText(QString(str));
        ttyWidget->textCursor().insertText(QString(str));
    } else {
        std::cout << str << endl;
    }
}

//------------------------------------------------------------------

void console::clear()
{
    if(ttyWidget) ttyWidget->clear();
}

//------------------------------------------------------------------

console& console::operator << (const char *str)
{
    print(str);
    return *this;
}

//------------------------------------------------------------------

console& console::operator << (const int val)
{
    char buf[64] = {0};
    snprintf(buf,sizeof(buf),"%d",val);
    print(buf);
    return *this;
}

//------------------------------------------------------------------

console& console::operator << (const unsigned long val)
{
    char buf[64] = {0};
    snprintf(buf,sizeof(buf),"%ld",val);
    print(buf);
    return *this;
}

//------------------------------------------------------------------

console& console::operator << (const size_t val)
{
    char buf[64] = {0};
    snprintf(buf,sizeof(buf),"%d",val);
    print(buf);
    return *this;
}

//------------------------------------------------------------------

console& console::operator << (const double val)
{
    char buf[64] = {0};
    snprintf(buf,sizeof(buf),"%f",val);
    print(buf);
    return *this;
}

//------------------------------------------------------------------

console& console::operator << (const string str)
{
    print(str);
    return *this;
}
