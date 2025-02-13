/****************************************************************************
** Meta object code from reading C++ file 'dailyConsumedFoodWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FoodCalc/DailyNutrition/dailyConsumedFoodWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dailyConsumedFoodWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DailyConsumedFoodWidget_t {
    QByteArrayData data[8];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DailyConsumedFoodWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DailyConsumedFoodWidget_t qt_meta_stringdata_DailyConsumedFoodWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "DailyConsumedFoodWidget"
QT_MOC_LITERAL(1, 24, 14), // "onFoodConsumed"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 25), // "DataStorage::ConsumedFood"
QT_MOC_LITERAL(4, 66, 4), // "food"
QT_MOC_LITERAL(5, 71, 29), // "onConsumedFoodRemoveRequested"
QT_MOC_LITERAL(6, 101, 8), // "recordId"
QT_MOC_LITERAL(7, 110, 27) // "onConsumedFoodRemovedFromDB"

    },
    "DailyConsumedFoodWidget\0onFoodConsumed\0"
    "\0DataStorage::ConsumedFood\0food\0"
    "onConsumedFoodRemoveRequested\0recordId\0"
    "onConsumedFoodRemovedFromDB"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DailyConsumedFoodWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    1,   32,    2, 0x0a /* Public */,
       7,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void DailyConsumedFoodWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DailyConsumedFoodWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onFoodConsumed((*reinterpret_cast< DataStorage::ConsumedFood(*)>(_a[1]))); break;
        case 1: _t->onConsumedFoodRemoveRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onConsumedFoodRemovedFromDB((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DailyConsumedFoodWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_DailyConsumedFoodWidget.data,
    qt_meta_data_DailyConsumedFoodWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DailyConsumedFoodWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DailyConsumedFoodWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DailyConsumedFoodWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DailyConsumedFoodWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
