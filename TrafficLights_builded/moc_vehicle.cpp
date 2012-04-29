/****************************************************************************
** Meta object code from reading C++ file 'vehicle.h'
**
** Created: Sun Apr 29 15:26:01 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/Cars/vehicle.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vehicle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Vehicle[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       1,   69, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,    9,    8,    8, 0x0a,
      42,    8,    8,    8, 0x0a,
      49,    8,    8,    8, 0x0a,
      78,   69,    8,    8, 0x0a,
     100,    8,    8,    8, 0x2a,
     124,  114,    8,    8, 0x0a,
     144,    8,    8,    8, 0x2a,
     170,  160,    8,    8, 0x0a,
     190,    8,    8,    8, 0x2a,
     206,    8,    8,    8, 0x0a,
     219,    8,    8,    8, 0x0a,

 // enums: name, flags, count, data
     231, 0x0,    3,   73,

 // enum data: key, value
     240, uint(Vehicle::RIGHT_BLINKERS),
     255, uint(Vehicle::LEFT_BLINKERS),
     269, uint(Vehicle::NO_BLINKERS),

       0        // eod
};

static const char qt_meta_stringdata_Vehicle[] = {
    "Vehicle\0\0initCheckpoint\0init(Checkpoint*)\0"
    "init()\0onAnimationFinish()\0blinkers\0"
    "setBlinkers(Blinkers)\0setBlinkers()\0"
    "longLight\0setLongLights(bool)\0"
    "setLongLights()\0backLight\0setBackLights(bool)\0"
    "setBackLights()\0resumeMove()\0pauseMove()\0"
    "Blinkers\0RIGHT_BLINKERS\0LEFT_BLINKERS\0"
    "NO_BLINKERS\0"
};

const QMetaObject Vehicle::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_Vehicle,
      qt_meta_data_Vehicle, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Vehicle::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Vehicle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Vehicle::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Vehicle))
        return static_cast<void*>(const_cast< Vehicle*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int Vehicle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: init((*reinterpret_cast< Checkpoint*(*)>(_a[1]))); break;
        case 1: init(); break;
        case 2: onAnimationFinish(); break;
        case 3: setBlinkers((*reinterpret_cast< Blinkers(*)>(_a[1]))); break;
        case 4: setBlinkers(); break;
        case 5: setLongLights((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: setLongLights(); break;
        case 7: setBackLights((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: setBackLights(); break;
        case 9: resumeMove(); break;
        case 10: pauseMove(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
