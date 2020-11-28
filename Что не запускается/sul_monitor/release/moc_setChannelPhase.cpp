/****************************************************************************
** Meta object code from reading C++ file 'setChannelPhase.h'
**
** Created: Sat 24. Jan 14:19:52 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/widgets/setChannelPhase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setChannelPhase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_set_channel_phase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   19,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_set_channel_phase[] = {
    "set_channel_phase\0\0code\0"
    "update_phase_image(unsigned char)\0"
    "setup_phase()\0"
};

const QMetaObject set_channel_phase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_set_channel_phase,
      qt_meta_data_set_channel_phase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &set_channel_phase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *set_channel_phase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *set_channel_phase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_set_channel_phase))
        return static_cast<void*>(const_cast< set_channel_phase*>(this));
    return QWidget::qt_metacast(_clname);
}

int set_channel_phase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update_phase_image((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 1: setup_phase(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void set_channel_phase::update_phase_image(unsigned char _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
