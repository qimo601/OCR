/****************************************************************************
** Meta object code from reading C++ file 'TcpServer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Net/TcpServer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpServer_t {
    QByteArrayData data[22];
    char stringdata[373];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpServer_t qt_meta_stringdata_TcpServer = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 18),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 15),
QT_MOC_LITERAL(4, 46, 17),
QT_MOC_LITERAL(5, 64, 21),
QT_MOC_LITERAL(6, 86, 24),
QT_MOC_LITERAL(7, 111, 23),
QT_MOC_LITERAL(8, 135, 28),
QT_MOC_LITERAL(9, 164, 14),
QT_MOC_LITERAL(10, 179, 15),
QT_MOC_LITERAL(11, 195, 10),
QT_MOC_LITERAL(12, 206, 18),
QT_MOC_LITERAL(13, 225, 15),
QT_MOC_LITERAL(14, 241, 18),
QT_MOC_LITERAL(15, 260, 20),
QT_MOC_LITERAL(16, 281, 28),
QT_MOC_LITERAL(17, 310, 17),
QT_MOC_LITERAL(18, 328, 16),
QT_MOC_LITERAL(19, 345, 5),
QT_MOC_LITERAL(20, 351, 4),
QT_MOC_LITERAL(21, 356, 16)
    },
    "TcpServer\0startSuccessSignal\0\0"
    "startFailSignal\0stopSuccessSignal\0"
    "addServerSocketSignal\0removeServerSocketSignal\0"
    "serverSocketErrorSignal\0"
    "QAbstractSocket::SocketError\0"
    "haveScanSignal\0getServerSocket\0"
    "TcpSocket*\0replyClientMessage\0"
    "addServerSocket\0removeServerSocket\0"
    "getServerSocketState\0QAbstractSocket::SocketState\0"
    "serverSocketError\0getClientMessage\0"
    "start\0stop\0getAllConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,
       4,    0,  106,    2, 0x06 /* Public */,
       5,    1,  107,    2, 0x06 /* Public */,
       6,    1,  110,    2, 0x06 /* Public */,
       7,    1,  113,    2, 0x06 /* Public */,
       9,    2,  116,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  121,    2, 0x0a /* Public */,
      12,    2,  124,    2, 0x0a /* Public */,
      13,    1,  129,    2, 0x0a /* Public */,
      14,    1,  132,    2, 0x0a /* Public */,
      15,    1,  135,    2, 0x0a /* Public */,
      17,    1,  138,    2, 0x0a /* Public */,
      18,    2,  141,    2, 0x08 /* Private */,
      19,    1,  146,    2, 0x08 /* Private */,
      19,    0,  149,    2, 0x28 /* Private | MethodCloned */,
      20,    0,  150,    2, 0x08 /* Private */,
      21,    0,  151,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    2,    2,

 // slots: parameters
    0x80000000 | 11, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpServer *_t = static_cast<TcpServer *>(_o);
        switch (_id) {
        case 0: _t->startSuccessSignal(); break;
        case 1: _t->startFailSignal(); break;
        case 2: _t->stopSuccessSignal(); break;
        case 3: _t->addServerSocketSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->removeServerSocketSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->serverSocketErrorSignal((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->haveScanSignal((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: { TcpSocket* _r = _t->getServerSocket((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< TcpSocket**>(_a[0]) = _r; }  break;
        case 8: _t->replyClientMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->addServerSocket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->removeServerSocket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->getServerSocketState((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 12: _t->serverSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 13: _t->getClientMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->start((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->start(); break;
        case 16: _t->stop(); break;
        case 17: _t->getAllConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::startSuccessSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (TcpServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::startFailSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (TcpServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::stopSuccessSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (TcpServer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::addServerSocketSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (TcpServer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::removeServerSocketSignal)) {
                *result = 4;
            }
        }
        {
            typedef void (TcpServer::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::serverSocketErrorSignal)) {
                *result = 5;
            }
        }
        {
            typedef void (TcpServer::*_t)(QByteArray , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpServer::haveScanSignal)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject TcpServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_TcpServer.data,
      qt_meta_data_TcpServer,  qt_static_metacall, 0, 0}
};


const QMetaObject *TcpServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpServer.stringdata))
        return static_cast<void*>(const_cast< TcpServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int TcpServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void TcpServer::startSuccessSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TcpServer::startFailSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TcpServer::stopSuccessSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void TcpServer::addServerSocketSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TcpServer::removeServerSocketSignal(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TcpServer::serverSocketErrorSignal(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TcpServer::haveScanSignal(QByteArray _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
