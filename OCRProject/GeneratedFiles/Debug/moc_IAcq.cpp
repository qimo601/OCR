/****************************************************************************
** Meta object code from reading C++ file 'IAcq.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Acq/IAcq.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IAcq.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_IAcq_t {
    QByteArrayData data[6];
    char stringdata[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IAcq_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IAcq_t qt_meta_stringdata_IAcq = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 4),
QT_MOC_LITERAL(2, 10, 4),
QT_MOC_LITERAL(3, 15, 0),
QT_MOC_LITERAL(4, 16, 4),
QT_MOC_LITERAL(5, 21, 12)
    },
    "IAcq\0init\0LONG\0\0read\0unLoadDevice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IAcq[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    3, 0x0a /* Public */,
       4,    0,   30,    3, 0x0a /* Public */,
       5,    0,   31,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2,
    0x80000000 | 2,
    0x80000000 | 2,

       0        // eod
};

void IAcq::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IAcq *_t = static_cast<IAcq *>(_o);
        switch (_id) {
        case 0: { LONG _r = _t->init();
            if (_a[0]) *reinterpret_cast< LONG*>(_a[0]) = _r; }  break;
        case 1: { LONG _r = _t->read();
            if (_a[0]) *reinterpret_cast< LONG*>(_a[0]) = _r; }  break;
        case 2: { LONG _r = _t->unLoadDevice();
            if (_a[0]) *reinterpret_cast< LONG*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject IAcq::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IAcq.data,
      qt_meta_data_IAcq,  qt_static_metacall, 0, 0}
};


const QMetaObject *IAcq::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IAcq::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IAcq.stringdata))
        return static_cast<void*>(const_cast< IAcq*>(this));
    return QObject::qt_metacast(_clname);
}

int IAcq::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
