/****************************************************************************
** Meta object code from reading C++ file 'paintarea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../UI/include/paintarea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PaintArea_t {
    QByteArrayData data[13];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintArea_t qt_meta_stringdata_PaintArea = {
    {
QT_MOC_LITERAL(0, 0, 9), // "PaintArea"
QT_MOC_LITERAL(1, 10, 11), // "sigShowData"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 38), // "QList<pcl::PointCloud<Box_Clo..."
QT_MOC_LITERAL(4, 62, 12), // "setPaintSlot"
QT_MOC_LITERAL(5, 75, 14), // "QList<QPointF>"
QT_MOC_LITERAL(6, 90, 3), // "tmp"
QT_MOC_LITERAL(7, 94, 5), // "index"
QT_MOC_LITERAL(8, 100, 9), // "setSplice"
QT_MOC_LITERAL(9, 110, 11), // "updataPoint"
QT_MOC_LITERAL(10, 122, 23), // "QList<pcl::PointXYZRGB>"
QT_MOC_LITERAL(11, 146, 2), // "ps"
QT_MOC_LITERAL(12, 149, 16) // "UpdateArea_index"

    },
    "PaintArea\0sigShowData\0\0"
    "QList<pcl::PointCloud<Box_Cloud>::Ptr>\0"
    "setPaintSlot\0QList<QPointF>\0tmp\0index\0"
    "setSplice\0updataPoint\0QList<pcl::PointXYZRGB>\0"
    "ps\0UpdateArea_index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       1,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   48,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,
       9,    2,   56,    2, 0x0a /* Public */,
      12,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    7,   11,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void PaintArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PaintArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigShowData(); break;
        case 1: _t->sigShowData((*reinterpret_cast< QList<pcl::PointCloud<Box_Cloud>::Ptr>(*)>(_a[1]))); break;
        case 2: _t->setPaintSlot((*reinterpret_cast< QList<QPointF>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setSplice((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updataPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<pcl::PointXYZRGB>(*)>(_a[2]))); break;
        case 5: _t->UpdateArea_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QPointF> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PaintArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintArea::sigShowData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PaintArea::*)(QList<pcl::PointCloud<Box_Cloud>::Ptr> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintArea::sigShowData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PaintArea::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PaintArea.data,
    qt_meta_data_PaintArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PaintArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PaintArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PaintArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PaintArea::sigShowData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PaintArea::sigShowData(QList<pcl::PointCloud<Box_Cloud>::Ptr> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
