/****************************************************************************
** Meta object code from reading C++ file 'sul_test.h'
**
** Created: Sat 24. Jul 09:48:49 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/sul_test.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sul_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_sul_test_widget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      38,   16,   16,   16, 0x05,
      67,   63,   16,   16, 0x05,
      99,   16,   16,   16, 0x25,
     127,   16,   16,   16, 0x05,
     150,   16,   16,   16, 0x05,
     171,   63,   16,   16, 0x05,
     199,   16,   16,   16, 0x25,
     223,   16,   16,   16, 0x05,
     242,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     253,   16,   16,   16, 0x0a,
     269,   16,   16,   16, 0x0a,
     288,   16,   16,   16, 0x0a,
     302,   16,   16,   16, 0x0a,
     321,  313,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_sul_test_widget[] = {
    "sul_test_widget\0\0abonent_changed(int)\0"
    "show_analizer_channels()\0fi0\0"
    "show_analizer_calculators(bool)\0"
    "show_analizer_calculators()\0"
    "show_analizer_pulses()\0show_grid_channels()\0"
    "show_grid_calculators(bool)\0"
    "show_grid_calculators()\0show_grid_pulses()\0"
    "show_fi0()\0test_channels()\0"
    "test_calculators()\0test_pulses()\0"
    "test_fi0()\0abonent\0abonent_number_changed(int)\0"
};

const QMetaObject sul_test_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sul_test_widget,
      qt_meta_data_sul_test_widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sul_test_widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sul_test_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sul_test_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sul_test_widget))
        return static_cast<void*>(const_cast< sul_test_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int sul_test_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: abonent_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: show_analizer_channels(); break;
        case 2: show_analizer_calculators((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: show_analizer_calculators(); break;
        case 4: show_analizer_pulses(); break;
        case 5: show_grid_channels(); break;
        case 6: show_grid_calculators((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: show_grid_calculators(); break;
        case 8: show_grid_pulses(); break;
        case 9: show_fi0(); break;
        case 10: test_channels(); break;
        case 11: test_calculators(); break;
        case 12: test_pulses(); break;
        case 13: test_fi0(); break;
        case 14: abonent_number_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void sul_test_widget::abonent_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sul_test_widget::show_analizer_channels()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void sul_test_widget::show_analizer_calculators(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void sul_test_widget::show_analizer_pulses()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void sul_test_widget::show_grid_channels()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void sul_test_widget::show_grid_calculators(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 8
void sul_test_widget::show_grid_pulses()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void sul_test_widget::show_fi0()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
