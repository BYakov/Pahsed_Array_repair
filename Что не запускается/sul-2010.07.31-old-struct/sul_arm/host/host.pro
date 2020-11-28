# -------------------------------------------------
# Project created by QtCreator 2010-05-04T09:01:19
# -------------------------------------------------
TARGET = host
TEMPLATE = app
SOURCES += main.cpp \
    widget.cpp \
    ../../base_class/message.cpp \
    ../../base_class/device.cpp \
    ../../sul_src/serial.cpp \
    exchange.cpp \
    sul_analizer.cpp
HEADERS += widget.h \
    ../../base_class/device.h \
    ../../base_class/message.h \
    ../../sul_src/serial.h \
    ../../sul_src/packet485.h \
    exchange.h \
    sul_analizer.h
FORMS += widget.ui
