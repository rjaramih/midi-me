/****************************************************************************
** Meta object code from reading C++ file 'ChainWidget.h'
**
** Created: Thu Jul 23 02:40:48 2009
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../src/Midi-Me/ChainWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChainWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MidiMe__ChainWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x0a,
      39,   30,   20,   20, 0x0a,
      64,   30,   20,   20, 0x0a,
      88,   20,   20,   20, 0x0a,
     115,  107,   20,   20, 0x09,
     139,  107,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MidiMe__ChainWidget[] = {
    "MidiMe::ChainWidget\0\0update()\0mousePos\0"
    "startConnecting(QPointF)\0"
    "stopConnecting(QPointF)\0addControlSignal()\0"
    "pAction\0addChainStart(QAction*)\0"
    "addProcessor(QAction*)\0"
};

const QMetaObject MidiMe::ChainWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_MidiMe__ChainWidget,
      qt_meta_data_MidiMe__ChainWidget, 0 }
};

const QMetaObject *MidiMe::ChainWidget::metaObject() const
{
    return &staticMetaObject;
}

void *MidiMe::ChainWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MidiMe__ChainWidget))
        return static_cast<void*>(const_cast< ChainWidget*>(this));
    if (!strcmp(_clname, "Chain::Listener"))
        return static_cast< Chain::Listener*>(const_cast< ChainWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int MidiMe::ChainWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update(); break;
        case 1: startConnecting((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 2: stopConnecting((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 3: addControlSignal(); break;
        case 4: addChainStart((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: addProcessor((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
