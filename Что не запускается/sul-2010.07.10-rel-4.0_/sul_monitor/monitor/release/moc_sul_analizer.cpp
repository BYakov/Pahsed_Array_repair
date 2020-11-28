/****************************************************************************
** Meta object code from reading C++ file 'sul_analizer.h'
**
** Created: Sat 3. Jul 16:37:40 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../sul_analizer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sul_analizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_sul_channel_analizer[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      27,   22,   21,   21, 0x0a,
      51,   21,   21,   21, 0x0a,
      65,   21,   21,   21, 0x0a,
      85,   81,   21,   21, 0x0a,
     108,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_sul_channel_analizer[] = {
    "sul_channel_analizer\0\0devn\0"
    "set_abonent_number(int)\0show_pulses()\0"
    "show_channels()\0Fi0\0show_calculators(bool)\0"
    "show_fi0()\0"
};

const QMetaObject sul_channel_analizer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sul_channel_analizer,
      qt_meta_data_sul_channel_analizer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sul_channel_analizer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sul_channel_analizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sul_channel_analizer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sul_channel_analizer))
        return static_cast<void*>(const_cast< sul_channel_analizer*>(this));
    return QWidget::qt_metacast(_clname);
}

int sul_channel_analizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: set_abonent_number((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: show_pulses(); break;
        case 2: show_channels(); break;
        case 3: show_calculators((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: show_fi0(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
