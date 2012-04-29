/****************************************************************************
** Meta object code from reading C++ file 'junction.h'
**
** Created: Sun Apr 29 16:19:39 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ui/TrafficLights_manager/junction.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'junction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Junction[] = {

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
      31,   10,    9,    9, 0x09,
      67,   10,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_Junction[] = {
    "Junction\0\0checkpointId,vehicle\0"
    "addVehicleToStatistic(int,Vehicle*)\0"
    "subtractVehicleFromStatistic(int,Vehicle*)\0"
};

const QMetaObject Junction::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Junction,
      qt_meta_data_Junction, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Junction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Junction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Junction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Junction))
        return static_cast<void*>(const_cast< Junction*>(this));
    return QObject::qt_metacast(_clname);
}

int Junction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addVehicleToStatistic((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Vehicle*(*)>(_a[2]))); break;
        case 1: subtractVehicleFromStatistic((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Vehicle*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
