/****************************************************************************
** Meta object code from reading C++ file 'array_antenna.h'
**
** Created: Sat 24. Jan 14:19:51 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/array_antenna.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'array_antenna.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_array_antenna[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   60,   14,   14, 0x0a,
      96,   91,   14,   14, 0x0a,
     138,  129,   14,   14, 0x0a,
     179,  174,   14,   14, 0x0a,
     212,  208,  201,   14, 0x0a,
     231,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_array_antenna[] = {
    "array_antenna\0\0X,Y,event\0"
    "mousePressed(int,int,QMouseEvent*)\0"
    "newSize\0elementSizeChange(int)\0info\0"
    "selectedChannelChange(channel_t)\0"
    "newParam\0setParameters(std::vector<double>*)\0"
    "flag\0setShowTextFlag(bool)\0QColor\0X,Y\0"
    "xyToColor(int,int)\0repaintWidget()\0"
};

const QMetaObject array_antenna::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_array_antenna,
      qt_meta_data_array_antenna, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &array_antenna::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *array_antenna::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *array_antenna::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_array_antenna))
        return static_cast<void*>(const_cast< array_antenna*>(this));
    return QWidget::qt_metacast(_clname);
}

int array_antenna::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: mousePressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 1: elementSizeChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: selectedChannelChange((*reinterpret_cast< channel_t(*)>(_a[1]))); break;
        case 3: setParameters((*reinterpret_cast< std::vector<double>*(*)>(_a[1]))); break;
        case 4: setShowTextFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: { QColor _r = xyToColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 6: repaintWidget(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void array_antenna::mousePressed(int _t1, int _t2, QMouseEvent * _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
