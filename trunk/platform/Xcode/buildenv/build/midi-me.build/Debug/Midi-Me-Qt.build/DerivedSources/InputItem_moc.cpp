/****************************************************************************
** Meta object code from reading C++ file 'InputItem.h'
**
** Created: Thu Jul 23 02:40:47 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../src/Midi-Me/InputItem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InputItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MidiMe__InputItem[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_MidiMe__InputItem[] = {
    "MidiMe::InputItem\0"
};

const QMetaObject MidiMe::InputItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MidiMe__InputItem,
      qt_meta_data_MidiMe__InputItem, 0 }
};

const QMetaObject *MidiMe::InputItem::metaObject() const
{
    return &staticMetaObject;
}

void *MidiMe::InputItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MidiMe__InputItem))
        return static_cast<void*>(const_cast< InputItem*>(this));
    if (!strcmp(_clname, "ChainItem"))
        return static_cast< ChainItem*>(const_cast< InputItem*>(this));
    if (!strcmp(_clname, "Input::Listener"))
        return static_cast< Input::Listener*>(const_cast< InputItem*>(this));
    return QObject::qt_metacast(_clname);
}

int MidiMe::InputItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
