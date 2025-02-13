/****************************************************************************
** Meta object code from reading C++ file 'datastorage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FoodCalc/datastorage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datastorage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataStorage_t {
    QByteArrayData data[19];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataStorage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataStorage_t qt_meta_stringdata_DataStorage = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DataStorage"
QT_MOC_LITERAL(1, 12, 15), // "ingredientAdded"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 21), // "std::shared_ptr<Food>"
QT_MOC_LITERAL(4, 51, 16), // "ingredientEdited"
QT_MOC_LITERAL(5, 68, 17), // "oldIngredientName"
QT_MOC_LITERAL(6, 86, 8), // "newValue"
QT_MOC_LITERAL(7, 95, 17), // "ingredientRemoved"
QT_MOC_LITERAL(8, 113, 14), // "ingredientName"
QT_MOC_LITERAL(9, 128, 9), // "dishAdded"
QT_MOC_LITERAL(10, 138, 11), // "dishRemoved"
QT_MOC_LITERAL(11, 150, 8), // "dishName"
QT_MOC_LITERAL(12, 159, 12), // "dishesEdited"
QT_MOC_LITERAL(13, 172, 40), // "std::map<QString,std::shared_..."
QT_MOC_LITERAL(14, 213, 13), // "changedDishes"
QT_MOC_LITERAL(15, 227, 12), // "foodConsumed"
QT_MOC_LITERAL(16, 240, 12), // "ConsumedFood"
QT_MOC_LITERAL(17, 253, 19), // "consumedFoodRemoved"
QT_MOC_LITERAL(18, 273, 8) // "recordId"

    },
    "DataStorage\0ingredientAdded\0\0"
    "std::shared_ptr<Food>\0ingredientEdited\0"
    "oldIngredientName\0newValue\0ingredientRemoved\0"
    "ingredientName\0dishAdded\0dishRemoved\0"
    "dishName\0dishesEdited\0"
    "std::map<QString,std::shared_ptr<Food> >\0"
    "changedDishes\0foodConsumed\0ConsumedFood\0"
    "consumedFoodRemoved\0recordId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataStorage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    2,   57,    2, 0x06 /* Public */,
       7,    1,   62,    2, 0x06 /* Public */,
       9,    1,   65,    2, 0x06 /* Public */,
      10,    1,   68,    2, 0x06 /* Public */,
      12,    1,   71,    2, 0x06 /* Public */,
      15,    1,   74,    2, 0x06 /* Public */,
      17,    1,   77,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 3,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void DataStorage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataStorage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ingredientAdded((*reinterpret_cast< std::shared_ptr<Food>(*)>(_a[1]))); break;
        case 1: _t->ingredientEdited((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<Food>(*)>(_a[2]))); break;
        case 2: _t->ingredientRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->dishAdded((*reinterpret_cast< std::shared_ptr<Food>(*)>(_a[1]))); break;
        case 4: _t->dishRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->dishesEdited((*reinterpret_cast< std::map<QString,std::shared_ptr<Food> >(*)>(_a[1]))); break;
        case 6: _t->foodConsumed((*reinterpret_cast< ConsumedFood(*)>(_a[1]))); break;
        case 7: _t->consumedFoodRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataStorage::*)(std::shared_ptr<Food> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::ingredientAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(const QString & , std::shared_ptr<Food> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::ingredientEdited)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::ingredientRemoved)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(std::shared_ptr<Food> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::dishAdded)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::dishRemoved)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(std::map<QString,std::shared_ptr<Food>> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::dishesEdited)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(ConsumedFood );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::foodConsumed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DataStorage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataStorage::consumedFoodRemoved)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataStorage::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DataStorage.data,
    qt_meta_data_DataStorage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataStorage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataStorage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataStorage.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DataStorage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void DataStorage::ingredientAdded(std::shared_ptr<Food> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataStorage::ingredientEdited(const QString & _t1, std::shared_ptr<Food> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DataStorage::ingredientRemoved(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataStorage::dishAdded(std::shared_ptr<Food> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataStorage::dishRemoved(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DataStorage::dishesEdited(std::map<QString,std::shared_ptr<Food>> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DataStorage::foodConsumed(ConsumedFood _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DataStorage::consumedFoodRemoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
