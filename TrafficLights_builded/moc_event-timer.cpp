/****************************************************************************
** Meta object code from reading C++ file 'event-timer.h'
**
** Created: Sun Apr 29 15:26:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/Root_window/event-timer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'event-timer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EventTimer[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      18,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   11,   11,   11, 0x08,
      35,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EventTimer[] = {
    "EventTimer\0\0day()\0night()\0setDay()\0"
    "setNight()\0"
};

const QMetaObject EventTimer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EventTimer,
      qt_meta_data_EventTimer, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EventTimer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EventTimer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EventTimer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EventTimer))
        return static_cast<void*>(const_cast< EventTimer*>(this));
    return QObject::qt_metacast(_clname);
}

int EventTimer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: day(); break;
        case 1: night(); break;
        case 2: setDay(); break;
        case 3: setNight(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EventTimer::day()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void EventTimer::night()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
