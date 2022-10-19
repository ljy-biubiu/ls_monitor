/****************************************************************************
** Meta object code from reading C++ file 'setroi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../UI/include/setroi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setroi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetROI_t {
    QByteArrayData data[14];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetROI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetROI_t qt_meta_stringdata_SetROI = {
    {
QT_MOC_LITERAL(0, 0, 6), // "SetROI"
QT_MOC_LITERAL(1, 7, 14), // "sigalareapaint"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "sigaltablepaint"
QT_MOC_LITERAL(4, 39, 19), // "sigChangeArea_index"
QT_MOC_LITERAL(5, 59, 26), // "on_tableWidget_cellChanged"
QT_MOC_LITERAL(6, 86, 3), // "row"
QT_MOC_LITERAL(7, 90, 6), // "column"
QT_MOC_LITERAL(8, 97, 21), // "on_comboBox_activated"
QT_MOC_LITERAL(9, 119, 5), // "index"
QT_MOC_LITERAL(10, 125, 29), // "on_lineEdit_times_textChanged"
QT_MOC_LITERAL(11, 155, 4), // "arg1"
QT_MOC_LITERAL(12, 160, 39), // "on_lineEdit_Area_height_max_t..."
QT_MOC_LITERAL(13, 200, 39) // "on_lineEdit_Area_height_min_t..."

    },
    "SetROI\0sigalareapaint\0\0sigaltablepaint\0"
    "sigChangeArea_index\0on_tableWidget_cellChanged\0"
    "row\0column\0on_comboBox_activated\0index\0"
    "on_lineEdit_times_textChanged\0arg1\0"
    "on_lineEdit_Area_height_max_textChanged\0"
    "on_lineEdit_Area_height_min_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetROI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   59,    2, 0x08 /* Private */,
       8,    1,   64,    2, 0x08 /* Private */,
      10,    1,   67,    2, 0x08 /* Private */,
      12,    1,   70,    2, 0x08 /* Private */,
      13,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void SetROI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SetROI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigalareapaint(); break;
        case 1: _t->sigaltablepaint(); break;
        case 2: _t->sigChangeArea_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_tableWidget_cellChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_comboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_lineEdit_times_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_lineEdit_Area_height_max_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_lineEdit_Area_height_min_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SetROI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetROI::sigalareapaint)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SetROI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetROI::sigaltablepaint)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SetROI::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SetROI::sigChangeArea_index)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SetROI::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_SetROI.data,
    qt_meta_data_SetROI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SetROI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetROI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SetROI.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SetROI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SetROI::sigalareapaint()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SetROI::sigaltablepaint()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SetROI::sigChangeArea_index(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
