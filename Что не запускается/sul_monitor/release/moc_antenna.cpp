/****************************************************************************
** Meta object code from reading C++ file 'antenna.h'
**
** Created: Sat 24. Jan 14:19:49 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/antenna.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'antenna.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_antenna[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    9,    8,    8, 0x05,
      42,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,    8,    8,    8, 0x0a,
      82,   72,    8,    8, 0x0a,
     118,    8,    8,    8, 0x0a,
     140,    8,    8,    8, 0x0a,
     162,  156,    8,    8, 0x0a,
     185,  180,    8,    8, 0x0a,
     205,    8,    8,    8, 0x0a,
     219,    8,    8,    8, 0x0a,
     232,    8,    8,    8, 0x0a,
     252,    8,  248,    8, 0x0a,
     271,    8,  248,    8, 0x0a,
     290,    8,  248,    8, 0x0a,
     307,    8,  248,    8, 0x0a,
     325,    8,  248,    8, 0x0a,
     338,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_antenna[] = {
    "antenna\0\0info\0selected_channel(channel_t)\0"
    "repaint_antenna()\0setup_sul()\0X,Y,event\0"
    "mouse_pressed(int,int,QMouseEvent*)\0"
    "update_channel_info()\0update_screen()\0"
    "index\0index_change(int)\0mode\0"
    "set_test_mode(bool)\0select_test()\0"
    "start_test()\0task_complete()\0int\0"
    "show_const_param()\0show_flash_param()\0"
    "show_ram_param()\0show_test_param()\0"
    "show_param()\0debug_slot()\0"
};

const QMetaObject antenna::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_antenna,
      qt_meta_data_antenna, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &antenna::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *antenna::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *antenna::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_antenna))
        return static_cast<void*>(const_cast< antenna*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int antenna::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selected_channel((*reinterpret_cast< channel_t(*)>(_a[1]))); break;
        case 1: repaint_antenna(); break;
        case 2: setup_sul(); break;
        case 3: mouse_pressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 4: update_channel_info(); break;
        case 5: update_screen(); break;
        case 6: index_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: set_test_mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: select_test(); break;
        case 9: start_test(); break;
        case 10: task_complete(); break;
        case 11: { int _r = show_const_param();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = show_flash_param();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: { int _r = show_ram_param();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 14: { int _r = show_test_param();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 15: { int _r = show_param();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: debug_slot(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void antenna::selected_channel(channel_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void antenna::repaint_antenna()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
