/****************************************************************************
** Meta object code from reading C++ file 'sul_analizer.h'
**
** Created: Sat 24. Jul 18:46:41 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sul_analizer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sul_analizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_data_plot[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_data_plot[] = {
    "data_plot\0\0show_data()\0"
};

const QMetaObject data_plot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_data_plot,
      qt_meta_data_data_plot, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &data_plot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *data_plot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *data_plot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_data_plot))
        return static_cast<void*>(const_cast< data_plot*>(this));
    return QWidget::qt_metacast(_clname);
}

int data_plot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: show_data(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
