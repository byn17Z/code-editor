/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSWidgetENDCLASS = QtMocHelpers::stringData(
    "Widget",
    "newSlot",
    "",
    "openSlot",
    "saveSlot",
    "saveAsSlot",
    "closeSlot",
    "updateDebuggerInfo",
    "debugSlot",
    "dNextSlot",
    "dPreSlot",
    "dJumpSlot",
    "dTmnSlot"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x0a,    1 /* Public */,
       3,    0,   81,    2, 0x0a,    2 /* Public */,
       4,    0,   82,    2, 0x0a,    3 /* Public */,
       5,    0,   83,    2, 0x0a,    4 /* Public */,
       6,    0,   84,    2, 0x0a,    5 /* Public */,
       7,    0,   85,    2, 0x0a,    6 /* Public */,
       8,    0,   86,    2, 0x0a,    7 /* Public */,
       9,    0,   87,    2, 0x0a,    8 /* Public */,
      10,    0,   88,    2, 0x0a,    9 /* Public */,
      11,    0,   89,    2, 0x0a,   10 /* Public */,
      12,    0,   90,    2, 0x0a,   11 /* Public */,

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

       0        // eod
};

Q_CONSTINIT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Widget, std::true_type>,
        // method 'newSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveAsSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateDebuggerInfo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'debugSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dNextSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dPreSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dJumpSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'dTmnSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newSlot(); break;
        case 1: _t->openSlot(); break;
        case 2: _t->saveSlot(); break;
        case 3: _t->saveAsSlot(); break;
        case 4: _t->closeSlot(); break;
        case 5: _t->updateDebuggerInfo(); break;
        case 6: _t->debugSlot(); break;
        case 7: _t->dNextSlot(); break;
        case 8: _t->dPreSlot(); break;
        case 9: _t->dJumpSlot(); break;
        case 10: _t->dTmnSlot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
