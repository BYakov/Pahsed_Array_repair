/****************************************************************************
** Meta object code from reading C++ file 'sulTableView.h'
**
** Created: Sat 24. Jan 14:19:50 2015
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../source/widgets/sulTableView.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sulTableView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SpinBoxDelegate[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      30,   17,   16,   16, 0x05,
      55,   51,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   74,   16,   16, 0x0a,
      98,   51,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SpinBoxDelegate[] = {
    "SpinBoxDelegate\0\0value,offset\0"
    "itemChanged(int,int)\0off\0editorCreated(int)\0"
    "value\0valueChanged(int)\0offsetChanged(int)\0"
};

const QMetaObject SpinBoxDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_SpinBoxDelegate,
      qt_meta_data_SpinBoxDelegate, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SpinBoxDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SpinBoxDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SpinBoxDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SpinBoxDelegate))
        return static_cast<void*>(const_cast< SpinBoxDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int SpinBoxDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: itemChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: editorCreated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: offsetChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SpinBoxDelegate::itemChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SpinBoxDelegate::editorCreated(int _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< SpinBoxDelegate *>(this), &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_SulTableView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x05,
      60,   47,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   47,   13,   13, 0x0a,
     119,  102,   13,   13, 0x0a,
     156,  102,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SulTableView[] = {
    "SulTableView\0\0current\0cellChanged(QModelIndex)\0"
    "value,offset\0cellChanged(int,int)\0"
    "itemChanged(int,int)\0current,previous\0"
    "dataChanged(QModelIndex,QModelIndex)\0"
    "currentChanged(QModelIndex,QModelIndex)\0"
};

const QMetaObject SulTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_SulTableView,
      qt_meta_data_SulTableView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SulTableView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SulTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SulTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SulTableView))
        return static_cast<void*>(const_cast< SulTableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int SulTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cellChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: itemChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: dataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 4: currentChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SulTableView::cellChanged(const QModelIndex & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SulTableView::cellChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
