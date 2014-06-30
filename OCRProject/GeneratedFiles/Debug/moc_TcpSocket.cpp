/****************************************************************************
** Meta object code from reading C++ file 'TcpSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Net/TcpSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpSocket_t {
    QByteArrayData data[21];
    char stringdata[336];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpSocket_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpSocket_t qt_meta_stringdata_TcpSocket = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 18),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 30),
QT_MOC_LITERAL(4, 61, 15),
QT_MOC_LITERAL(5, 77, 24),
QT_MOC_LITERAL(6, 102, 20),
QT_MOC_LITERAL(7, 123, 28),
QT_MOC_LITERAL(8, 152, 19),
QT_MOC_LITERAL(9, 172, 11),
QT_MOC_LITERAL(10, 184, 14),
QT_MOC_LITERAL(11, 199, 11),
QT_MOC_LITERAL(12, 211, 6),
QT_MOC_LITERAL(13, 218, 4),
QT_MOC_LITERAL(14, 223, 7),
QT_MOC_LITERAL(15, 231, 11),
QT_MOC_LITERAL(16, 243, 13),
QT_MOC_LITERAL(17, 257, 16),
QT_MOC_LITERAL(18, 274, 14),
QT_MOC_LITERAL(19, 289, 17),
QT_MOC_LITERAL(20, 307, 28)
    },
    "TcpSocket\0haveReadDataSignal\0\0"
    "disconnectedBeforeDeleteSignal\0"
    "connectedSignal\0connectedForServerSignal\0"
    "tcpSocketErrorSignal\0QAbstractSocket::SocketError\0"
    "connectToRemoteHost\0readMessage\0"
    "readAllMessage\0QByteArray&\0result\0"
    "int&\0descrip\0sendMessage\0connectedSlot\0"
    "disconnectedSlot\0TcpSocketError\0"
    "getTcpSocketState\0QAbstractSocket::SocketState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   84,    2, 0x06 /* Public */,
       3,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,
       5,    1,   95,    2, 0x06 /* Public */,
       6,    1,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,  101,    2, 0x0a /* Public */,
       9,    0,  106,    2, 0x0a /* Public */,
      10,    0,  107,    2, 0x0a /* Public */,
      10,    2,  108,    2, 0x0a /* Public */,
      15,    1,  113,    2, 0x0a /* Public */,
      16,    0,  116,    2, 0x0a /* Public */,
      17,    0,  117,    2, 0x0a /* Public */,
      18,    1,  118,    2, 0x0a /* Public */,
      19,    1,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,
    QMetaType::LongLong, 0x80000000 | 11,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 20,    2,

       0        // eod
};

void TcpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpSocket *_t = static_cast<TcpSocket *>(_o);
        switch (_id) {
        case 0: _t->haveReadDataSignal((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->disconnectedBeforeDeleteSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->connectedSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->connectedForServerSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->tcpSocketErrorSignal((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->connectToRemoteHost((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2]))); break;
        case 6: _t->readMessage(); break;
        case 7: _t->readAllMessage(); break;
        case 8: _t->readAllMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: { qint64 _r = _t->sendMessage((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 10: _t->connectedSlot(); break;
        case 11: _t->disconnectedSlot(); break;
        case 12: _t->TcpSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->getTcpSocketState((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpSocket::*_t)(QByteArray , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocket::haveReadDataSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpSocket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocket::disconnectedBeforeDeleteSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (TcpSocket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocket::connectedSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (TcpSocket::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocket::connectedForServerSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (TcpSocket::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpSocket::tcpSocketErrorSignal)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject TcpSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_TcpSocket.data,
      qt_meta_data_TcpSocket,  qt_static_metacall, 0, 0}
};


const QMetaObject *TcpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpSocket.stringdata))
        return static_cast<void*>(const_cast< TcpSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int TcpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TcpSocket::haveReadDataSignal(QByteArray _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpSocket::disconnectedBeforeDeleteSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpSocket::connectedSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpSocket::connectedForServerSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpSocket::tcpSocketErrorSignal(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
