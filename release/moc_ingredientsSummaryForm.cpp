/****************************************************************************
** Meta object code from reading C++ file 'ingredientsSummaryForm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FoodCalc/ingredientsSummaryForm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ingredientsSummaryForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IngredientsSummaryForm_t {
    QByteArrayData data[8];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IngredientsSummaryForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IngredientsSummaryForm_t qt_meta_stringdata_IngredientsSummaryForm = {
    {
QT_MOC_LITERAL(0, 0, 22), // "IngredientsSummaryForm"
QT_MOC_LITERAL(1, 23, 28), // "onAddIngredientButtonClicked"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 27), // "onIngredientListItemClicked"
QT_MOC_LITERAL(4, 81, 21), // "std::shared_ptr<Food>"
QT_MOC_LITERAL(5, 103, 24), // "onIngredientInfoCommited"
QT_MOC_LITERAL(6, 128, 13), // "fixupPFCInput"
QT_MOC_LITERAL(7, 142, 26) // "onDeleteIngredientCommited"

    },
    "IngredientsSummaryForm\0"
    "onAddIngredientButtonClicked\0\0"
    "onIngredientListItemClicked\0"
    "std::shared_ptr<Food>\0onIngredientInfoCommited\0"
    "fixupPFCInput\0onDeleteIngredientCommited"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IngredientsSummaryForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IngredientsSummaryForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IngredientsSummaryForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onAddIngredientButtonClicked(); break;
        case 1: _t->onIngredientListItemClicked((*reinterpret_cast< const std::shared_ptr<Food>(*)>(_a[1]))); break;
        case 2: _t->onIngredientInfoCommited(); break;
        case 3: _t->fixupPFCInput(); break;
        case 4: _t->onDeleteIngredientCommited(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IngredientsSummaryForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_IngredientsSummaryForm.data,
    qt_meta_data_IngredientsSummaryForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IngredientsSummaryForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IngredientsSummaryForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IngredientsSummaryForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int IngredientsSummaryForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
