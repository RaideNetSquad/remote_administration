/****************************************************************************
** Meta object code from reading C++ file 'serverObjectLogic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Server/ServerObjectLogic/serverObjectLogic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverObjectLogic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ServerObjectLogic_t {
    QByteArrayData data[21];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServerObjectLogic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServerObjectLogic_t qt_meta_stringdata_ServerObjectLogic = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ServerObjectLogic"
QT_MOC_LITERAL(1, 18, 10), // "newMessage"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "message"
QT_MOC_LITERAL(4, 38, 8), // "newError"
QT_MOC_LITERAL(5, 47, 13), // "deleteFromSet"
QT_MOC_LITERAL(6, 61, 4), // "desc"
QT_MOC_LITERAL(7, 66, 30), // "parserFileWithInstructionsRole"
QT_MOC_LITERAL(8, 97, 9), // "errorSend"
QT_MOC_LITERAL(9, 107, 20), // "disconnectWithClient"
QT_MOC_LITERAL(10, 128, 7), // "qintptr"
QT_MOC_LITERAL(11, 136, 13), // "addConnection"
QT_MOC_LITERAL(12, 150, 18), // "slot_addConnection"
QT_MOC_LITERAL(13, 169, 16), // "slot_TimerUpdate"
QT_MOC_LITERAL(14, 186, 21), // "slot_newMessageClient"
QT_MOC_LITERAL(15, 208, 13), // "slot_newError"
QT_MOC_LITERAL(16, 222, 14), // "slot_CheckRole"
QT_MOC_LITERAL(17, 237, 4), // "role"
QT_MOC_LITERAL(18, 242, 18), // "slot_deleteFromSet"
QT_MOC_LITERAL(19, 261, 4), // "sock"
QT_MOC_LITERAL(20, 266, 15) // "slot_StartTimer"

    },
    "ServerObjectLogic\0newMessage\0\0message\0"
    "newError\0deleteFromSet\0desc\0"
    "parserFileWithInstructionsRole\0errorSend\0"
    "disconnectWithClient\0qintptr\0addConnection\0"
    "slot_addConnection\0slot_TimerUpdate\0"
    "slot_newMessageClient\0slot_newError\0"
    "slot_CheckRole\0role\0slot_deleteFromSet\0"
    "sock\0slot_StartTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServerObjectLogic[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    1,   87,    2, 0x06 /* Public */,
       5,    1,   90,    2, 0x06 /* Public */,
       7,    4,   93,    2, 0x06 /* Public */,
       8,    1,  102,    2, 0x06 /* Public */,
       9,    2,  105,    2, 0x06 /* Public */,
      11,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  113,    2, 0x08 /* Private */,
      13,    0,  116,    2, 0x08 /* Private */,
      14,    1,  117,    2, 0x08 /* Private */,
      15,    1,  120,    2, 0x08 /* Private */,
      16,    2,  123,    2, 0x08 /* Private */,
      18,    1,  128,    2, 0x08 /* Private */,
      20,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   17,    6,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,

       0        // eod
};

void ServerObjectLogic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ServerObjectLogic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->newError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->deleteFromSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->parserFileWithInstructionsRole((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 4: _t->errorSend((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->disconnectWithClient((*reinterpret_cast< const qintptr(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->addConnection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_addConnection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_TimerUpdate(); break;
        case 9: _t->slot_newMessageClient((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->slot_newError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->slot_CheckRole((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 12: _t->slot_deleteFromSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->slot_StartTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ServerObjectLogic::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::newMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ServerObjectLogic::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::newError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ServerObjectLogic::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::deleteFromSet)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ServerObjectLogic::*)(const int & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::parserFileWithInstructionsRole)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ServerObjectLogic::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::errorSend)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ServerObjectLogic::*)(const qintptr & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::disconnectWithClient)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ServerObjectLogic::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ServerObjectLogic::addConnection)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ServerObjectLogic::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpServer::staticMetaObject>(),
    qt_meta_stringdata_ServerObjectLogic.data,
    qt_meta_data_ServerObjectLogic,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ServerObjectLogic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServerObjectLogic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ServerObjectLogic.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int ServerObjectLogic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ServerObjectLogic::newMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerObjectLogic::newError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerObjectLogic::deleteFromSet(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ServerObjectLogic::parserFileWithInstructionsRole(const int & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ServerObjectLogic::errorSend(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ServerObjectLogic::disconnectWithClient(const qintptr & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ServerObjectLogic::addConnection(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
