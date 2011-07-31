/****************************************************************************
** Meta object code from reading C++ file 'PropertyWidgetString.h'
**
** Created: Thu Jul 23 02:39:08 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../src/PropertiesEditor/PropertyWidgetString.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertyWidgetString.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MidiMe__PropertyWidgetString[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      30,   29,   29,   29, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MidiMe__PropertyWidgetString[] = {
    "MidiMe::PropertyWidgetString\0\0changed()\0"
};

const QMetaObject MidiMe::PropertyWidgetString::staticMetaObject = {
    { &PropertyWidget::staticMetaObject, qt_meta_stringdata_MidiMe__PropertyWidgetString,
      qt_meta_data_MidiMe__PropertyWidgetString, 0 }
};

const QMetaObject *MidiMe::PropertyWidgetString::metaObject() const
{
    return &staticMetaObject;
}

void *MidiMe::PropertyWidgetString::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MidiMe__PropertyWidgetString))
        return static_cast<void*>(const_cast< PropertyWidgetString*>(this));
    return PropertyWidget::qt_metacast(_clname);
}

int MidiMe::PropertyWidgetString::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PropertyWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changed(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
