#-------------------------------------------------
#
# Project created by QtCreator 2011-04-25T17:47:17
#
#-------------------------------------------------

QT       += core gui

TARGET = sul_monitor2
TEMPLATE = app
INCLUDEPATH += ../sul_base ../sul_common ../sul_monitor/source

SOURCES += \
    source/main.cpp \
    source/mainwindow.cpp \
    source/dbgwidget.cpp \
    source/eepromwidget.cpp \
    source/ramwidget.cpp \
    source/configwidget.cpp \
    source/beamwidget.cpp \
    source/tunewidget.cpp \
    source/console.cpp \
    source/legendwidget.cpp \
    source/position_graph.cpp \
    source/worker_thread.cpp \
    ../sul_common/scanner.cpp \
    ../sul_base/device.cpp \
    ../sul_base/sul_base.cpp \
    ../sul_base/space.cpp \
    ../sul_base/sul_protocol.cpp \
    ../sul_monitor/source/array_antenna.cpp

HEADERS  += \
    source/mainwindow.h \
    source/dbgwidget.h \
    source/eepromwidget.h \
    source/ramwidget.h \
    source/configwidget.h \
    source/beamwidget.h \
    source/tunewidget.h \
    source/console.h \
    source/legendwidget.h \
    source/position_graph.h \
    source/worker_thread.h \
    ../sul_common/scanner.h \
    ../sul_base/device.h \
    ../sul_base/sul_base.h \
    ../sul_base/space.h \
    ../sul_base/sul_protocol.h \
    ../sul_monitor/source/array_antenna.h

FORMS    += \
    forms/mainwindow.ui \
    forms/beamwidget.ui \
    forms/eepromwidget.ui \
    forms/ramwidget.ui \
    forms/configwidget.ui \
    forms/dbgwidget.ui \
    forms/tunewidget.ui
