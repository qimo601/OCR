/****************************************************************************
** Meta object code from reading C++ file 'BllDataIdentity.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Bll/BllDataIdentity.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BllDataIdentity.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BllDataIdentity_t {
    QByteArrayData data[10];
    char stringdata[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BllDataIdentity_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BllDataIdentity_t qt_meta_stringdata_BllDataIdentity = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 9),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 10),
QT_MOC_LITERAL(4, 38, 6),
QT_MOC_LITERAL(5, 45, 9),
QT_MOC_LITERAL(6, 55, 12),
QT_MOC_LITERAL(7, 68, 4),
QT_MOC_LITERAL(8, 73, 5),
QT_MOC_LITERAL(9, 79, 4)
    },
    "BllDataIdentity\0readyRead\0\0DataOutput\0"
    "output\0byteArray\0readyReadBmp\0init\0"
    "start\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BllDataIdentity[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       6,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   49,    2, 0x0a /* Public */,
       8,    0,   50,    2, 0x0a /* Public */,
       9,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QByteArray,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QByteArray,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BllDataIdentity::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BllDataIdentity *_t = static_cast<BllDataIdentity *>(_o);
        switch (_id) {
        case 0: _t->readyRead((*reinterpret_cast< DataOutput(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 1: _t->readyReadBmp((*reinterpret_cast< DataOutput(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        case 2: _t->init(); break;
        case 3: _t->start(); break;
        case 4: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BllDataIdentity::*_t)(DataOutput , QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BllDataIdentity::readyRead)) {
                *result = 0;
            }
        }
        {
            typedef void (BllDataIdentity::*_t)(DataOutput , QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BllDataIdentity::readyReadBmp)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject BllDataIdentity::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BllDataIdentity.data,
      qt_meta_data_BllDataIdentity,  qt_static_metacall, 0, 0}
};


const QMetaObject *BllDataIdentity::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BllDataIdentity::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BllDataIdentity.stringdata))
        return static_cast<void*>(const_cast< BllDataIdentity*>(this));
    return QObject::qt_metacast(_clname);
}

int BllDataIdentity::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void BllDataIdentity::readyRead(DataOutput _t1, QByteArray _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BllDataIdentity::readyReadBmp(DataOutput _t1, QByteArray _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
