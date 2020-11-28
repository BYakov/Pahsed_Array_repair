
INCLUDEPATH += . \
    ./source \
    ../sul_src \
    ../base_class \


HEADERS += \
    source/worker_thread.h \
    source/sul_tune_widget.h \
    source/sul_test.h \
    source/sul_monitor.h \
    source/sul_graph.h \
    source/sul_array.h \
    source/sul_analizer.h \
    source/sul_adc.h \
    ../sul_src/sul_mdo.h \
    ../sul_src/serial.h \
    ../sul_src/scanner.h \
    ../sul_src/packet485.h \
    ../sul_src/angle_correct.h \
    ../sul_src/sul_mdo_cmd.h \
    ../base_class/sul_config.h \
    ../base_class/sul_base.h \
    ../base_class/ram_config.h \
    ../base_class/message.h \
    ../base_class/flash_config.h \
    ../base_class/fi0_config.h \
    ../base_class/device.h \
    ../base_class/process_type.h \
    ../sul_src/sul_bmk.h

SOURCES += \
    source/worker_thread.cpp \
    source/sul_tune_widget.cpp \
    source/sul_test.cpp \
    source/sul_monitor.cpp \
    source/sul_graph.cpp \
    source/sul_array.cpp \
    source/sul_analizer.cpp \
    source/sul_adc.cpp \
    source/main.cpp \
    ../sul_src/sul_mdo.cpp \
    ../sul_src/serial.cpp \
    ../sul_src/scanner.cpp \
    ../sul_src/packet485.cpp \
    ../sul_src/angle_correct.cpp \
    ../base_class/sul_config.cpp \
    ../base_class/sul_base.cpp \
    ../base_class/ram_config.cpp \
    ../base_class/message.cpp \
    ../base_class/flash_config.cpp \
    ../base_class/fi0_config.cpp \
    ../base_class/device.cpp \
    ../sul_src/sul_bmk.cpp
