
TEMPLATE = app

QT = core gui widgets

FORMS += \
    forms/sul_monitor.ui \
    forms/antenna.ui

INCLUDEPATH += . \
    ./source \
    ./source/widgets \
    ../sul_common \
    ../sul_base


HEADERS += \
    source/sul_monitor.h \
    source/worker_thread.h \
    source/sul_graph.h \
    source/sul_analizer.h \
    source/antenna.h \
    source/widgets/sulTableView.h \
    source/task_thread.h \
    source/array_antenna.h \
    source/widgets/setChannelPhase.h \
    ../sul_common/scanner.h \
    ../sul_common/cross.h \
    ../sul_base/protocol_data_types.h \
    ../sul_base/sul_base.h \
    ../sul_base/device.h \
    ../sul_base/sul_protocol.h \
    ../sul_base/sul_channel_data.h \
    ../sul_base/vid_data.h

SOURCES += \
    source/sul_monitor.cpp \
    source/worker_thread.cpp \
    source/sul_graph.cpp \
    source/sul_analizer.cpp \
    source/antenna.cpp \
    source/main.cpp \
    source/widgets/sulTableView.cpp \
    source/task_thread.cpp \
    source/array_antenna.cpp \
    source/widgets/setChannelPhase.cpp \
    ../sul_common/scanner.cpp \
    ../sul_common/cross.cpp \
    ../sul_base/sul_base.cpp \
    ../sul_base/sul_protocol.cpp \
    ../sul_base/device.cpp

#LIBS += -ldl
