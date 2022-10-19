/****************************************************************************
** Meta object code from reading C++ file 'ptz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MONITOR/include/ptz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ptz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PTZ_t {
    QByteArrayData data[22];
    char stringdata0[407];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PTZ_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PTZ_t qt_meta_stringdata_PTZ = {
    {
QT_MOC_LITERAL(0, 0, 3), // "PTZ"
QT_MOC_LITERAL(1, 4, 17), // "OnButtonUpChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 18), // "OffButtonUpChanged"
QT_MOC_LITERAL(4, 42, 19), // "OnButtonDownChanged"
QT_MOC_LITERAL(5, 62, 20), // "OffButtonDownChanged"
QT_MOC_LITERAL(6, 83, 19), // "OnButtonLeftChanged"
QT_MOC_LITERAL(7, 103, 20), // "OffButtonLeftChanged"
QT_MOC_LITERAL(8, 124, 20), // "OnButtonRightChanged"
QT_MOC_LITERAL(9, 145, 21), // "OffButtonRightChanged"
QT_MOC_LITERAL(10, 167, 17), // "OnButtonInChanged"
QT_MOC_LITERAL(11, 185, 18), // "OffButtonInChanged"
QT_MOC_LITERAL(12, 204, 18), // "OnButtonOutChanged"
QT_MOC_LITERAL(13, 223, 19), // "OffButtonOutChanged"
QT_MOC_LITERAL(14, 243, 19), // "OnButtonNearChanged"
QT_MOC_LITERAL(15, 263, 20), // "OffButtonNearChanged"
QT_MOC_LITERAL(16, 284, 18), // "OnButtonFarChanged"
QT_MOC_LITERAL(17, 303, 19), // "OffButtonFarChanged"
QT_MOC_LITERAL(18, 323, 19), // "OnButtonOpenChanged"
QT_MOC_LITERAL(19, 343, 20), // "OffButtonOpenChanged"
QT_MOC_LITERAL(20, 364, 20), // "OnButtonCloseChanged"
QT_MOC_LITERAL(21, 385, 21) // "OffButtonCloseChanged"

    },
    "PTZ\0OnButtonUpChanged\0\0OffButtonUpChanged\0"
    "OnButtonDownChanged\0OffButtonDownChanged\0"
    "OnButtonLeftChanged\0OffButtonLeftChanged\0"
    "OnButtonRightChanged\0OffButtonRightChanged\0"
    "OnButtonInChanged\0OffButtonInChanged\0"
    "OnButtonOutChanged\0OffButtonOutChanged\0"
    "OnButtonNearChanged\0OffButtonNearChanged\0"
    "OnButtonFarChanged\0OffButtonFarChanged\0"
    "OnButtonOpenChanged\0OffButtonOpenChanged\0"
    "OnButtonCloseChanged\0OffButtonCloseChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PTZ[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x0a /* Public */,
       3,    0,  115,    2, 0x0a /* Public */,
       4,    0,  116,    2, 0x0a /* Public */,
       5,    0,  117,    2, 0x0a /* Public */,
       6,    0,  118,    2, 0x0a /* Public */,
       7,    0,  119,    2, 0x0a /* Public */,
       8,    0,  120,    2, 0x0a /* Public */,
       9,    0,  121,    2, 0x0a /* Public */,
      10,    0,  122,    2, 0x0a /* Public */,
      11,    0,  123,    2, 0x0a /* Public */,
      12,    0,  124,    2, 0x0a /* Public */,
      13,    0,  125,    2, 0x0a /* Public */,
      14,    0,  126,    2, 0x0a /* Public */,
      15,    0,  127,    2, 0x0a /* Public */,
      16,    0,  128,    2, 0x0a /* Public */,
      17,    0,  129,    2, 0x0a /* Public */,
      18,    0,  130,    2, 0x0a /* Public */,
      19,    0,  131,    2, 0x0a /* Public */,
      20,    0,  132,    2, 0x0a /* Public */,
      21,    0,  133,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PTZ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PTZ *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnButtonUpChanged(); break;
        case 1: _t->OffButtonUpChanged(); break;
        case 2: _t->OnButtonDownChanged(); break;
        case 3: _t->OffButtonDownChanged(); break;
        case 4: _t->OnButtonLeftChanged(); break;
        case 5: _t->OffButtonLeftChanged(); break;
        case 6: _t->OnButtonRightChanged(); break;
        case 7: _t->OffButtonRightChanged(); break;
        case 8: _t->OnButtonInChanged(); break;
        case 9: _t->OffButtonInChanged(); break;
        case 10: _t->OnButtonOutChanged(); break;
        case 11: _t->OffButtonOutChanged(); break;
        case 12: _t->OnButtonNearChanged(); break;
        case 13: _t->OffButtonNearChanged(); break;
        case 14: _t->OnButtonFarChanged(); break;
        case 15: _t->OffButtonFarChanged(); break;
        case 16: _t->OnButtonOpenChanged(); break;
        case 17: _t->OffButtonOpenChanged(); break;
        case 18: _t->OnButtonCloseChanged(); break;
        case 19: _t->OffButtonCloseChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PTZ::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_PTZ.data,
    qt_meta_data_PTZ,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PTZ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PTZ::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PTZ.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int PTZ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
