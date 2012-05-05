/****************************************************************************
** Meta object code from reading C++ file 'trafficlight.h'
**
** Created: Sat May 5 19:54:34 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/Lights/trafficlight.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trafficlight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrafficLight[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      30,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TrafficLight[] = {
    "TrafficLight\0\0letGoVehicles()\0"
    "holdVehicles()\0"
};

const QMetaObject TrafficLight::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_TrafficLight,
      qt_meta_data_TrafficLight, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrafficLight::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrafficLight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrafficLight::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrafficLight))
        return static_cast<void*>(const_cast< TrafficLight*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int TrafficLight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: letGoVehicles(); break;
        case 1: holdVehicles(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
