/****************************************************************************
** Meta object code from reading C++ file 'usermanagement.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../usermanagement.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usermanagement.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSUserManagementENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSUserManagementENDCLASS = QtMocHelpers::stringData(
    "UserManagement",
    "channelGroupsChanged",
    "",
    "onAddUserClicked",
    "onEditUserClicked",
    "onDeleteUserClicked",
    "onTableItemClicked",
    "row",
    "column",
    "clearForm",
    "onAddChannelGroupClicked",
    "onEditChannelGroupClicked",
    "onDeleteChannelGroupClicked",
    "onChannelGroupTableItemClicked",
    "clearChannelGroupForm"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSUserManagementENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    0,   82,    2, 0x08,    3 /* Private */,
       5,    0,   83,    2, 0x08,    4 /* Private */,
       6,    2,   84,    2, 0x08,    5 /* Private */,
       9,    0,   89,    2, 0x08,    8 /* Private */,
      10,    0,   90,    2, 0x08,    9 /* Private */,
      11,    0,   91,    2, 0x08,   10 /* Private */,
      12,    0,   92,    2, 0x08,   11 /* Private */,
      13,    2,   93,    2, 0x08,   12 /* Private */,
      14,    0,   98,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject UserManagement::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSUserManagementENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSUserManagementENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSUserManagementENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<UserManagement, std::true_type>,
        // method 'channelGroupsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddUserClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditUserClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteUserClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTableItemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clearForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddChannelGroupClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEditChannelGroupClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteChannelGroupClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onChannelGroupTableItemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'clearChannelGroupForm'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void UserManagement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserManagement *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->channelGroupsChanged(); break;
        case 1: _t->onAddUserClicked(); break;
        case 2: _t->onEditUserClicked(); break;
        case 3: _t->onDeleteUserClicked(); break;
        case 4: _t->onTableItemClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->clearForm(); break;
        case 6: _t->onAddChannelGroupClicked(); break;
        case 7: _t->onEditChannelGroupClicked(); break;
        case 8: _t->onDeleteChannelGroupClicked(); break;
        case 9: _t->onChannelGroupTableItemClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 10: _t->clearChannelGroupForm(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UserManagement::*)();
            if (_t _q_method = &UserManagement::channelGroupsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *UserManagement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserManagement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSUserManagementENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserManagement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void UserManagement::channelGroupsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
