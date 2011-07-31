/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Thu Jul 23 09:52:06 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../src/Midi-Me/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MidiMe__MainWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      30,   19,   19,   19, 0x0a,
      41,   19,   19,   19, 0x0a,
      52,   19,   19,   19, 0x0a,
      65,   19,   19,   19, 0x0a,
      85,   19,   19,   19, 0x0a,
     107,   19,   19,   19, 0x0a,
     129,  121,   19,   19, 0x0a,
     154,  146,   19,   19, 0x09,
     179,   19,   19,   19, 0x09,
     205,  146,   19,   19, 0x09,
     233,   19,   19,   19, 0x09,
     255,  146,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MidiMe__MainWindow[] = {
    "MidiMe::MainWindow\0\0newFile()\0openFile()\0"
    "saveFile()\0saveFileAs()\0showPluginManager()\0"
    "openVirtualMidiPort()\0aboutDialog()\0"
    "started\0setStarted(bool)\0pAction\0"
    "openRecentFile(QAction*)\0"
    "populateInputDeviceMenu()\0"
    "selectInputDevice(QAction*)\0"
    "populateMidiOutMenu()\0selectMidiOut(QAction*)\0"
};

const QMetaObject MidiMe::MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MidiMe__MainWindow,
      qt_meta_data_MidiMe__MainWindow, 0 }
};

const QMetaObject *MidiMe::MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MidiMe::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MidiMe__MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "DeviceManager::Listener"))
        return static_cast< DeviceManager::Listener*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MidiMe::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: openFile(); break;
        case 2: saveFile(); break;
        case 3: saveFileAs(); break;
        case 4: showPluginManager(); break;
        case 5: openVirtualMidiPort(); break;
        case 6: aboutDialog(); break;
        case 7: setStarted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: openRecentFile((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 9: populateInputDeviceMenu(); break;
        case 10: selectInputDevice((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 11: populateMidiOutMenu(); break;
        case 12: selectMidiOut((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
