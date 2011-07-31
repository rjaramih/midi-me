/****************************************************************************
** Meta object code from reading C++ file 'PropertyWidgetBool.h'
**
** Created: Thu Jul 23 02:39:06 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../src/PropertiesEditor/PropertyWidgetBool.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyWidgetBool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MidiMe__PropertyWidgetBool[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      34,   28,   27,   27, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MidiMe__PropertyWidgetBool[] = {
    "MidiMe::PropertyWidgetBool\0\0state\0"
    "changed(int)\0"
};

const QMetaObject MidiMe::PropertyWidgetBool::staticMetaObject = {
    { &PropertyWidget::staticMetaObject, qt_meta_stringdata_MidiMe__PropertyWidgetBool,
      qt_meta_data_MidiMe__PropertyWidgetBool, 0 }
};

const QMetaObject *MidiMe::PropertyWidgetBool::metaObject() const
{
    return &staticMetaObject;
}

void *MidiMe::PropertyWidgetBool::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MidiMe__PropertyWidgetBool))
        return static_cast<void*>(const_cast< PropertyWidgetBool*>(this));
    return PropertyWidget::qt_metacast(_clname);
}

int MidiMe::PropertyWidgetBool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
