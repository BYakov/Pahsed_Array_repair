/****************************************************************************
** Meta object code from reading C++ file 'sul_monitor.h'
**
** Created: Sat 24. Jul 10:07:10 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/sul_monitor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sul_monitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_sul_monitor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      29,   12,   12,   12, 0x0a,
      44,   12,   12,   12, 0x0a,
      59,   12,   12,   12, 0x0a,
      73,   12,   12,   12, 0x0a,
      86,   12,   12,   12, 0x0a,
      98,   12,   12,   12, 0x0a,
     113,   12,   12,   12, 0x0a,
     133,   12,   12,   12, 0x0a,
     147,   12,   12,   12, 0x0a,
     161,   12,   12,   12, 0x0a,
     182,  176,   12,   12, 0x0a,
     199,   12,   12,   12, 0x2a,
     213,   12,   12,   12, 0x0a,
     224,   12,   12,   12, 0x0a,
     237,   12,   12,   12, 0x0a,
     263,   12,   12,   12, 0x0a,
     281,   12,   12,   12, 0x0a,
     304,   12,   12,   12, 0x0a,
     318,   12,   12,   12, 0x0a,
     331,   12,   12,   12, 0x0a,
     345,   12,   12,   12, 0x0a,
     358,   12,   12,   12, 0x0a,
     372,   12,   12,   12, 0x0a,
     382,   12,   12,   12, 0x0a,
     398,   12,   12,   12, 0x0a,
     414,   12,   12,   12, 0x0a,
     425,   12,   12,   12, 0x0a,
     437,   12,   12,   12, 0x0a,
     448,   12,   12,   12, 0x0a,
     459,   12,   12,   12, 0x0a,
     480,   12,   12,   12, 0x0a,
     501,  494,   12,   12, 0x0a,
     524,   12,   12,   12, 0x0a,
     546,   12,   12,   12, 0x0a,
     571,  567,   12,   12, 0x0a,
     589,  567,   12,   12, 0x0a,
     617,   12,   12,   12, 0x0a,
     643,  639,   12,   12, 0x0a,
     673,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_sul_monitor[] = {
    "sul_monitor\0\0start_scanner()\0"
    "stop_scanner()\0step_scanner()\0"
    "set_scanner()\0setup_beam()\0dr_change()\0"
    "angle_change()\0sector_max_change()\0"
    "axis_change()\0timer_event()\0iface_change()\0"
    "index\0tool_change(int)\0tool_change()\0"
    "fill_ram()\0fill_flash()\0"
    "prepare_abonent_request()\0dbg_timer_event()\0"
    "send_abonent_request()\0zone_change()\0"
    "open_flash()\0erase_flash()\0load_flash()\0"
    "check_flash()\0set_ram()\0inc_ram_value()\0"
    "dec_ram_value()\0open_ram()\0erase_ram()\0"
    "load_ram()\0save_ram()\0show_beam_position()\0"
    "test_widget()\0status\0processing_status(int)\0"
    "display_timer_event()\0set_antenna_params()\0"
    "val\0set_dbgtimer(int)\0update_abonent_address(int)\0"
    "new_cfg_file_create()\0X,Y\0"
    "update_beam_position(int,int)\0"
    "restart_system()\0"
};

const QMetaObject sul_monitor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sul_monitor,
      qt_meta_data_sul_monitor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sul_monitor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sul_monitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sul_monitor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sul_monitor))
        return static_cast<void*>(const_cast< sul_monitor*>(this));
    return QWidget::qt_metacast(_clname);
}

int sul_monitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start_scanner(); break;
        case 1: stop_scanner(); break;
        case 2: step_scanner(); break;
        case 3: set_scanner(); break;
        case 4: setup_beam(); break;
        case 5: dr_change(); break;
        case 6: angle_change(); break;
        case 7: sector_max_change(); break;
        case 8: axis_change(); break;
        case 9: timer_event(); break;
        case 10: iface_change(); break;
        case 11: tool_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: tool_change(); break;
        case 13: fill_ram(); break;
        case 14: fill_flash(); break;
        case 15: prepare_abonent_request(); break;
        case 16: dbg_timer_event(); break;
        case 17: send_abonent_request(); break;
        case 18: zone_change(); break;
        case 19: open_flash(); break;
        case 20: erase_flash(); break;
        case 21: load_flash(); break;
        case 22: check_flash(); break;
        case 23: set_ram(); break;
        case 24: inc_ram_value(); break;
        case 25: dec_ram_value(); break;
        case 26: open_ram(); break;
        case 27: erase_ram(); break;
        case 28: load_ram(); break;
        case 29: save_ram(); break;
        case 30: show_beam_position(); break;
        case 31: test_widget(); break;
        case 32: processing_status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: display_timer_event(); break;
        case 34: set_antenna_params(); break;
        case 35: set_dbgtimer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: update_abonent_address((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: new_cfg_file_create(); break;
        case 38: update_beam_position((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 39: restart_system(); break;
        default: ;
        }
        _id -= 40;
    }
    return _id;
}
static const uint qt_meta_data_worker_thread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   15,   14,   14, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_worker_thread[] = {
    "worker_thread\0\0status\0task_status(int)\0"
};

const QMetaObject worker_thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_worker_thread,
      qt_meta_data_worker_thread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &worker_thread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *worker_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *worker_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_worker_thread))
        return static_cast<void*>(const_cast< worker_thread*>(this));
    return QThread::qt_metacast(_clname);
}

int worker_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: task_status((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void worker_thread::task_status(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
