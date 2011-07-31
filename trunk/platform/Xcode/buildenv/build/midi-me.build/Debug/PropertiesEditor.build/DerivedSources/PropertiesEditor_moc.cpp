/****************************************************************************
** Meta object code from reading C++ file 'PropertiesEditor.h'
**
** Created: Thu Jul 23 02:39:08 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../src/PropertiesEditor/PropertiesEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PropertiesEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MidiMe__PropertiesEditor[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x0a,
      56,   34,   25,   25, 0x0a,
     120,  115,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MidiMe__PropertiesEditor[] = {
    "MidiMe::PropertiesEditor\0\0clear()\0"
    "name,type,pProperties\0"
    "addCollection(std::string,std::string,PropertyCollection*)\0"
    "name\0removeCollection(std::string)\0"
};

const QMetaObject MidiMe::PropertiesEditor::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MidiMe__PropertiesEditor,
      qt_meta_data_MidiMe__PropertiesEditor, 0 }
};

const QMetaObject *MidiMe::PropertiesEditor::metaObject() const
{
    return &staticMetaObject;
}

void *MidiMe::PropertiesEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MidiMe__PropertiesEditor))
        return static_cast<void*>(const_cast< PropertiesEditor*>(this));
    if (!strcmp(_clname, "PropertyCollection::Listener"))
        return static_cast< PropertyCollection::Listener*>(const_cast< PropertiesEditor*>(this));
    return QWidget::qt_metacast(_clname);
}

int MidiMe::PropertiesEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clear(); break;
        case 1: addCollection((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< PropertyCollection*(*)>(_a[3]))); break;
        case 2: removeCollection((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
