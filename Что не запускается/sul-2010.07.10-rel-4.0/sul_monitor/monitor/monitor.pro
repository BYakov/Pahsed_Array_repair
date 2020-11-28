HEADERS += ../sul_monitor.h \
    ../../sul_src/sul_mdo_cmd.h \
    ../../sul_src/sul_mdo.h \
    ../../sul_src/serial.h \
    ../../sul_src/scanner.h \
    ../../sul_src/packet485.h \
    ../../sul_src/coordinate.h \
    ../../sul_src/angle_correct.h \
    ../../base_class/sul_config.h \
    ../../base_class/sul_base.h \
    ../../base_class/message.h \
    ../../base_class/device.h \
    ../worker_thread.h \
    ../sul_analizer.h \
    ../sul_graph.h \
    ../sul_test.h \
    ../grid_array.h \
    ../../base_class/flash_config.h \
    ../../base_class/ram_config.h \
    ../../sul_src/sul_tune.h \
    ../sul_tune_widget.h \
    ../../base_class/process_type.h \
    ../../base_class/fi0_config.h
SOURCES += ../sul_monitor.cpp \
    ../../sul_src/sul_mdo.cpp \
    ../../sul_src/serial.cpp \
    ../../sul_src/scanner.cpp \
    ../../sul_src/packet485.cpp \
    ../../sul_src/coordinate.cpp \
    ../../sul_src/angle_correct.cpp \
    ../../base_class/sul_config.cpp \
    ../../base_class/sul_base.cpp \
    ../../base_class/message.cpp \
    ../../base_class/device.cpp \
    ../main.cpp \
    ../sul_graph.cpp \
    ../sul_analizer.cpp \
    ../worker_thread.cpp \
    ../sul_test.cpp \
    ../grid_array.cpp \
    ../../base_class/ram_config.cpp \
    ../../base_class/flash_config.cpp \
    ../../sul_src/sul_tune.cpp \
    ../sul_tune_widget.cpp \
    ../../base_class/fi0_config.cpp
FORMS += ../sul_monitor.ui
OTHER_FILES += 
RESOURCES += monitor.qrc
