/****************************************************************************
** Meta object code from reading C++ file 'maintitlebar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../UI/include/maintitlebar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maintitlebar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainTitleBar_t {
    QByteArrayData data[7];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainTitleBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainTitleBar_t qt_meta_stringdata_MainTitleBar = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MainTitleBar"
QT_MOC_LITERAL(1, 13, 17), // "sig_about_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 26), // "on_pushButtonClose_clicked"
QT_MOC_LITERAL(4, 59, 24), // "on_pushButtonMin_clicked"
QT_MOC_LITERAL(5, 84, 30), // "on_pushButtonNormalMax_clicked"
QT_MOC_LITERAL(6, 115, 26) // "on_pushButtonAbout_clicked"

    },
    "MainTitleBar\0sig_about_clicked\0\0"
    "on_pushButtonClose_clicked\0"
    "on_pushButtonMin_clicked\0"
    "on_pushButtonNormalMax_clicked\0"
    "on_pushButtonAbout_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainTitleBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainTitleBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainTitleBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_about_clicked(); break;
        case 1: _t->on_pushButtonClose_clicked(); break;
        case 2: _t->on_pushButtonMin_clicked(); break;
        case 3: _t->on_pushButtonNormalMax_clicked(); break;
        case 4: _t->on_pushButtonAbout_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainTitleBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainTitleBar::sig_about_clicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MainTitleBar::staticMetaObject = { {
    QMetaObject::SuperData::link<TitleBar::staticMetaObject>(),
    qt_meta_stringdata_MainTitleBar.data,
    qt_meta_data_MainTitleBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainTitleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainTitleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainTitleBar.stringdata0))
        return static_cast<void*>(this);
    return TitleBar::qt_metacast(_clname);
}

int MainTitleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TitleBar::qt_metacall(_c, _id, _a);
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
void MainTitleBar::sig_about_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
